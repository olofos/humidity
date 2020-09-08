#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <cmocka.h>
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "firmware.h"

#define TEMP_PARENT_DIR_TEMPLATE "/tmp/test_firmware.temp"
#define TEMP_DIR_TEMPLATE TEMP_PARENT_DIR_TEMPLATE "/test-XXXXXX"

//////// Global variables //////////////////////////////////////////////////////

static const uint8_t fw_mock_const_buf[] = {
    0xA8, 0xD1, 0x08, 0x2E, 0x15, 0xCC, 0x38, 0x54,
    0x9C, 0xFE, 0xDA, 0xE4, 0x2E, 0x9A, 0x70, 0xA0,
    0xA9, 0xEA, 0xA4, 0x41, 0x78, 0x10, 0xBA, 0xE5,
    0x57, 0xDC, 0xBC, 0x91, 0xBA, 0xD1, 0x2B, 0xD2,
    0x21, 0xD8, 0x82, 0x81, 0xCA, 0x2F, 0x92, 0xB9,
    0xE1, 0xF6, 0x77, 0x82, 0x3A, 0x35, 0x80, 0x29,
    0xB3, 0x64, 0xC8, 0xED, 0x58, 0xF9, 0x62, 0xCD,
    0xB4, 0x61, 0x08, 0x65, 0x36, 0x56, 0xFF, 0x94,
};


//////// Mocked functions //////////////////////////////////////////////////////

//////// Helper functions //////////////////////////////////////////////////////

static char *create_temp_dir(void)
{
    static char template[] = TEMP_DIR_TEMPLATE;
    strcpy(template, TEMP_DIR_TEMPLATE);

    char *dirname = mkdtemp(template);
    if(!dirname) {
        perror("mkdtemp");
    } else {
        printf("Created directory %s\n", dirname);
    }

    return dirname;
}

static char *create_temp_file(void)
{
    static char template[] = TEMP_DIR_TEMPLATE;
    strcpy(template, TEMP_DIR_TEMPLATE);

    int fd = mkstemp(template);
    if(fd < 0) {
        perror("mkstemp");
        return NULL;
    } else {
        close(fd);
        printf("Created file %s\n", template);
    }

    return template;
}

static int write_fill(int fd, const uint8_t *buf, int buf_size, int fill_size)
{
    for(int i = 0; i < fill_size; i += buf_size) {
        if(write(fd, buf, buf_size) < 0) return -1;
    }
    return fill_size;
}

#define EMPTY_PAGES 1
#define NO_EMPTY_PAGES 0

static int open_firmware_image(const char *dirname, uint64_t hash, mode_t mode)
{
    int fd = -1;
    char filename[] = TEMP_DIR_TEMPLATE "/0123456789ABCDEF.bin";

    sprintf(filename, "%s/%016" PRIX64 ".bin", dirname, hash);
    printf("Creating %s\n", filename);

    fd = open(filename, mode, 0660);
    if(fd < 0) {
        perror("open");
    }

    return fd;
}

static int create_firmware_image(const char *dirname, uint64_t hash, int empty)
{
    int fd = open_firmware_image(dirname, hash, O_CREAT | O_WRONLY);
    if(fd < 0) goto err;

    const uint8_t empty_buf[] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    };

    const uint8_t hash_buf[] = {
        (hash >> 32) & 0xFF, (hash >> 40) & 0xFF, (hash >> 48) & 0xFF, (hash >> 56) & 0xFF,
        hash & 0xFF, (hash >> 8) & 0xFF, (hash >> 16) & 0xFF, (hash >> 24) & 0xFF,
    };

    if(write_fill(fd, fw_mock_const_buf, sizeof(fw_mock_const_buf), FW_SIZE / 2) < 0) goto err;
    if(empty) {
        if(write_fill(fd, empty_buf, sizeof(empty_buf), FW_SIZE / 4) < 0) goto err;
    } else {
        if(write_fill(fd, fw_mock_const_buf, sizeof(fw_mock_const_buf), FW_SIZE / 4) < 0) goto err;
    }
    if(write_fill(fd, hash_buf, sizeof(hash_buf), FW_SIZE / 4) < 0) goto err;

    close(fd);
    return 1;

err:
    if(fd >= 0) close(fd);
    return -1;
}

