#define _XOPEN_SOURCE
#define  _POSIX_C_SOURCE 200112L

#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <cmocka.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>

#include "spi.h"

//////// Helper Functions //////////////////////////////////////////////////////

void spi_wait_for_txe(void)
{
}

void spi_wait_for_rxne(void)
{
}

void spi_wait_for_busy(void)
{
}

uint8_t spi_receive(void)
{
    return mock();
}

void spi_send(uint8_t data)
{
    check_expected(data);
}


//////// Tests /////////////////////////////////////////////////////////////////

static void test__spi_write_byte__writes_a_single_byte(void **states)
{
    expect_value(spi_send, data, 0xAB);
    will_return_maybe(spi_receive, 0x00);

    spi_write_byte(0xAB);
}

static void test__spi_read_byte__reads_a_single_byte(void **states)
{
    expect_any(spi_send, data);
    will_return(spi_receive, 0xAB);

    assert_int_equal(spi_read_byte(), 0xAB);
}

static void test__spi_write__writes_the_correct_number_of_bytes(void **states)
{
    expect_value(spi_send, data, 0x01);
    expect_value(spi_send, data, 0x02);
    expect_value(spi_send, data, 0x03);
    expect_value(spi_send, data, 0x04);

    will_return_maybe(spi_receive, 0x00);

    uint8_t buf[] = {1,2,3,4};
    spi_write(buf, sizeof(buf));
}

static void test__spi_read__reads_the_correct_number_of_bytes(void **states)
{
    expect_any_count(spi_send, data, 4);

    will_return(spi_receive, 0x01);
    will_return(spi_receive, 0x02);
    will_return(spi_receive, 0x03);
    will_return(spi_receive, 0x04);

    uint8_t buf[] = {0,0,0,0};
    spi_read(buf, sizeof(buf));

    assert_int_equal(buf[0], 0x01);
}

static void test__spi_write__reads_the_correct_number_of_bytes(void **states)
{
    expect_value(spi_send, data, 0x01);
    expect_value(spi_send, data, 0x02);
    expect_value(spi_send, data, 0x03);
    expect_value(spi_send, data, 0x04);

    will_return_count(spi_receive, 0x00, 4);

    uint8_t buf[] = {1,2,3,4};
    spi_write(buf, sizeof(buf));
}


const struct CMUnitTest tests_for_spi[] = {
    cmocka_unit_test(test__spi_write_byte__writes_a_single_byte),
    cmocka_unit_test(test__spi_read_byte__reads_a_single_byte),
    cmocka_unit_test(test__spi_write__writes_the_correct_number_of_bytes),
    cmocka_unit_test(test__spi_read__reads_the_correct_number_of_bytes),
    cmocka_unit_test(test__spi_write__reads_the_correct_number_of_bytes),
};

//////// Main //////////////////////////////////////////////////////////////////

int main(void)
{
    int fails = 0;
    fails += cmocka_run_group_tests(tests_for_spi, NULL, NULL);

    return fails;
}
