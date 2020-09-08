#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdio.h>

#include "crc32.h"

//////// Global variables //////////////////////////////////////////////////////


//////// Mocked functions //////////////////////////////////////////////////////


//////// Helper functions //////////////////////////////////////////////////////


//////// Tests /////////////////////////////////////////////////////////////////

static void test__crc32__00000000(void **states)
{
    uint8_t buf[] = { 0x00, 0x00, 0x00, 0x00, };
    assert_int_equal(crc32(buf, sizeof(buf)), 0x2144DF1C);
}

static void test__crc32__FFFFFFFF(void **states)
{
    uint8_t buf[] = { 0xFF, 0xFF, 0xFF, 0xFF, };
    assert_int_equal(crc32(buf, sizeof(buf)), 0xFFFFFFFF);
}

static void test__crc32__0123456789ABCDEF(void **states)
{
    uint8_t buf[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, };
    assert_int_equal(crc32(buf, sizeof(buf)), 0x28C7D1AE);
}

static void test__crc32__64bytes(void **states)
{
    uint8_t buf[] = {
        0xA8, 0xD1, 0x08, 0x2E, 0x15, 0xCC, 0x38, 0x54,
        0x9C, 0xFE, 0xDA, 0xE4, 0x2E, 0x9A, 0x70, 0xA0,
        0xA9, 0xEA, 0xA4, 0x41, 0x78, 0x10, 0xBA, 0xE5,
        0x57, 0xDC, 0xBC, 0x91, 0xBA, 0xD1, 0x2B, 0xD2,
        0x21, 0xD8, 0x82, 0x81, 0xCA, 0x2F, 0x92, 0xB9,
        0xE1, 0xF6, 0x77, 0x82, 0x3A, 0x35, 0x80, 0x29,
        0xB3, 0x64, 0xC8, 0xED, 0x58, 0xF9, 0x62, 0xCD,
        0xB4, 0x61, 0x08, 0x65, 0x36, 0x56, 0xFF, 0x94,
    };
    assert_int_equal(crc32(buf, sizeof(buf)), 0x2840E1A4);
}

const struct CMUnitTest tests_for_crc32[] = {
    cmocka_unit_test(test__crc32__00000000),
    cmocka_unit_test(test__crc32__FFFFFFFF),
    cmocka_unit_test(test__crc32__0123456789ABCDEF),
    cmocka_unit_test(test__crc32__64bytes),
};


//////// Main //////////////////////////////////////////////////////////////////


int main(void)
{
    int fails = 0;
    fails += cmocka_run_group_tests(tests_for_crc32, NULL, NULL);

    return fails;
}
