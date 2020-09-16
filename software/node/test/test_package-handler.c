#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "state.h"
#include "adc.h"
#include "shtc3.h"
#include "package-protocol.h"
#include "measurement.h"
#include "package-handler.h"

//////// Global variables //////////////////////////////////////////////////////

//////// Mocked functions //////////////////////////////////////////////////////

//////// Helper functions //////////////////////////////////////////////////////

#define assert_package_equal(p,resp) do { assert_memory_equal(p.buf, resp, sizeof(resp)); assert_int_equal(p.write_counter, sizeof(resp)); } while(0)

//////// Tests /////////////////////////////////////////////////////////////////

static void test__construct_registration_package_constructs_package(void **state)
{
    struct pkg_buffer pkg_buffer;
    construct_registration_package(&pkg_buffer, 0x01, 0x31BADDECAFC0FFEE);

    uint8_t buf[] = { 0x80, 0x01, 0xEC, 0xDD, 0xBA, 0x31, 0xEE, 0xFF, 0xC0, 0xAF, 0x01 };
    assert_package_equal(pkg_buffer, buf);
}

static void test__construct_measurement_package_constructs_package_when_retries_is_zero(void **state)
{
    struct measurement measurement = {
        .timestamp = {
            .year = 0x20,
            .month = 0x01,
            .day = 0x02,
            .hour = 0x03,
            .minute = 0x04,
            .second = 0x05,
        },
        .humidity_temperature = {
            .humidity = 0x8040,
            .temperature = 0x1920,
        },
        .voltages = {
            .vcc = 0x1800,
            .vmid = 0x1444,
        },
        .retries = 0,
    };

    struct pkg_buffer pkg_buffer;

    construct_measurement_package(&pkg_buffer, &measurement);

    uint8_t buf[] = { 0x81, 0x02, 0x01, 0x20, 0x05, 0x04, 0x03, 0x40, 0x80, 0x20, 0x19, 0x00, 0x18, 0x44, 0x14 };
    assert_package_equal(pkg_buffer, buf);
}

static void test__construct_measurement_package_constructs_package_when_retries_is_not_zero(void **state)
{
    struct measurement measurement = {
        .timestamp = {
            .year = 0x20,
            .month = 0x01,
            .day = 0x02,
            .hour = 0x03,
            .minute = 0x04,
            .second = 0x05,
        },
        .humidity_temperature = {
            .humidity = 0x8040,
            .temperature = 0x1920,
        },
        .voltages = {
            .vcc = 0x1800,
            .vmid = 0x1444,
        },
        .retries = 3,
    };

    struct pkg_buffer pkg_buffer;

    construct_measurement_package(&pkg_buffer, &measurement);

    uint8_t buf[] = { 0x85, 0x02, 0x01, 0x20, 0x05, 0x04, 0x03, 0x40, 0x80, 0x20, 0x19, 0x00, 0x18, 0x44, 0x14 };
    assert_package_equal(pkg_buffer, buf);
}

static void test__construct_debug_package_constructs_package(void **state)
{
    struct pkg_timestamp timestamp = {
        .year = 0x20,
        .month = 0x01,
        .day = 0x02,
        .hour = 0x03,
        .minute = 0x04,
        .second = 0x05,
    };

    struct pkg_buffer pkg_buffer;

    construct_debug_package(&pkg_buffer, &timestamp, "Hi there, this is a test");

    uint8_t buf[] = { 0x82, 0x02, 0x01, 0x20, 0x05, 0x04, 0x03, 'H', 'i', ' ', 't', 'h', 'e', 'r', 'e', ',', ' ', 't', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a', ' ', 't', 'e', 's', 't', };
    assert_package_equal(pkg_buffer, buf);
}

static void test__construct_debug_package_truncates_long_messages(void **state)
{
    struct pkg_timestamp timestamp = {
        .year = 0x20,
        .month = 0x01,
        .day = 0x02,
        .hour = 0x03,
        .minute = 0x04,
        .second = 0x05,
    };

    struct pkg_buffer pkg_buffer;

    construct_debug_package(&pkg_buffer, &timestamp, "012345678901234567890123456789012345678901234567890123456789");

    uint8_t buf[] = {
        0x82, 0x02, 0x01, 0x20, 0x05, 0x04, 0x03,
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    };
    assert_package_equal(pkg_buffer, buf);
}

static void test__construct_update_request_package_constructs_package(void **state)
{
    struct pkg_buffer pkg_buffer;

    construct_update_request_package(&pkg_buffer, 0x0123456789ABCDEF, 0x33BADDECAFC0FFEE, 0x1240);

    uint8_t buf[] = {
        0x83,
        0x40, 0x12,
        0x67, 0x45, 0x23, 0x01, 0xEF, 0xCD, 0xAB, 0x89,
        0xEC, 0xDD, 0xBA, 0x33, 0xEE, 0xFF, 0xC0, 0xAF,
    };
    assert_package_equal(pkg_buffer, buf);
}


static const struct CMUnitTest tests_for_construct_registration_package[] = {
    cmocka_unit_test(test__construct_registration_package_constructs_package),
};

static const struct CMUnitTest tests_for_construct_measurement_package[] = {
    cmocka_unit_test(test__construct_measurement_package_constructs_package_when_retries_is_zero),
    cmocka_unit_test(test__construct_measurement_package_constructs_package_when_retries_is_not_zero),
};

static const struct CMUnitTest tests_for_construct_debug_package[] = {
    cmocka_unit_test(test__construct_debug_package_constructs_package),
    cmocka_unit_test(test__construct_debug_package_truncates_long_messages),
};

static const struct CMUnitTest tests_for_construct_update_request_package[] = {
    cmocka_unit_test(test__construct_update_request_package_constructs_package),
};

//////// Main //////////////////////////////////////////////////////////////////


int main(void)
{
    int fails = 0;
    fails += cmocka_run_group_tests(tests_for_construct_measurement_package, NULL, NULL);
    fails += cmocka_run_group_tests(tests_for_construct_registration_package, NULL, NULL);
    fails += cmocka_run_group_tests(tests_for_construct_debug_package, NULL, NULL);
    fails += cmocka_run_group_tests(tests_for_construct_update_request_package, NULL, NULL);

    return fails;
}
