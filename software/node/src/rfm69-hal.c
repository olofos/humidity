#include "stm32l0xx.h"
#include "spi.h"
#include "rfm69-hal.h"
#include "rfm69-registers.h"
#include "systick.h"
#include "gpio.h"

static void rfm69_cs_assert(void)
{
    GPIOA->BSRR = GPIO_BSRR_BR_4;
}

static void rfm69_cs_deassert(void)
{
    GPIOA->BSRR = GPIO_BSRR_BS_4;
}


void rfm69_write_byte(uint8_t reg, uint8_t val)
{
    rfm69_cs_assert();

    spi_write_byte(reg | RFM69_REG_WRITE);
    spi_write_byte(val);

    rfm69_cs_deassert();
}

void rfm69_write(uint8_t reg, uint8_t *buf, uint8_t len)
{
    rfm69_cs_assert();

    spi_write_byte(reg | RFM69_REG_WRITE);
    spi_write(buf, len);

    rfm69_cs_deassert();
}

uint8_t rfm69_read_byte(uint8_t reg)
{
    rfm69_cs_assert();

    spi_write_byte(reg | RFM69_REG_READ);
    uint8_t val = spi_read_byte();

    rfm69_cs_deassert();

    return val;
}

void rfm69_read(uint8_t reg, uint8_t *buf, uint8_t len)
{
    rfm69_cs_assert();

    spi_write_byte(reg | RFM69_REG_READ);
    spi_read(buf, len);

    rfm69_cs_deassert();
}

void rfm69_fifo_write_begin(void)
{
    rfm69_cs_assert();
    spi_write_byte(RFM69_REG_FIFO | RFM69_REG_WRITE);
}

void rfm69_fifo_write_byte(uint8_t val)
{
    spi_write_byte(val);
}

void rfm69_fifo_write(uint8_t *buf, uint8_t len)
{
    spi_write(buf, len);
}

void rfm69_fifo_write_end(void)
{
    rfm69_cs_deassert();
}

void rfm69_fifo_read_begin(void)
{
    rfm69_cs_assert();
    spi_write_byte(RFM69_REG_FIFO | RFM69_REG_READ);
}

uint8_t rfm69_fifo_read_byte(void)
{
    return spi_read_byte();
}

void rfm69_fifo_read(uint8_t *buf, uint8_t len)
{
    spi_read(buf, len);
}

void rfm69_fifo_read_end(void)
{
    rfm69_cs_deassert();
}

int rfm69_wait_for_packet(void)
{
    uint32_t start = systick;

    while((systick - start) < 2000) {
        if(rfm69_read_byte(RFM69_REG_IRQ_FLAGS2) & RFM69_IRQ2_PAYLOAD_READY) {
            return 1;
        }
    }

    return 0;
}