static int create_firmware_image_with_size(const char *dirname, uint64_t hash, uint16_t size)
{
    int fd = open_firmware_image(dirname, hash, O_CREAT | O_WRONLY);
    if(fd < 0) goto err;

    const uint8_t hash_buf[] = {
        (hash >> 32) & 0xFF, (hash >> 40) & 0xFF, (hash >> 48) & 0xFF, (hash >> 56) & 0xFF,
        hash & 0xFF, (hash >> 8) & 0xFF, (hash >> 16) & 0xFF, (hash >> 24) & 0xFF,
    };

    if(write_fill(fd, fw_mock_const_buf, sizeof(fw_mock_const_buf), size) < 0) goto err;

    if(size >= FW_SIZE) {
        if(lseek(fd, FW_SIZE - 8, SEEK_SET) < 0) {
            perror("lseek");
            goto err;
        }
        if(write(fd, hash_buf, sizeof(hash_buf)) < 0) {
            perror("write");
            goto err;
        }
    }

    close(fd);
    return 1;

err:
    if(fd >= 0) close(fd);
    return -1;
}

static int create_firmware_image_with_wrong_hash(const char *dirname, uint64_t hash, uint64_t wrong_hash)
{
    int fd = open_firmware_image(dirname, hash, O_CREAT | O_WRONLY);
    if(fd < 0) goto err;

    const uint8_t hash_buf[] = {
        (wrong_hash >> 32) & 0xFF, (wrong_hash >> 40) & 0xFF, (wrong_hash >> 48) & 0xFF, (wrong_hash >> 56) & 0xFF,
        wrong_hash & 0xFF, (wrong_hash >> 8) & 0xFF, (wrong_hash >> 16) & 0xFF, (wrong_hash >> 24) & 0xFF,
    };

    if(write_fill(fd, fw_mock_const_buf, sizeof(fw_mock_const_buf), FW_SIZE / 2) < 0) goto err;
    if(write_fill(fd, hash_buf, sizeof(hash_buf), FW_SIZE / 2) < 0) goto err;

    close(fd);
    return 1;

err:
    if(fd >= 0) close(fd);
    return -1;
}

//////// Tests /////////////////////////////////////////////////////////////////

static void test__firmware_set_dir__returns_non_negative_if_dir_exists(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    int ret = firmware_set_dir(dirname);
    assert_false(ret < 0);

    firmware_deinit();
}

static void test__firmware_set_dir__returns_negative_if_dir_does_not_exist(void **states)
{
    char *dirname = TEMP_DIR_TEMPLATE "-nonexistent";

    int ret = firmware_set_dir(dirname);
    assert_true(ret < 0);

    firmware_deinit();
}

static void test__firmware_set_dir__returns_negative_if_not_a_dir(void **states)
{
    char *dirname = create_temp_file();
    assert_non_null(dirname);

    int ret = firmware_set_dir(dirname);
    assert_true(ret < 0);

    firmware_deinit();
}


static void test__firmware_get_halfpage__returns_data_for_an_odd_page(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image(dirname, hash_new, EMPTY_PAGES) < 0);
    assert_false(create_firmware_image(dirname, hash_old, NO_EMPTY_PAGES) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0x0020,
    };

    assert_false(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);

    assert_int_equal(halfpage.result, FW_DATA);
    assert_memory_equal(halfpage.buf, fw_mock_const_buf + 32, 32);
    assert_int_equal(halfpage.crc, 0x59789098);

    firmware_deinit();
}

static void test__firmware_get_halfpage__returns_data_for_a_changed_even_page(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image(dirname, hash_new, EMPTY_PAGES) < 0);
    assert_false(create_firmware_image(dirname, hash_old, NO_EMPTY_PAGES) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0x6000,
    };

    assert_false(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);

    assert_int_equal(halfpage.result, FW_DATA);

    const uint8_t hash_buf[] = {
        0x67, 0x45, 0x23, 0x01, 0xEF, 0xCD, 0xAB, 0x89,
        0x67, 0x45, 0x23, 0x01, 0xEF, 0xCD, 0xAB, 0x89,
        0x67, 0x45, 0x23, 0x01, 0xEF, 0xCD, 0xAB, 0x89,
        0x67, 0x45, 0x23, 0x01, 0xEF, 0xCD, 0xAB, 0x89,
    };

    assert_memory_equal(halfpage.buf, hash_buf, sizeof(hash_buf));
    assert_int_equal(halfpage.crc, 0x451E824C);

    firmware_deinit();
}

static void test__firmware_get_halfpage__returns_unchanged_for_an_unchanged_even_page(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image(dirname, hash_new, EMPTY_PAGES) < 0);
    assert_false(create_firmware_image(dirname, hash_old, NO_EMPTY_PAGES) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0,
    };

    assert_false(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);
    assert_int_equal(halfpage.result, FW_UNCHANGED);
    assert_int_equal(halfpage.count, FW_SIZE / FW_PAGE_SIZE / 2);

    firmware_deinit();
}

