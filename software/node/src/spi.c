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

uint8_t spi_transfer(uint8_t out)
{
    while(!(SPI1->SR & SPI_SR_TXE)) {
    }

    SPI1->DR = out;

    while(!(SPI1->SR & SPI_SR_RXNE)) {
    }

    uint8_t in = SPI1->DR;
    return in;
}
