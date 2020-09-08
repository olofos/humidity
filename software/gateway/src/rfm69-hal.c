#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <linux/types.h>
#include <linux/spi/spidev.h>

#include <time.h>

#include <gpiod.h>

#include "rfm69.h"
#include "rfm69-hal.h"
#include "rfm69-registers.h"


int spi = -1;
struct gpiod_chip *chip;
struct gpiod_line *int_line;

void rfm69_hal_init(void)
{
    chip = gpiod_chip_open("/dev/gpiochip0");

    if(!chip) {
        perror("gpiod_chip_open");
    }

    int_line = gpiod_chip_get_line(chip, 23);
    if(!int_line) {
        perror("gpiod_chip_get_line");
    }

    if(gpiod_line_request_rising_edge_events(int_line, "gateway") < 0) {
        perror("gpiod_line_request_rising_edge_events");
    }

    spi = open("/dev/spidev0.0", O_RDWR);

    if (spi < 0) {
        perror("open");
        return;
    }

    uint32_t max_speed = 1000000;

    ioctl(spi, SPI_IOC_WR_MAX_SPEED_HZ, &max_speed);
}

void rfm69_hal_deinit(void)
{
    if(spi > 0) {
        rfm69_set_mode(RFM69_MODE_SLEEP);
        close(spi);
    }
    if(int_line) gpiod_line_release(int_line);
    if(chip) gpiod_chip_close(chip);
}

void rfm69_hal_write_byte(uint8_t reg, uint8_t val)
{
    uint8_t tx_buf[] = { reg | RFM69_REG_WRITE, val, };
    struct spi_ioc_transfer xfer[] = {
        {
            .tx_buf = (uint32_t) &tx_buf,
            .len = sizeof(tx_buf),
        },
    };
    int status = ioctl(spi, SPI_IOC_MESSAGE(1), xfer);
    if (status < 0) {
        perror("SPI_IOC_MESSAGE");
    }
}

void rfm69_hal_write(uint8_t reg, const uint8_t *buf, uint8_t len)
{
    uint8_t tx_buf[] = { reg | RFM69_REG_WRITE };
    struct spi_ioc_transfer xfer[] = {
        {
            .tx_buf = (uint32_t) &tx_buf,
            .len = sizeof(tx_buf),
        },
        {
            .tx_buf = (uint32_t) buf,
            .len = len,
        },
    };
    int status = ioctl(spi, SPI_IOC_MESSAGE(2), xfer);
    if (status < 0) {
        perror("SPI_IOC_MESSAGE");
    }
}

uint8_t rfm69_hal_read_byte(uint8_t reg)
{
    uint8_t tx_buf[] = { reg | RFM69_REG_READ };
    uint8_t rx_buf[1];

    struct spi_ioc_transfer xfer[] = {
        {
            .tx_buf = (uint32_t) &tx_buf,
            .len = sizeof(tx_buf),
        },
        {
            .rx_buf = (uint32_t) rx_buf,
            .len = sizeof(rx_buf),
        },
    };
    int status = ioctl(spi, SPI_IOC_MESSAGE(2), xfer);
    if (status < 0) {
        perror("SPI_IOC_MESSAGE");
    }

    return rx_buf[0];
}

void rfm69_hal_read(uint8_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t tx_buf[] = { reg | RFM69_REG_READ };

    struct spi_ioc_transfer xfer[] = {
        {
            .tx_buf = (uint32_t) &tx_buf,
            .len = sizeof(tx_buf),
        },
        {
            .rx_buf = (uint32_t) buf,
            .len = len,
        },
    };
    int status = ioctl(spi, SPI_IOC_MESSAGE(2), xfer);
    if (status < 0) {
        perror("SPI_IOC_MESSAGE");
    }
}


static int rfm69_wait_for_interrupt(const struct timespec *timeout)
{
    int ret = gpiod_line_event_wait(int_line, timeout);

    if(ret > 0) {
        struct gpiod_line_event event;
        if(gpiod_line_event_read(int_line, &event) < 0) {
            perror("gpiod_line_event_read");
        }
    }

    return ret;
}

int rfm69_wait_for_payload_ready(void)
{
    const struct timespec timeout = {
        .tv_sec = 30,
        .tv_nsec = 0,
    };

    return rfm69_wait_for_interrupt(&timeout);
}


int rfm69_wait_for_packet_sent(void)
{
    const struct timespec timeout = {
        .tv_sec = 0,
        .tv_nsec = 500000000,
    };

    return rfm69_wait_for_interrupt(&timeout);
}