static void test__firmware_get_halfpage__returns_unchanged_for_an_unchanged_empty_even_page(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image(dirname, hash_new, EMPTY_PAGES) < 0);
    assert_false(create_firmware_image(dirname, hash_old, EMPTY_PAGES) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0x4000,
    };

    assert_false(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);
    assert_int_equal(halfpage.result, FW_UNCHANGED);
    assert_int_equal(halfpage.count, FW_SIZE / FW_PAGE_SIZE / 4);

    firmware_deinit();
}

static void test__firmware_get_halfpage__returns_empty_for_a_changed_empty_even_page(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image(dirname, hash_new, EMPTY_PAGES) < 0);
    assert_false(create_firmware_image(dirname, hash_old, NO_EMPTY_PAGES) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0x4000,
    };

    assert_false(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);
    assert_int_equal(halfpage.result, FW_EMPTY);
    assert_int_equal(halfpage.count, FW_SIZE / FW_PAGE_SIZE / 4);

    firmware_deinit();
}

static void test__firmware_get_halfpage__returns_error_when_new_file_does_not_exist(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0x0020,
    };

    assert_true(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);
    assert_int_equal(halfpage.result, FW_ERROR);

    firmware_deinit();
}

static void test__firmware_get_halfpage__returns_error_when_old_file_does_not_exist(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image(dirname, hash_new, EMPTY_PAGES) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0x0040,
    };

    assert_true(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);
    assert_int_equal(halfpage.result, FW_ERROR);

    firmware_deinit();
}

static void test__firmware_get_halfpage__returns_error_when_new_file_is_too_small(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image_with_size(dirname, hash_new, FW_SIZE - sizeof(fw_mock_const_buf)) < 0);
    assert_false(create_firmware_image(dirname, hash_old, NO_EMPTY_PAGES) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0x4000,
    };

    assert_true(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);
    assert_int_equal(halfpage.result, FW_ERROR);

    firmware_deinit();
}

static void test__firmware_get_halfpage__returns_error_when_new_file_is_too_large(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image_with_size(dirname, hash_new, FW_SIZE + sizeof(fw_mock_const_buf)) < 0);
    assert_false(create_firmware_image(dirname, hash_old, NO_EMPTY_PAGES) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0x4000,
    };

    assert_true(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);
    assert_int_equal(halfpage.result, FW_ERROR);

    firmware_deinit();
}

static void test__firmware_get_halfpage__returns_error_when_old_file_is_too_small(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image(dirname, hash_new, EMPTY_PAGES) < 0);
    assert_false(create_firmware_image_with_size(dirname, hash_old, FW_SIZE - sizeof(fw_mock_const_buf)) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0x4000,
    };

    assert_true(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);
    assert_int_equal(halfpage.result, FW_ERROR);

    firmware_deinit();
}

static void test__firmware_get_halfpage__returns_error_when_old_file_is_too_large(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image(dirname, hash_new, EMPTY_PAGES) < 0);
    assert_false(create_firmware_image_with_size(dirname, hash_old, FW_SIZE - sizeof(fw_mock_const_buf)) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0x4000,
    };

    assert_true(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);
    assert_int_equal(halfpage.result, FW_ERROR);

    firmware_deinit();
}

static void test__firmware_get_halfpage__returns_error_when_old_file_has_wrong_hash(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image_with_wrong_hash(dirname, hash_new, hash_old) < 0);
    assert_false(create_firmware_image(dirname, hash_old, NO_EMPTY_PAGES) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0x4000,
    };

    assert_true(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);
    assert_int_equal(halfpage.result, FW_ERROR);

    firmware_deinit();
}

static void test__firmware_get_halfpage__returns_error_when_new_file_has_wrong_hash(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image(dirname, hash_new, NO_EMPTY_PAGES) < 0);
    assert_false(create_firmware_image_with_wrong_hash(dirname, hash_old, hash_new) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0x4000,
    };

    assert_true(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);
    assert_int_equal(halfpage.result, FW_ERROR);

    firmware_deinit();
}

