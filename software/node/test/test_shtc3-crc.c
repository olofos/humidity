#define _XOPEN_SOURCE
#define  _POSIX_C_SOURCE 200112L

#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <cmocka.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>

#include "shtc3-crc.h"

//////// Helper Functions //////////////////////////////////////////////////////


//////// Tests /////////////////////////////////////////////////////////////////

// Test data from http://www.sunshine2k.de/coding/javascript/crc/crc_js.html
// Input reflected: false
// Result reflected: false
// Polynomial: 0x31
// Initial value: 0xFF
// Final Xor Value: 0x00

static void test__shtc3_crc__0000(void **state)
{
    assert_int_equal(shtc3_crc(0x0000), 0x81);
}

static void test__shtc3_crc__1234(void **state)
{
    assert_int_equal(shtc3_crc(0x1234), 0x37);
}

static void test__shtc3_crc__DEAD(void **state)
{
    assert_int_equal(shtc3_crc(0xDEAD), 0x98);
}

static void test__shtc3_crc__BEEF(void **state)
{
    assert_int_equal(shtc3_crc(0xBEEF), 0x92);
}

static void test__shtc3_crc__FFFF(void **state)
{
    assert_int_equal(shtc3_crc(0xFFFF), 0xAC);
}


const struct CMUnitTest tests_for_shtc3_crc[] = {
    cmocka_unit_test(test__shtc3_crc__0000),
    cmocka_unit_test(test__shtc3_crc__1234),
    cmocka_unit_test(test__shtc3_crc__DEAD),
    cmocka_unit_test(test__shtc3_crc__BEEF),
    cmocka_unit_test(test__shtc3_crc__FFFF),
};

//////// Main //////////////////////////////////////////////////////////////////


int main(void)
{
    int fails = 0;
    fails += cmocka_run_group_tests(tests_for_shtc3_crc, NULL, NULL);

    return fails;
}
