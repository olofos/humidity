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
#include "rtc.h"
#include "package-protocol.h"
#include "measurement.h"
#include "package-handler.h"
#include "debug.h"

//////// Global variables //////////////////////////////////////////////////////

#define NODE_ID 65

//////// Mocked functions //////////////////////////////////////////////////////

void rtc_set_time(const struct pkg_timestamp *timestamp)
{
    check_expected(timestamp);
}

//////// Helper functions //////////////////////////////////////////////////////

#define construct_pkg(pkg) construct_pkg_helper(pkg, sizeof(pkg))

struct pkg_buffer construct_pkg_helper(uint8_t *buf, size_t len)
{
    struct pkg_buffer p;

    p.write_counter = 0;
    p.read_counter = 2;
    p.len = p.buf[0] = len + 2;
    p.from = p.buf[1] = NODE_ID;

    for(int i = 2; i < sizeof(p.buf); i++) {
        if(i - 2 < len) {
            p.buf[i] = buf[i - 2];
        } else {
            p.buf[i] = 0xAA;
        }
    }

    return p;
}

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
    struct debug_message msg = {
        .timestamp = {
            .year = 0x20,
            .month = 0x01,
            .day = 0x02,
            .hour = 0x03,
            .minute = 0x04,
            .second = 0x05,
        },
        .buf = "Hi there, this is a test",
    };
    msg.len = strlen(msg.buf);

    struct pkg_buffer pkg_buffer;

    construct_debug_package(&pkg_buffer, &msg);

    uint8_t buf[] = { 0x82, 0x02, 0x01, 0x20, 0x05, 0x04, 0x03, 'H', 'i', ' ', 't', 'h', 'e', 'r', 'e', ',', ' ', 't', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a', ' ', 't', 'e', 's', 't', };
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

static void test__handle_ack_or_nack_returns_ok_for_ack(void **test_state)
{
    uint8_t pkg[] = { 0x01, 0x00 };
    struct pkg_buffer pkg_buffer = construct_pkg(pkg);

    struct state state = { .flags = 0, .update = { .hash = 0, .address = 0 }};

    int ret = handle_ack_or_nack(&pkg_buffer, &state);

    assert_int_equal(ret, PKG_OK);
    assert_int_equal(state.flags, 0);
}

static void test__handle_ack_or_nack_returns_error_for_nack(void **test_state)
{
    uint8_t pkg[] = { 0x00, 0x00 };
    struct pkg_buffer pkg_buffer = construct_pkg(pkg);

    struct state state = { .flags = 0, .update = { .hash = 0, .address = 0 }};

    int ret = handle_ack_or_nack(&pkg_buffer, &state);

    assert_int_equal(ret, PKG_ERROR);
    assert_int_equal(state.flags, 0);
}

static void test__handle_ack_or_nack_returns_error_for_nack_no_retry(void **test_state)
{
    uint8_t pkg[] = { 0x00, 0x08 };
    struct pkg_buffer pkg_buffer = construct_pkg(pkg);

    struct state state = { .flags = 0, .update = { .hash = 0, .address = 0 }};

    int ret = handle_ack_or_nack(&pkg_buffer, &state);

    assert_int_equal(ret, PKG_ERROR_NO_RETRY);
    assert_int_equal(state.flags, 0);
}

static void test__handle_ack_or_nack_clears_registered_flag(void **test_state)
{
    uint8_t pkg[] = { 0x00, 0x02, };
    struct pkg_buffer pkg_buffer = construct_pkg(pkg);

    struct state state = { .flags = STATE_FLAG_REGISTERED, .update = { .hash = 0, .address = 32 }};

    int ret = handle_ack_or_nack(&pkg_buffer, &state);

    assert_int_equal(ret, PKG_ERROR);
    assert_int_equal(state.flags, 0);
}

static void test__handle_ack_or_nack_sets_the_time(void **test_state)
{
    uint8_t pkg[] = { 0x01, 0x04, 0x02, 0x01, 0x20, 0x05, 0x04, 0x03, };
    struct pkg_buffer pkg_buffer = construct_pkg(pkg);

    struct state state = { .flags = 0, .update = { .hash = 0, .address = 0 }};

    struct pkg_timestamp pkg_timestamp = {
        .year = 0x20,
        .month = 0x01,
        .day = 0x02,
        .hour = 0x03,
        .minute = 0x04,
        .second = 0x05,
    };

    expect_memory(rtc_set_time, timestamp, &pkg_timestamp, sizeof(pkg_timestamp));

    int ret = handle_ack_or_nack(&pkg_buffer, &state);

    assert_int_equal(ret, PKG_OK);
    assert_int_equal(state.flags, 0);
}

static void test__handle_ack_or_nack_sets_update_data(void **test_state)
{
    uint8_t pkg[] = { 0x01, 0x01, 0xEC, 0xDD, 0xBA, 0x33, 0xEE, 0xFF, 0xC0, 0xAF,};
    struct pkg_buffer pkg_buffer = construct_pkg(pkg);

    struct state state = { .flags = 0, .update = { .hash = 0, .address = 32 }};

    int ret = handle_ack_or_nack(&pkg_buffer, &state);

    assert_int_equal(ret, PKG_OK);
    assert_int_equal(state.flags, STATE_FLAG_UPDATE_AVAILABLE);
    assert_int_equal(state.update.hash, 0x33BADDECAFC0FFEE);
    assert_int_equal(state.update.address, 0);
}

static void test__handle_ack_or_nack_sets_update_data_and_time(void **test_state)
{
    uint8_t pkg[] = { 0x01, 0x05, 0xEC, 0xDD, 0xBA, 0x33, 0xEE, 0xFF, 0xC0, 0xAF, 0x02, 0x01, 0x20, 0x05, 0x04, 0x03, };
    struct pkg_buffer pkg_buffer = construct_pkg(pkg);

    struct state state = { .flags = 0, .update = { .hash = 0, .address = 32 }};

    struct pkg_timestamp pkg_timestamp = {
        .year = 0x20,
        .month = 0x01,
        .day = 0x02,
        .hour = 0x03,
        .minute = 0x04,
        .second = 0x05,
    };

    expect_memory(rtc_set_time, timestamp, &pkg_timestamp, sizeof(pkg_timestamp));

    int ret = handle_ack_or_nack(&pkg_buffer, &state);

    assert_int_equal(ret, PKG_OK);
    assert_int_equal(state.flags, STATE_FLAG_UPDATE_AVAILABLE);
    assert_int_equal(state.update.hash, 0x33BADDECAFC0FFEE);
    assert_int_equal(state.update.address, 0);
}

static void test__handle_ack_or_nack_updates_update_data_if_update_has_not_started(void **test_state)
{
    uint8_t pkg[] = { 0x01, 0x01, 0xEC, 0xDD, 0xBA, 0x33, 0xEE, 0xFF, 0xC0, 0xAF,};
    struct pkg_buffer pkg_buffer = construct_pkg(pkg);

    struct state state = { .flags = STATE_FLAG_UPDATE_AVAILABLE, .update = { .hash = 0x1234567812345678, .address = 0 }};

    int ret = handle_ack_or_nack(&pkg_buffer, &state);

    assert_int_equal(ret, PKG_OK);
    assert_int_equal(state.flags, STATE_FLAG_UPDATE_AVAILABLE);
    assert_int_equal(state.update.hash, 0x33BADDECAFC0FFEE);
    assert_int_equal(state.update.address, 0);
}

static void test__handle_ack_or_nack_does_not_change_update_data_if_update_has_started(void **test_state)
{
    uint8_t pkg[] = { 0x01, 0x01, 0xEC, 0xDD, 0xBA, 0x33, 0xEE, 0xFF, 0xC0, 0xAF,};
    struct pkg_buffer pkg_buffer = construct_pkg(pkg);

    struct state state = { .flags = STATE_FLAG_UPDATE_AVAILABLE, .update = { .hash = 0x1234567812345678, .address = 32 }};

    int ret = handle_ack_or_nack(&pkg_buffer, &state);

    assert_int_equal(ret, PKG_OK);
    assert_int_equal(state.flags, STATE_FLAG_UPDATE_AVAILABLE);
    assert_int_equal(state.update.hash, 0x1234567812345678);
    assert_int_equal(state.update.address, 32);
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
};

static const struct CMUnitTest tests_for_construct_update_request_package[] = {
    cmocka_unit_test(test__construct_update_request_package_constructs_package),
};

static const struct CMUnitTest tests_for_handle_ack_or_nack[] = {
    cmocka_unit_test(test__handle_ack_or_nack_returns_ok_for_ack),
    cmocka_unit_test(test__handle_ack_or_nack_returns_error_for_nack),
    cmocka_unit_test(test__handle_ack_or_nack_returns_error_for_nack_no_retry),
    cmocka_unit_test(test__handle_ack_or_nack_clears_registered_flag),
    cmocka_unit_test(test__handle_ack_or_nack_sets_the_time),
    cmocka_unit_test(test__handle_ack_or_nack_sets_update_data),
    cmocka_unit_test(test__handle_ack_or_nack_sets_update_data_and_time),
    cmocka_unit_test(test__handle_ack_or_nack_updates_update_data_if_update_has_not_started),
    cmocka_unit_test(test__handle_ack_or_nack_does_not_change_update_data_if_update_has_started),
};

//////// Main //////////////////////////////////////////////////////////////////


int main(void)
{
    int fails = 0;
    fails += cmocka_run_group_tests(tests_for_construct_measurement_package, NULL, NULL);
    fails += cmocka_run_group_tests(tests_for_construct_registration_package, NULL, NULL);
    fails += cmocka_run_group_tests(tests_for_construct_debug_package, NULL, NULL);
    fails += cmocka_run_group_tests(tests_for_construct_update_request_package, NULL, NULL);
    fails += cmocka_run_group_tests(tests_for_handle_ack_or_nack, NULL, NULL);

    return fails;
}
