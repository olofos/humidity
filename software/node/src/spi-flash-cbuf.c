#include <stdint.h>

#include "spi-flash-cbuf.h"
#include "spi-flash.h"

uint16_t sf_cbuf_head;
uint16_t sf_cbuf_tail;

static uint16_t sf_cbuf_head_address(void)
{
    return SPI_FLASH_CBUF_RECORD_SIZE * (sf_cbuf_head & (SPI_FLASH_CBUF_CAPACITY - 1));
}

static uint16_t sf_cbuf_tail_address(void)
{
    return SPI_FLASH_CBUF_RECORD_SIZE * (sf_cbuf_tail & (SPI_FLASH_CBUF_CAPACITY - 1));
}

uint16_t sf_cbuf_len(void)
{
    return sf_cbuf_head - sf_cbuf_tail;
}

int sf_cbuf_empty(void)
{
    return sf_cbuf_len() == 0;
}

int sf_cbuf_full(void)
{
    return sf_cbuf_len() == SPI_FLASH_CBUF_CAPACITY;
}

int sf_cbuf_push(uint8_t *data, uint8_t len)
{
    if(len > 63) len = 63;

    if((sf_cbuf_head_address() & (SPI_FLASH_PAGE_SIZE - 1)) == 0) {
        spi_flash_erase_page(sf_cbuf_head_address());
    }

    spi_flash_write_page(sf_cbuf_head_address(), &len, 1);
    spi_flash_write_page(sf_cbuf_head_address() + 1, data, len);

    sf_cbuf_head++;

    return len;
}

int sf_cbuf_read(uint8_t *data, uint8_t len)
{
    uint8_t saved_len;

    spi_flash_read(sf_cbuf_tail_address(), &saved_len, 1);

    if(len > saved_len) len = saved_len;

    spi_flash_read(sf_cbuf_tail_address() + 1, data, len);

    return len;
}

void sf_cbuf_pop(void)
{
    sf_cbuf_tail++;
}
