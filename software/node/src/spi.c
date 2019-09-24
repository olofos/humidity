#include "stm32l0xx.h"
#include "spi.h"
#include <stdio.h>

void spi_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    SPI1->CR1 = (0x0 << SPI_CR1_BR_Pos) | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI;
    SPI1->CR1 = (0x0 << SPI_CR1_BR_Pos) | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE;
}

void spi_deinit(void)
{
    while(!(SPI1->SR & SPI_SR_RXNE)) {
    }

    while(!(SPI1->SR & SPI_SR_TXE)) {
    }

    while(!(SPI1->SR & SPI_SR_BSY)) {
    }

    uint32_t dummy __attribute__((unused)) = SPI1->DR;

    SPI1->CR1 = 0x00;
    RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
}

void spi_write_byte(uint8_t out) {
    while(!(SPI1->SR & SPI_SR_TXE)) {
    }

    SPI1->DR = out;

    while(!(SPI1->SR & SPI_SR_RXNE)) {
    }
    uint32_t dummy __attribute__((unused)) = SPI1->DR;
}

uint8_t spi_read_byte(void)
{
    while(!(SPI1->SR & SPI_SR_TXE)) {
    }

    SPI1->DR = 0xFF;

    while(!(SPI1->SR & SPI_SR_RXNE)) {
    }

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
    while(SPI1->SR & SPI_SR_BSY) ;

    for(uint32_t i = 0; i < length; i++) {
        while(!(SPI1->SR & SPI_SR_TXE)) {
        }

        SPI1->DR = buf[i];
    }

    while(!(SPI1->SR & SPI_SR_RXNE)) {
    }
    uint32_t dummy __attribute__((unused)) = SPI1->DR;
}
