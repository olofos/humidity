#include "stm32l0xx.h"
#include "spi.h"
#include "rfm69-hal.h"
#include "rfm69-registers.h"
#include "systick.h"
#include "gpio.h"

void rfm69_hal_init(void)
{
}

void rfm69_hal_deinit(void)
{
}

static void rfm69_cs_assert(void)
{
    GPIOA->BSRR = GPIO_BSRR_BR_4;
}

static void rfm69_cs_deassert(void)
{
    GPIOA->BSRR = GPIO_BSRR_BS_4;
}


void rfm69_hal_write_byte(uint8_t reg, uint8_t val)
{
    rfm69_cs_assert();

    spi_write_byte(reg | RFM69_REG_WRITE);
    spi_write_byte(val);

    rfm69_cs_deassert();
}

void rfm69_hal_write(uint8_t reg, uint8_t *buf, uint8_t len)
{
    rfm69_cs_assert();

    spi_write_byte(reg | RFM69_REG_WRITE);
    spi_write(buf, len);

    rfm69_cs_deassert();
}

uint8_t rfm69_hal_read_byte(uint8_t reg)
{
    rfm69_cs_assert();

    spi_write_byte(reg | RFM69_REG_READ);
    uint8_t val = spi_read_byte();

    rfm69_cs_deassert();

    return val;
}

void rfm69_hal_read(uint8_t reg, uint8_t *buf, uint8_t len)
{
    rfm69_cs_assert();

    spi_write_byte(reg | RFM69_REG_READ);
    spi_read(buf, len);

    rfm69_cs_deassert();
}

int rfm69_wait_for_payload_ready(void)
{
    uint32_t start = systick;

    while((systick - start) < 2000) {
        if(rfm69_hal_read_byte(RFM69_REG_IRQ_FLAGS2) & RFM69_IRQ2_PAYLOAD_READY) {
            return 1;
        }
    }

    return 0;
}


int rfm69_wait_for_packet_sent(void)
{
    uint32_t start = systick;

    while((systick - start) < 2000) {
        if(rfm69_hal_read_byte(RFM69_REG_IRQ_FLAGS2) & RFM69_IRQ2_PACKET_SENT) {
            return 1;
        }
    }

    return 0;
}
