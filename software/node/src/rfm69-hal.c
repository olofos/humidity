#include "stm32l0xx.h"
#include "spi.h"
#include "rfm69-hal.h"
#include "rfm69-registers.h"
#include "systick.h"
#include "gpio.h"

#define TIMEOUT_MS 250

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

void rfm69_hal_write(uint8_t reg, const uint8_t *buf, uint8_t len)
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

int rfm69_wait_for_interrupt(uint32_t timeout)
{
    uint32_t start = systick;
    int result = 0;

    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MASK << 16)) | (GPIO_MODER_INPUT << 16);
    while((systick - start) < timeout) {
        if(GPIOA->IDR & (1 << 8)) {
            result = 1;
            break;
        }
    }

    GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MASK << 16)) | (GPIO_MODER_ANALOG << 16);
    return result;
}

int rfm69_wait_for_payload_ready(void)
{
    return rfm69_wait_for_interrupt(TIMEOUT_MS);
}

int rfm69_wait_for_packet_sent(void)
{
    return rfm69_wait_for_interrupt(TIMEOUT_MS);
}
