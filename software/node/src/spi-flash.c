#include <stdint.h>

#include "stm32l0xx.h"
#include "spi.h"
#include "spi-flash.h"

#define SPI_FLASH_CMD_READ_ARRAY            0x03

#define SPI_FLASH_CMD_PAGE_ERASE            0x81
#define SPI_FLASH_CMD_BLOCK_ERASE_4K        0x20
#define SPI_FLASH_CMD_BLOCK_ERASE_32K       0x52
#define SPI_FLASH_CMD_CHIP_ERASE            0x60
#define SPI_FLASH_CMD_PAGE_PROGRAM          0x02

#define SPI_FLASH_CMD_WRITE_ENABLE          0x06
#define SPI_FLASH_CMD_WRITE_DISABLE         0x04

#define SPI_FLASH_CMD_PROGRAM_OTP           0x9B
#define SPI_FLASH_CMD_READ_OTP              0x77

#define SPI_FLASH_CMD_READ_STATUS           0x05
#define SPI_FLASH_CMD_WRITE_STATUS_1        0x01
#define SPI_FLASH_CMD_WRITE_STATUS_2        0x31

#define SPI_FLASH_CMD_RESET                 0xF0
#define SPI_FLASH_CMD_READ_ID               0x9F
#define SPI_FLASH_CMD_DEEP_POWER_DOWN       0xB9
#define SPI_FLASH_CMD_RESUME_DEEP_DOWN      0xAB
#define SPI_FLASH_CMD_ULTRA_DEEP_POWER_DOWN 0x79


#define SPI_FLASH_STATUS_BPL 0x80
#define SPI_FLASH_STATUS_EPE 0x20
#define SPI_FLASH_STATUS_WPP 0x10
#define SPI_FLASH_STATUS_BP0 0x04
#define SPI_FLASH_STATUS_WEL 0x02
#define SPI_FLASH_STATUS_BSY 0x01


static inline void spi_flash_cs_assert(void)
{
    GPIOB->BSRR = GPIO_BSRR_BR_0;
}

static inline void spi_flash_cs_deassert(void)
{
    GPIOB->BSRR = GPIO_BSRR_BS_0;
}

static void spi_flash_write_enable(void)
{
    spi_flash_cs_assert();
    spi_write_byte(SPI_FLASH_CMD_WRITE_ENABLE);
    spi_flash_cs_deassert();
}

static void spi_flash_wait_until_ready(void)
{
    spi_flash_cs_assert();

    spi_write_byte(SPI_FLASH_CMD_READ_STATUS);

    uint8_t status;

    do {
        status = spi_read_byte();
    } while(status & SPI_FLASH_STATUS_BSY);

    spi_flash_cs_deassert();
}

void spi_flash_erase_page(uint32_t address)
{
    const uint8_t address_hi  = (address & 0x00FF0000) >> 16;
    const uint8_t address_mid = (address & 0x0000FF00) >> 8;
    const uint8_t address_low = (address & 0x000000FF);

    spi_flash_write_enable();

    spi_flash_cs_assert();

    uint8_t cmd[] = { SPI_FLASH_CMD_PAGE_ERASE, address_hi, address_mid, address_low };

    spi_write(cmd, sizeof(cmd));

    spi_flash_cs_deassert();

    spi_flash_wait_until_ready();
}

void spi_flash_write_page(uint32_t address, uint8_t *buf, uint16_t length)
{
    const uint8_t address_hi  = (address & 0x00FF0000) >> 16;
    const uint8_t address_mid = (address & 0x0000FF00) >> 8;
    const uint8_t address_low = (address & 0x000000FF);

    spi_flash_write_enable();

    spi_flash_cs_assert();

    uint8_t cmd[] = { SPI_FLASH_CMD_PAGE_PROGRAM, address_hi, address_mid, address_low };

    spi_write(cmd, sizeof(cmd));

    spi_write(buf, length);

    spi_flash_cs_deassert();

    spi_flash_wait_until_ready();
}

void spi_flash_read(uint32_t address, uint8_t *buf, uint32_t length)
{
    const uint8_t address_hi  = (address & 0x00FF0000) >> 16;
    const uint8_t address_mid = (address & 0x0000FF00) >> 8;
    const uint8_t address_low = (address & 0x000000FF);

    spi_flash_cs_assert();

    uint8_t cmd[] = { SPI_FLASH_CMD_READ_ARRAY, address_hi, address_mid, address_low };

    spi_write(cmd, sizeof(cmd));

    spi_read(buf, length);

    spi_flash_cs_deassert();
}

uint32_t spi_flash_read_id(void)
{
    spi_flash_cs_assert();

    spi_write_byte(SPI_FLASH_CMD_READ_ID);

    uint8_t buf[3];

    spi_read(buf, sizeof(buf));

    spi_flash_cs_deassert();

    return (buf[0] << 16) | (buf[1] << 8) | buf[2];
}

int spi_flash_test(void)
{
    return spi_flash_read_id() != 0;
}

void spi_flash_sleep(void)
{
    spi_flash_cs_assert();

    spi_write_byte(SPI_FLASH_CMD_ULTRA_DEEP_POWER_DOWN);

    spi_flash_cs_deassert();
}

void spi_flash_wakeup(void)
{
    spi_flash_cs_assert();

    // Write a dummy byte to waste some time waiting for flash to wake up
    spi_write_byte(SPI_FLASH_CMD_READ_STATUS);

    spi_flash_cs_deassert();
}
