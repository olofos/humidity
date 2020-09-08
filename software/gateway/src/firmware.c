#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>

#include "firmware.h"
#include "crc32.h"

#ifdef UNIT_TESTING
extern void* _test_malloc(const size_t size, const char* file, const int line);
extern void _test_free(void *ptr, const char* file, const int line);
#define malloc(size) _test_malloc(size, __FILE__, __LINE__)
#define free(ptr) _test_free(ptr, __FILE__, __LINE__)
#endif

#define FW_SUFFIX ".bin"
#define FW_DIRNAME "/firmware/"
#define FW_NAME_LEN (2*8)

static char *fw_dirname;

static int firmware_check_dir(void)
{
    struct stat statbuf;
    if(stat(fw_dirname, &statbuf) < 0) {
        perror("stat");
        return -1;
    }

    if(!(statbuf.st_mode & S_IFDIR)) {
        fprintf(stderr, "Error: %s is not a directory\n", fw_dirname);
        return -1;
    }

    return 1;
}

int firmware_set_dir(char *dirname)
{
    if(dirname[strlen(dirname)-1] == '/') {
        fw_dirname = malloc(strlen(dirname) + 1);
        if(!fw_dirname) {
            perror("malloc");
            return -1;
        }
        strcpy(fw_dirname, dirname);
    } else {
        fw_dirname = malloc(strlen(dirname) + 2);
        if(!fw_dirname) {
            perror("malloc");
            return -1;
        }
        strcpy(fw_dirname, dirname);
        strcat(fw_dirname, "/");
    }

    printf("Setting firmware directory to %s\n", fw_dirname);

    return firmware_check_dir();
}

int firmware_set_dir_from_file(char *name)
{
    char *filename = strdup(name);

    if(!filename) {
        perror("malloc");
        return -1;
    }

    char *dir = dirname(filename);

    fw_dirname = malloc(strlen(dir) + strlen(FW_DIRNAME) + 1);

    if(!fw_dirname) {
        perror("malloc");
        return -1;
    }

    strcpy(fw_dirname, dir);
    strcat(fw_dirname, FW_DIRNAME);

    free(filename);

    printf("Setting firmware directory to %s\n", fw_dirname);

    return firmware_check_dir();
}

void firmware_deinit(void)
{
    if(fw_dirname) {
        free(fw_dirname);
    }
    fw_dirname = 0;
}

static int firmware_check_stat(int fd, uint64_t hash)
{
    struct stat statbuf;

    if(fstat(fd, &statbuf) < 0) {
        perror("stat");
        return -1;
    }

    if(!(statbuf.st_mode & S_IFREG)) {
        fprintf(stderr, "Firmware %016" PRIX64 " is not a regular file\n", hash);
        return -1;
    }

    if(statbuf.st_size != FW_SIZE) {
        fprintf(stderr, "Firmware %016" PRIX64 " does not have the expected size (expected %d bytes but found %ld bytes)\n", hash, FW_SIZE, statbuf.st_size);
        return -1;
    }

    return 1;
}

static int firmware_check_hash(int fd, uint64_t hash)
{
    off_t off;
    if((off = lseek(fd, 0, SEEK_CUR)) < 0) {
        perror("lseek");
        return -1;
    }

    if(lseek(fd, FW_SIZE - 8, SEEK_SET) < 0) {
        perror("lseek");
        return -1;
    }

    uint8_t hash_buf[8];
    if(read(fd, hash_buf, sizeof(hash_buf)) != sizeof(hash_buf)) {
        fprintf(stderr, "Could not read firmware hash\n");
        return -1;
    }

    if(lseek(fd, off, SEEK_SET) < 0) {
        perror("lseek");
        return -1;
    }

    uint64_t file_hash_hi = ((uint64_t)hash_buf[3] << 24) | ((uint64_t)hash_buf[2] << 16) | ((uint64_t)hash_buf[1] << 8) | ((uint64_t)hash_buf[0]);
    uint64_t file_hash_lo = ((uint64_t)hash_buf[7] << 24) | ((uint64_t)hash_buf[6] << 16) | ((uint64_t)hash_buf[5] << 8) | ((uint64_t)hash_buf[4]);
    uint64_t file_hash = (file_hash_hi << 32) | file_hash_lo;

    if(file_hash != hash) {
        fprintf(stderr, "Firmware hash does not match (expected %016" PRIX64 " but found %016" PRIX64 ")\n", hash, file_hash);
        return -1;
    }

    return 1;
}

static int firmware_check(int fd, uint64_t hash)
{
    if(firmware_check_stat(fd, hash) < 0) {
        return -1;
    }
    if(firmware_check_hash(fd, hash) < 0) {
        return -1;
    }
    return 1;
}

