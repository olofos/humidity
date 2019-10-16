#include <setjmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "spi-flash-cbuf.h"
#include "spi-flash.h"

//////// Helper Functions //////////////////////////////////////////////////////

extern uint16_t sf_cbuf_head;
extern uint16_t sf_cbuf_tail;

uint8_t spi_flash_buf[SPI_FLASH_CBUF_BUF_SIZE];

int setup(void **state)
{
    sf_cbuf_head = 0;
    sf_cbuf_tail = 0;
    memset(spi_flash_buf, 0xFF, sizeof(spi_flash_buf));
    return 0;
}

int teardown(void **state)
{
    return 0;
}

//////// Mocks /////////////////////////////////////////////////////////////////

void spi_flash_erase_page(uint32_t address)
{
    address &= ~(SPI_FLASH_PAGE_SIZE - 1);

    printf("Erasing page %04X\n", address);

    memset(&spi_flash_buf[address], 0xFF, SPI_FLASH_PAGE_SIZE);
}

void spi_flash_write_page(uint32_t address, uint8_t *buf, uint16_t length)
{
    for(int i = 0; i < length; i++) {
        spi_flash_buf[address + i] &= buf[i];
    }

    printf("Writing %d bytes to %04X:\n", length, address);
    for(int i = 0; i < length; i++) {
        printf("%04X: %02X %02X\n", address + i, buf[i], spi_flash_buf[address + i]);
    }
}

void spi_flash_read(uint32_t address, uint8_t *buf, uint32_t length)
{
    memcpy(buf, &spi_flash_buf[address], length);

    printf("Reading %d bytes from %04X:\n", length, address);
    for(int i = 0; i < length; i++) {
        printf("%04X: %02X\n", address + i, spi_flash_buf[address + i]);
    }
}


//////// Tests /////////////////////////////////////////////////////////////////

static void test__spi_flash_cbuf_len__returns_the_length_when_length_is_zero(void **state)
{
    assert_int_equal(sf_cbuf_len(), 0);
}

static void test__spi_flash_cbuf_len__returns_the_length_when_length_is_one(void **state)
{
    for(int i = 0; i < 512; i++) {
        uint8_t d = i & 0xFF;
        sf_cbuf_push(&d, 1);
        assert_int_equal(sf_cbuf_len(), 1);
        sf_cbuf_pop(&d, 1);
    }
}

static void test__spi_flash_cbuf_len__returns_the_length_when_length_is_two(void **state)
{
    uint8_t d = 0xAB;
    sf_cbuf_push(&d, 1);
    for(int i = 0; i < 512; i++) {
        sf_cbuf_push(&d, 1);
        assert_int_equal(sf_cbuf_len(), 2);
        sf_cbuf_pop(&d, 1);
    }
}

static void test__spi_flash_cbuf_empty__returns_false_when_not_empty(void **state)
{
    uint8_t d = 0xAB;
    sf_cbuf_push(&d, 1);

    assert_false(sf_cbuf_empty());
}


static void test__spi_flash_cbuf_empty__returns_true_when_empty(void **state)
{
    uint8_t d = 0xAB;
    for(int i = 0; i < 512; i++) {
        sf_cbuf_push(&d, 1);
        uint8_t dummy __attribute__((unused)) =  sf_cbuf_pop(&d, 1);
        assert_true(sf_cbuf_empty());
    }
}


static void test__spi_flash_cbuf_full__returns_true_when_full(void **state)
{
    uint8_t d;
    for(int i = 0; i < SPI_FLASH_CBUF_CAPACITY; i++) {
        assert_false(sf_cbuf_full());
        sf_cbuf_push(&d, 1);
    }

    assert_true(sf_cbuf_full());
}


static void test__spi_flash_cbuf_push__and__cbuf_pop__works(void **state)
{
    uint8_t w1[] = { 0x01, 0x23, 0x45, 0x67 };
    uint8_t w2[] = { 0x00 };
    uint8_t w3[] = { 0xDE, 0xAD, 0xC0, 0xFF, 0xEE, 0xBE, 0xEF };

    uint8_t r[SPI_FLASH_CBUF_RECORD_SIZE];

    for(int i = 0; i < 2 * SPI_FLASH_CBUF_CAPACITY; i++) {
    // for(int i = 0; i < 2 ; i++) {
        uint8_t len;

        len = sf_cbuf_push(w1, sizeof(w1));
        assert_int_equal(len, sizeof(w1));

        len = sf_cbuf_push(w2, sizeof(w2));
        assert_int_equal(len, sizeof(w2));

        len = sf_cbuf_push(w3, sizeof(w3));
        assert_int_equal(len, sizeof(w3));


        len = sf_cbuf_pop(r, sizeof(r));
        assert_int_equal(len, sizeof(w1));
        assert_memory_equal(w1, r, sizeof(w1));

        len = sf_cbuf_pop(r, sizeof(r));
        assert_int_equal(len, sizeof(w2));
        assert_memory_equal(w2, r, sizeof(w2));

        len = sf_cbuf_pop(r, sizeof(r));
        assert_int_equal(len, sizeof(w3));
        assert_memory_equal(w3, r, sizeof(w3));
    }
}

const struct CMUnitTest tests_for_spi_flash_cbuf[] = {
    cmocka_unit_test_setup_teardown(test__spi_flash_cbuf_len__returns_the_length_when_length_is_zero, setup, teardown),
    cmocka_unit_test_setup_teardown(test__spi_flash_cbuf_len__returns_the_length_when_length_is_one, setup, teardown),
    cmocka_unit_test_setup_teardown(test__spi_flash_cbuf_len__returns_the_length_when_length_is_two, setup, teardown),
    cmocka_unit_test_setup_teardown(test__spi_flash_cbuf_empty__returns_false_when_not_empty, setup, teardown),
    cmocka_unit_test_setup_teardown(test__spi_flash_cbuf_empty__returns_true_when_empty, setup, teardown),
    cmocka_unit_test_setup_teardown(test__spi_flash_cbuf_full__returns_true_when_full, setup, teardown),
    cmocka_unit_test_setup_teardown(test__spi_flash_cbuf_push__and__cbuf_pop__works, setup, teardown),
};

//////// Main //////////////////////////////////////////////////////////////////


int main(void)
{
    int fails = 0;
    fails += cmocka_run_group_tests(tests_for_spi_flash_cbuf, NULL, NULL);

    return fails;
}
