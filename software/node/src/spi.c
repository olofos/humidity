#include "stm32l0xx.h"
#include "spi.h"

#define SPI_DUMMY 0x55

void spi_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    SPI1->CR1 = (0x0 << SPI_CR1_BR_Pos) | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI;
    SPI1->CR1 = (0x0 << SPI_CR1_BR_Pos) | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE;
}

static void spi_wait_for_txe(void)
{
    while(!(SPI1->SR & SPI_SR_TXE)) {
    }
}

static void spi_wait_for_rxne(void)
{
    while(!(SPI1->SR & SPI_SR_RXNE)) {
    }
}

static void spi_wait_for_busy(void)
{
    while(SPI1->SR & SPI_SR_BSY) {
    }
}

static uint8_t spi_receive(void)
{
    return SPI1->DR;
}

static void spi_send(uint8_t data)
{
    SPI1->DR = data;
}

void spi_deinit(void)
{
    spi_wait_for_rxne();
    spi_wait_for_txe();
    spi_wait_for_busy();

    uint32_t dummy __attribute__((unused)) = spi_receive();

    SPI1->CR1 = 0x00;
    RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
}

void spi_write_byte(uint8_t out) {
    spi_wait_for_txe();
    spi_send(out);

    spi_wait_for_rxne();
    uint32_t dummy __attribute__((unused)) = spi_receive();
}

uint8_t spi_read_byte(void)
{
    spi_wait_for_txe();

    spi_send(SPI_DUMMY);

    spi_wait_for_rxne();

    return spi_receive();
}

void spi_read(uint8_t *buf, uint32_t length)
{
    for(uint32_t i = 0; i < length; i++) {
        buf[i] = spi_read_byte();
    }
}

void spi_write(uint8_t *buf, uint32_t length)
{
    spi_wait_for_busy();

    for(uint32_t i = 0; i < length; i++) {
        spi_wait_for_txe();

        spi_send(buf[i]);
    }

    spi_wait_for_rxne();
    uint32_t dummy __attribute__((unused)) = spi_receive();
}