static int firmware_open(uint64_t hash)
{
    int fd = -1;

    char *filename = malloc(strlen(fw_dirname) + FW_NAME_LEN + strlen(FW_SUFFIX) + 1);
    if(!filename) {
        perror("malloc");
        goto err;
    }

    sprintf(filename, "%s%016" PRIX64 FW_SUFFIX, fw_dirname, hash);

    printf("Opening %s\n", filename);
    fd = open(filename, O_RDONLY);
    if(fd < 0) {
        perror("open");
        goto err;
    }

    if(firmware_check(fd, hash) < 0) {
        goto err;
    }

    free(filename);
    return fd;

err:
    if(fd >= 0) close(fd);
    free(filename);
    return -1;
}

static int16_t count_equal_pages(int fd_old, int fd_new, uint16_t address)
{
    if(lseek(fd_new, address, SEEK_SET) < 0) {
        perror("lseek");
        return -1;
    }

    if(lseek(fd_old, address, SEEK_SET) < 0) {
        perror("lseek");
        return -1;
    }

    int16_t count = 0;
    char old_buf[FW_PAGE_SIZE];
    char new_buf[FW_PAGE_SIZE];

    while(address < FW_SIZE) {
        int ret;
        ret = read(fd_old, old_buf, FW_PAGE_SIZE);
        if(ret < 0) {
            perror("read old");
            return -1;
        }
        if(ret < FW_PAGE_SIZE) {
            printf("Unexpected EOF in old file\n");
            return -1;
        }
        ret = read(fd_new, new_buf, FW_PAGE_SIZE);
        if(ret < 0) {
            perror("read new");
            return -1;
        }
        if(ret < FW_PAGE_SIZE) {
            printf("Unexpected EOF in new file\n");
            return -1;
        }

        if(memcmp(old_buf, new_buf, FW_PAGE_SIZE) == 0) {
            count++;
        } else {
            break;
        }

        address += FW_PAGE_SIZE;
    }

    return count;
}

static int16_t count_empty_pages(int fd_new, uint16_t address)
{
    if(lseek(fd_new, address, SEEK_SET) < 0) {
        perror("lseek");
        return -1;
    }

    int16_t count = 0;
    uint8_t new_buf[FW_PAGE_SIZE];

    while(address < FW_SIZE) {
        int ret = read(fd_new, new_buf, FW_PAGE_SIZE);
        if(ret < 0) {
            perror("read");
            return -1;
        }
        if(ret < FW_PAGE_SIZE) {
            printf("Unexpected EOF\n");
            return -1;
        }

        int is_empty = 1;
        for(int i = 0; i < FW_PAGE_SIZE; i++) {
            if(new_buf[i] != 0xFF) {
                is_empty = 0;
                break;
            }
        }

        if(is_empty) {
            count++;
        } else {
            break;
        }

        address += FW_PAGE_SIZE;
    }

    return count;
}


int firmware_get_halfpage(uint64_t old_hash, uint64_t new_hash, struct firmware_halfpage *halfpage)
{
    if(!halfpage) {
        fprintf(stderr, "halpage must be non-NULL\n");
        return -1;
    }

    halfpage->result = FW_ERROR;

    if(halfpage->address > FW_SIZE) {
        fprintf(stderr, "Address %04X is larger than firmware size %04X\n", halfpage->address, FW_SIZE);
        return -1;
    }
    if(halfpage->address & (FW_HALFPAGE_SIZE - 1)) {
        fprintf(stderr, "Address %04X is not a multiple of %d\n", halfpage->address, FW_HALFPAGE_SIZE);
        return -1;
    }

    int fd_old = -1;
    int fd_new = -1;

    if((fd_new = firmware_open(new_hash)) < 0) goto cleanup;

    if((halfpage->address & (FW_PAGE_SIZE - 1)) == 0) {
        // Even page
        if((fd_old = firmware_open(old_hash)) < 0) goto cleanup;

        int16_t equal_count = count_equal_pages(fd_old, fd_new, halfpage->address);
        if(equal_count < 0) goto cleanup;

        if(equal_count > 0) {
            halfpage->result = FW_UNCHANGED;
            halfpage->count = equal_count;
            printf("%d unchanged pages\n", equal_count);
            goto cleanup;
        }

        int16_t empty_count = count_empty_pages(fd_new, halfpage->address);
        if(empty_count < 0) goto cleanup;
        if(empty_count > 0) {
            halfpage->result = FW_EMPTY;
            halfpage->count = empty_count;
            printf("%d empty pages\n", empty_count);
            goto cleanup;
        }
    }

    // Odd page or no match: just return the data

    if(lseek(fd_new, halfpage->address, SEEK_SET) < 0) {
        perror("lseek");
        goto cleanup;
    }

    if(read(fd_new, halfpage->buf, FW_HALFPAGE_SIZE) < 0) {
        perror("read");
        goto cleanup;
    }

    halfpage->result = FW_DATA;
    halfpage->crc = crc32(halfpage->buf, FW_HALFPAGE_SIZE);

cleanup:
    if(fd_old >= 0) close(fd_old);
    if(fd_new >= 0) close(fd_new);

    return halfpage->result;
}
