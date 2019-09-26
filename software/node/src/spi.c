#include "stm32l0xx.h"
#include "spi.h"
#include <stdio.h>

void spi_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    SPI1->CR1 = (0x0 << SPI_CR1_BR_Pos) | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI;
    SPI1->CR1 = (0x0 << SPI_CR1_BR_Pos) | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE;
}

static void spi_wait_for(const uint32_t flag)
{
    while(!(SPI1->SR & flag)) {
    }
}

static void spi_wait_for_busy(void)
{
    while(SPI1->SR & SPI_SR_BSY) {
    }
}

void spi_deinit(void)
{
    spi_wait_for(SPI_SR_RXNE);
    spi_wait_for(SPI_SR_TXE);
    spi_wait_for_busy();

    uint32_t dummy __attribute__((unused)) = SPI1->DR;

    SPI1->CR1 = 0x00;
    RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
}

void spi_write_byte(uint8_t out) {
    spi_wait_for(SPI_SR_TXE);
    SPI1->DR = out;

    spi_wait_for(SPI_SR_RXNE);
    uint32_t dummy __attribute__((unused)) = SPI1->DR;
}

uint8_t spi_read_byte(void)
{
    spi_wait_for(SPI_SR_TXE);

    SPI1->DR = 0xFF;

    spi_wait_for(SPI_SR_RXNE);

    return SPI1->DR;
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
        spi_wait_for(SPI_SR_TXE);

        SPI1->DR = buf[i];
    }

    spi_wait_for(SPI_SR_RXNE);
    uint32_t dummy __attribute__((unused)) = SPI1->DR;
}