static void test__firmware_get_halfpage__can_reproduce_firmware(void **states)
{
    char *dirname = create_temp_dir();
    assert_non_null(dirname);

    uint64_t hash_new = 0x0123456789ABCDEF;
    uint64_t hash_old = 0x123456789ABCDEF0;

    assert_false(create_firmware_image(dirname, hash_new, EMPTY_PAGES) < 0);
    assert_false(create_firmware_image(dirname, hash_old, NO_EMPTY_PAGES) < 0);
    assert_false(firmware_set_dir(dirname) < 0);

    struct firmware_halfpage halfpage = {
        .address = 0,
    };

    int fd_old = open_firmware_image(dirname, hash_old, O_RDONLY);

    uint8_t buf_fw[FW_SIZE];

    while(halfpage.address < FW_SIZE) {
        assert_false(firmware_get_halfpage(hash_old, hash_new, &halfpage) < 0);
        if(halfpage.result == FW_DATA) {
            memcpy(&buf_fw[halfpage.address], halfpage.buf, FW_HALFPAGE_SIZE);
            halfpage.address += FW_HALFPAGE_SIZE;
        } else if(halfpage.result == FW_UNCHANGED) {
            for(int i = 0; i < halfpage.count; i++) {
                assert_false(lseek(fd_old, halfpage.address, SEEK_SET) < 0);
                assert_false(read(fd_old, &buf_fw[halfpage.address], FW_PAGE_SIZE) < FW_PAGE_SIZE);
                halfpage.address += FW_PAGE_SIZE;
            }
        } else if(halfpage.result == FW_EMPTY) {
            for(int i = 0; i < halfpage.count; i++) {
                memset(&buf_fw[halfpage.address], 0xFF, FW_PAGE_SIZE);
                halfpage.address += FW_PAGE_SIZE;
            }
        } else {
            assert_true(0);
        }
    }

    close(fd_old);

    int fd_new = open_firmware_image(dirname, hash_new, O_RDONLY);
    char buf_new[FW_SIZE];
    assert_false(read(fd_new, buf_new, sizeof(buf_new)) < sizeof(buf_new));
    assert_memory_equal(buf_fw, buf_new, sizeof(buf_new));

    close(fd_new);

    firmware_deinit();
}


const struct CMUnitTest tests_for_firmware_set_dir[] = {
    cmocka_unit_test(test__firmware_set_dir__returns_non_negative_if_dir_exists),
    cmocka_unit_test(test__firmware_set_dir__returns_negative_if_dir_does_not_exist),
    cmocka_unit_test(test__firmware_set_dir__returns_negative_if_not_a_dir),
};

const struct CMUnitTest tests_for_firmware_get_halfpage[] = {
    cmocka_unit_test(test__firmware_get_halfpage__returns_data_for_an_odd_page),
    cmocka_unit_test(test__firmware_get_halfpage__returns_data_for_a_changed_even_page),
    cmocka_unit_test(test__firmware_get_halfpage__returns_unchanged_for_an_unchanged_even_page),
    cmocka_unit_test(test__firmware_get_halfpage__returns_unchanged_for_an_unchanged_empty_even_page),
    cmocka_unit_test(test__firmware_get_halfpage__returns_empty_for_a_changed_empty_even_page),
    cmocka_unit_test(test__firmware_get_halfpage__returns_error_when_new_file_does_not_exist),
    cmocka_unit_test(test__firmware_get_halfpage__returns_error_when_old_file_does_not_exist),
    cmocka_unit_test(test__firmware_get_halfpage__returns_error_when_new_file_is_too_small),
    cmocka_unit_test(test__firmware_get_halfpage__returns_error_when_new_file_is_too_large),
    cmocka_unit_test(test__firmware_get_halfpage__returns_error_when_old_file_is_too_small),
    cmocka_unit_test(test__firmware_get_halfpage__returns_error_when_old_file_is_too_large),
    cmocka_unit_test(test__firmware_get_halfpage__returns_error_when_new_file_has_wrong_hash),
    cmocka_unit_test(test__firmware_get_halfpage__returns_error_when_old_file_has_wrong_hash),
    cmocka_unit_test(test__firmware_get_halfpage__can_reproduce_firmware),
};

//////// Main //////////////////////////////////////////////////////////////////

int main(void)
{
    if(mkdir(TEMP_PARENT_DIR_TEMPLATE, 0770) < 0) {
        if(errno != EEXIST) {
            perror("mkdir");
            return 1;
        }
    }

    int fails = 0;
    fails += cmocka_run_group_tests(tests_for_firmware_set_dir, NULL, NULL);
    fails += cmocka_run_group_tests(tests_for_firmware_get_halfpage, NULL, NULL);

    printf("To clean up, remove the directory %s\n", TEMP_PARENT_DIR_TEMPLATE);

    return fails;
}
