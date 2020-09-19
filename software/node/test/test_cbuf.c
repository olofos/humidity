#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdio.h>

#include "cbuf.h"

#define cbuf_LEN 64

struct {
    uint8_t head;
    uint8_t tail;
    uint8_t buf[cbuf_LEN];
} cbuf;


//////// Tests /////////////////////////////////////////////////////////////////

static void test__cbuf_init__leaves_an_empty_buffer(void **state)
{
    cbuf.head = 0xAB;
    cbuf.head = 0xCD;

    cbuf_init(cbuf);

    assert_true(cbuf_empty(cbuf));
}

static void test__cbuf_len__returns_the_length_when_length_is_one(void **state)
{
    cbuf_init(cbuf);

    for(int i = 0; i < 512; i++) {
        cbuf_push(cbuf, 0);
        assert_int_equal(cbuf_len(cbuf), 1);
        cbuf_tail_next(cbuf);
    }
}

static void test__cbuf_len__returns_the_length_when_length_is_two(void **state)
{
    cbuf_init(cbuf);
    cbuf_push(cbuf, 0);
    for(int i = 0; i < 512; i++) {
        cbuf_push(cbuf, 0);
        assert_int_equal(cbuf_len(cbuf), 2);
        cbuf_tail_next(cbuf);
    }
}

static void test__cbuf_empty__returns_false_when_not_empty(void **state)
{
    cbuf_init(cbuf);
    cbuf_push(cbuf, 0);

    assert_false(cbuf_empty(cbuf));
}

static void test__cbuf_empty__returns_true_when_empty(void **state)
{
    cbuf_init(cbuf);

    for(int i = 0; i < 512; i++) {
        for(int j = 0; j < (i % cbuf_LEN); j++) {
            cbuf_push(cbuf, 0);
        }
        for(int j = 0; j < (i % cbuf_LEN); j++) {
            cbuf_tail_next(cbuf);
        }
        assert_true(cbuf_empty(cbuf));
    }
}

static void test__cbuf_push__and__cbuf_pop__works(void **state)
{
    cbuf_init(cbuf);

    for(int i = 0; i < 512; i++) {
        cbuf_push(cbuf, 0xAB);
        cbuf_push(cbuf, 0xCD);
        cbuf_push(cbuf, 0xEF);

        assert_int_equal(cbuf_pop(cbuf), 0xAB);
        assert_int_equal(cbuf_pop(cbuf), 0xCD);
        assert_int_equal(cbuf_pop(cbuf), 0xEF);
    }
}

static void test__cbuf__inline_functionality_works(void **state)
{
    cbuf_init(cbuf);

    for(int i = 0; i < 512; i++) {
        *cbuf_head(cbuf) = 0xAB;
        cbuf_head_next(cbuf);
        *cbuf_head(cbuf) = 0xCD;
        cbuf_head_next(cbuf);
        *cbuf_head(cbuf) = 0xEF;
        cbuf_head_next(cbuf);

        assert_int_equal(*cbuf_tail(cbuf), 0xAB);
        cbuf_tail_next(cbuf);
        assert_int_equal(*cbuf_tail(cbuf), 0xCD);
        cbuf_tail_next(cbuf);
        assert_int_equal(*cbuf_tail(cbuf), 0xEF);
        cbuf_tail_next(cbuf);
    }
}

static void test__cbuf_full__returns_true_when_full(void **state)
{
    cbuf_init(cbuf);

    for(int i = 0; i < cbuf_LEN; i++) {
        cbuf_push(cbuf, i);
    }

    assert_true(cbuf_full(cbuf));
}

static void test__cbuf_linear_len__works(void **state)
{
    uint8_t dummy __attribute__((unused));

    cbuf_init(cbuf);

    for(int i = 0; i < 3 * cbuf_LEN / 4; i++) {
        cbuf_push(cbuf, i);
    }

    assert_int_equal(cbuf_linear_len(cbuf), 3 * cbuf_LEN / 4);

    for(int i = 0; i < 3 * cbuf_LEN / 4; i++) {
        dummy = cbuf_pop(cbuf);
    }

    for(int i = 0; i < cbuf_LEN / 4; i++) {
        cbuf_push(cbuf, i);
    }

    assert_int_equal(cbuf_len(cbuf), cbuf_LEN / 4);
    assert_int_equal(cbuf_linear_len(cbuf), cbuf_LEN / 4);

    for(int i = 0; i < cbuf_LEN / 4; i++) {
        cbuf_push(cbuf, i);
    }

    assert_int_equal(cbuf_len(cbuf), cbuf_LEN / 2);
    assert_int_equal(cbuf_linear_len(cbuf), cbuf_LEN / 4);

    for(int i = 1; i <= cbuf_LEN / 4 - 1; i++) {
        printf("head = %02X tail = %02X len = %02X linear_len = %02X\n", cbuf.head, cbuf.tail, cbuf_len(cbuf), (unsigned) cbuf_linear_len(cbuf));
        dummy = cbuf_pop(cbuf);
        assert_int_equal(cbuf_linear_len(cbuf), cbuf_LEN / 4 - i);
    }

    printf("head = %02X tail = %02X len = %02X linear_len = %02X\n", cbuf.head, cbuf.tail, cbuf_len(cbuf), (unsigned) cbuf_linear_len(cbuf));
    dummy = cbuf_pop(cbuf);
    printf("head = %02X tail = %02X len = %02X linear_len = %02X\n", cbuf.head, cbuf.tail, cbuf_len(cbuf), (unsigned) cbuf_linear_len(cbuf));

    assert_int_equal(cbuf_len(cbuf), cbuf_LEN / 4);
    assert_int_equal(cbuf_linear_len(cbuf), cbuf_LEN / 4);
}


const struct CMUnitTest tests_for_cbuf[] = {
    cmocka_unit_test(test__cbuf_init__leaves_an_empty_buffer),
    cmocka_unit_test(test__cbuf_len__returns_the_length_when_length_is_one),
    cmocka_unit_test(test__cbuf_len__returns_the_length_when_length_is_two),
    cmocka_unit_test(test__cbuf_empty__returns_false_when_not_empty),
    cmocka_unit_test(test__cbuf_empty__returns_true_when_empty),
    cmocka_unit_test(test__cbuf_push__and__cbuf_pop__works),
    cmocka_unit_test(test__cbuf__inline_functionality_works),
    cmocka_unit_test(test__cbuf_full__returns_true_when_full),
    cmocka_unit_test(test__cbuf_linear_len__works),
};

//////// Main //////////////////////////////////////////////////////////////////


int main(void)
{
    int fails = 0;
    fails += cmocka_run_group_tests(tests_for_cbuf, NULL, NULL);

    return fails;
}
