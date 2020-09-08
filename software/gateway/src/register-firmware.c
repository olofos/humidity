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

#include <sqlite3.h>

#define FW_SIZE 32768
#define HASH_SIZE 8

#define FW_DIR_NAME "firmware"
#define FW_SUFFIX ".bin"

static sqlite3 *db;
static sqlite3_stmt *stmt_insert_firmware;

int db_init(const char *filename)
{
    const char *sql_insert_firmware =
        "INSERT INTO firmware_versions (timestamp, hash) VALUES (@timestamp, @hash)";

    if(sqlite3_open(filename, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_busy_timeout(db, 50);

    const char *sql_pragma_foreign_keys = "PRAGMA foreign_keys = ON";

    if(sqlite3_exec(db, sql_pragma_foreign_keys, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to execute pragma: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    if(sqlite3_prepare_v2(db, sql_insert_firmware, -1, &stmt_insert_firmware, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    return 0;
}

int db_insert_firmware(time_t timestamp, uint64_t hash)
{
    sqlite3_stmt *stmt = stmt_insert_firmware;

    sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, "@timestamp"), timestamp);
    sqlite3_bind_int64(stmt, sqlite3_bind_parameter_index(stmt, "@hash"), hash);

    int ret = sqlite3_step(stmt);
    if(ret != SQLITE_DONE) {
        fprintf(stderr, "SQL error (%d): %s\n", ret, sqlite3_errmsg(db));
        return -1;
    }
    return 0;
}

int open_input(char *filename)
{
    int in;

    if((in = open(filename, O_RDONLY)) < 0) {
        perror("Opening input file");
        goto err;
    }

    struct stat statbuf;
    if(fstat(in, &statbuf) < 0) {
        perror("stat");
        goto err;
    }

    if(!(statbuf.st_mode & S_IFREG)) {
        fprintf(stderr, "Input file is not a regular file\n");
        goto err;
    }

    if(statbuf.st_size != FW_SIZE) {
        fprintf(stderr, "Input file does not have the expected size (%d bytes)\n", FW_SIZE);
        goto err;
    }

    return in;
err:
    return -1;
}

uint64_t read_hash(int in)
{
    off_t off;
    if((off = lseek(in, 0, SEEK_CUR)) < 0) {
        perror("lseek");
        exit(1);
    }

    if(lseek(in, FW_SIZE - HASH_SIZE, SEEK_SET) < 0) {
        perror("lseek");
        exit(1);
    }

    uint8_t hash_buf[HASH_SIZE];
    if(read(in, hash_buf, sizeof(hash_buf)) < 0) {
        perror("read");
        exit(1);
    }

    if(lseek(in, off, SEEK_SET) < 0) {
        perror("lseek");
        exit(1);
    }

    uint64_t hash1 = ((uint64_t)hash_buf[0]) | ((uint64_t)hash_buf[1] << 8) | ((uint64_t)hash_buf[2] << 16) | ((uint64_t)hash_buf[3] << 24);
    uint64_t hash2 = ((uint64_t)hash_buf[4]) | ((uint64_t)hash_buf[5] << 8) | ((uint64_t)hash_buf[6] << 16) | ((uint64_t)hash_buf[7] << 24);

    uint64_t hash = (hash1 << 32) | hash2;

    if(hash & (1ULL << 63)) {
        fprintf(stderr, "63 bit hash expected. Truncating.");
        hash &= ~(1ULL << 63);
    }

    printf("Firmware hash: %016" PRIX64 "\n", hash);

    return hash;
}

int open_output(char *db_filename, uint64_t hash)
{
    char *out_filename = 0;
    char hash_str[2 * HASH_SIZE + 1];
    int out = -1;

    sprintf(hash_str, "%016" PRIX64, hash);

    out_filename = malloc(strlen(db_filename) + strlen(FW_DIR_NAME) + strlen(FW_SUFFIX) + strlen(hash_str) + 2);
    if(!out_filename) {
        perror("malloc");
        goto err;
    }

    strcpy(out_filename, db_filename);
    char *delim = strrchr(out_filename, '/');
    if(!delim) {
        fprintf(stderr, "Could not parse DB filename");
        goto err;
    }

    delim[1] = 0;
    strcat(out_filename, FW_DIR_NAME);
    printf("Firmware directory: %s\n", out_filename);

    int ret;
    if((ret = mkdir(out_filename, 0777)) < 0) {
        if(errno != EEXIST) {
            perror("Could not create directory");
            goto err;
        }
    }

    strcat(out_filename, "/");
    strcat(out_filename, hash_str);
    strcat(out_filename, FW_SUFFIX);

    printf("Opening out file %s\n", out_filename);

    if((out = creat(out_filename, 0666)) < 0) {
        perror("Opening out file");
        goto err;
    }

    free(out_filename);
    return out;

err:
    free(out_filename);
    return out;
}

int copy_file(int in, int out)
{
    char buf[4096];

    printf("Copying firmware\n");

    for(int i = 0; i < FW_SIZE / sizeof(buf); i++) {
        if(read(in, buf, sizeof(buf)) < sizeof(buf)) {
            perror("read");
            return -1;
        }
        if(write(out, buf, sizeof(buf)) < sizeof(buf)) {
            perror("read");
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int in = -1;
    int out = -1;

    if(argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        goto err;
    }

    char *db_filename = getenv("DB");

    if(!db_filename) {
        fprintf(stderr, "No database specified\n");
        goto err;
    }

    printf("Opening database %s\n", db_filename);
    if(db_init(db_filename) < 0) {
        goto err;
    }

    printf("Opening input file %s\n", argv[1]);

    if((in = open_input(argv[1])) < 0) {
        goto err;
    }

    uint64_t hash = read_hash(in);

    if((out = open_output(db_filename, hash)) < 0) {
        goto err;
    }

    if(copy_file(in, out) < 0) {
        goto err;
    }

    if(db_insert_firmware(time(0), hash) < 0) {
        goto err;
    }

    close(in);
    close(out);
    sqlite3_finalize(stmt_insert_firmware);
    sqlite3_close(db);
    return 0;

err:
    if(in >= 0) close(in);
    if(out >= 0) close(out);

    if(stmt_insert_firmware) sqlite3_finalize(stmt_insert_firmware);
    if(db) sqlite3_close(db);
    return 1;
}
