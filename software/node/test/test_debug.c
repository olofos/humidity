#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "rtc.h"
#include "package-protocol.h"
#include "debug.h"

//////// Global variables //////////////////////////////////////////////////////

#define NODE_ID 65

//////// Mocked functions //////////////////////////////////////////////////////

static struct pkg_timestamp rtc_get_time_mock_timestamp = {
    .year = 0x20,
    .month = 0x01,
    .day = 0x02,
    .hour = 0x03,
    .minute = 0x04,
    .second = 0x05,
};

void rtc_get_time(struct pkg_timestamp *timestamp)
{
    *timestamp = rtc_get_time_mock_timestamp;
}

//////// Helper functions //////////////////////////////////////////////////////

#define assert_timestamp_equal(t1,t2) do {      \
        assert_int_equal(t1.year,t2.year);      \
        assert_int_equal(t1.month,t2.month);    \
        assert_int_equal(t1.day,t2.day);        \
        assert_int_equal(t1.hour,t2.hour);      \
        assert_int_equal(t1.minute,t2.minute);  \
        assert_int_equal(t1.second,t2.second);  \
    } while(0)

//////// Tests /////////////////////////////////////////////////////////////////

static void test__debug_empty__returns_true_when_empty(void **state)
{
    assert_true(debug_empty());
    debug_print("Hi");
    assert_false(debug_empty());
    debug_handled();
    assert_true(debug_empty());
}

static void test__debug_get__returns_null_when_empty(void **state)
{
    struct debug_message *msg = debug_get();
    assert_null(msg);
}

static void test__debug_print__adds_the_message(void **state)
{
    char *str = "Hi!";

    debug_print(str);
    struct debug_message *msg = debug_get();

    assert_non_null(msg);
    assert_int_equal(msg->len, strlen(str));
    assert_timestamp_equal(msg->timestamp, rtc_get_time_mock_timestamp);
    assert_memory_equal(msg->buf, str, strlen(str));
}

static void test__debug_print__doesnt_add_anything_if_string_is_empty(void **state)
{
    struct debug_message *msg1 = debug_get();
    debug_print("");
    struct debug_message *msg2 = debug_get();

    assert_ptr_equal(msg1, msg2);
}

static void test__debug_print__adds_a_long_message(void **state)
{
    char *str =
        "0123456789012345678901234567890123456789"
        "01234567890123456789";

    debug_print(str);
    struct debug_message *msg;

    msg = debug_get();

    assert_non_null(msg);
    assert_int_equal(msg->len, DEBUG_LEN);
    assert_timestamp_equal(msg->timestamp, rtc_get_time_mock_timestamp);
    assert_memory_equal(msg->buf, str, DEBUG_LEN);

    debug_handled();

    msg = debug_get();

    assert_non_null(msg);
    assert_int_equal(msg->len, strlen(str) - DEBUG_LEN);
    assert_timestamp_equal(msg->timestamp, rtc_get_time_mock_timestamp);
    assert_memory_equal(msg->buf, str, strlen(str) - DEBUG_LEN);

    debug_handled();
}

static void test__debug_printf__adds_the_message(void **state)
{
    char *str = "The answer is: 42";
    debug_printf("The answer is: %d", 42);
    struct debug_message *msg = debug_get();

    assert_non_null(msg);
    assert_int_equal(msg->len, strlen(str));
    assert_timestamp_equal(msg->timestamp, rtc_get_time_mock_timestamp);
    assert_memory_equal(msg->buf, str, strlen(str));
}


static int setup(void **state)
{
    memset(&debug_cbuf, 0, sizeof(debug_cbuf));

    return 0;
}

static const struct CMUnitTest tests_for_debug[] = {
    cmocka_unit_test_setup(test__debug_empty__returns_true_when_empty, setup),
    cmocka_unit_test_setup(test__debug_get__returns_null_when_empty, setup),
    cmocka_unit_test_setup(test__debug_print__adds_the_message, setup),
    cmocka_unit_test_setup(test__debug_print__adds_a_long_message, setup),
    cmocka_unit_test_setup(test__debug_print__doesnt_add_anything_if_string_is_empty, setup),
    cmocka_unit_test_setup(test__debug_printf__adds_the_message, setup),
};

//////// Main //////////////////////////////////////////////////////////////////


int main(void)
{
    int fails = 0;
    fails += cmocka_run_group_tests(tests_for_debug, NULL, NULL);

    return fails;
}
