#include "stm32l0xx.h"
#include "spi.h"

void spi_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    SPI1->CR1 = (0x0 << SPI_CR1_BR_Pos) | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI;
    SPI1->CR1 = (0x0 << SPI_CR1_BR_Pos) | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE;
}

void spi_deinit(void)
{
    SPI1->CR1 = 0x00;
    RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
}

void spi_write(uint8_t out) {
    while(!(SPI1->SR & SPI_SR_TXE)) {
    }

    SPI1->DR = out;
}

uint8_t spi_read(void) {
    // Read DR to clear SPI_SR_RXNE

    uint32_t dummy = SPI1->DR;

    while(!(SPI1->SR & SPI_SR_TXE)) {
    }

    // Reusing previously read value saves a load
    SPI1->DR = dummy;

    while(!(SPI1->SR & SPI_SR_RXNE)) {
    }

    return SPI1->DR;
}
