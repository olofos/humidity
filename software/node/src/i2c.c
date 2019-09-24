#include <stdint.h>

#include "stm32l0xx.h"
#include "i2c.h"
#include "systick.h"


void i2c_init(void)
{
    RCC->CCIPR &= ~(RCC_CCIPR_I2C1SEL_0 | RCC_CCIPR_I2C1SEL_1);
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    I2C1->TIMINGR = (0UL << I2C_TIMINGR_PRESC_Pos) | (0UL << I2C_TIMINGR_SCLDEL_Pos) | (0UL << I2C_TIMINGR_SDADEL_Pos) | (8UL << I2C_TIMINGR_SCLH_Pos) | (9UL << I2C_TIMINGR_SCLL_Pos);
    I2C1->CR1 = I2C_CR1_PE;
}

void i2c_deinit(void)
{
    I2C1->CR1 = 0;
    RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN;
}

static int i2c_check_nackf(uint32_t start, uint32_t timeout)
{
    if(I2C1->ISR & I2C_ISR_NACKF) {
        while(!(I2C1->ISR & I2C_ISR_STOPF)) {
            if(systick - start >= timeout) break;
        }

        I2C1->ICR = I2C_ICR_STOPCF | I2C_ICR_NACKCF;
        I2C1->CR2 = 0;

        return I2C_ERROR;
    }

    return I2C_OK;
}

static int i2c_wait_for_txis(uint32_t start, uint32_t timeout)
{
    while(!(I2C1->ISR & I2C_ISR_TXIS)) {
        if(i2c_check_nackf(start, timeout) == I2C_ERROR) return I2C_ERROR;
        if(systick - start >= timeout) return I2C_ERROR;
    }
    return I2C_OK;
}

static int i2c_wait_for_tc(uint32_t start, uint32_t timeout)
{
    while(!(I2C1->ISR & I2C_ISR_TC)) {
        if(i2c_check_nackf(start, timeout) == I2C_ERROR) return I2C_ERROR;
        if(systick - start >= timeout) return I2C_ERROR;
    }
    return I2C_OK;
}

static int i2c_wait_for_stop(uint32_t start, uint32_t timeout)
{
    while(!(I2C1->ISR & I2C_ISR_STOPF)) {
        if(i2c_check_nackf(start, timeout) == I2C_ERROR) return I2C_ERROR;
        if(systick - start >= timeout) return I2C_ERROR;
    }
    return I2C_OK;
}

static int i2c_wait_for_rxne(uint32_t start, uint32_t timeout)
{
    while(!(I2C1->ISR & I2C_ISR_RXNE)) {
        if(i2c_check_nackf(start, timeout) == I2C_ERROR) return I2C_ERROR;

        if(I2C1->ISR & I2C_ISR_STOPF) {
            if(I2C1->ISR & I2C_ISR_RXNE) {
                return I2C_OK;
            }
            I2C1->ICR = I2C_ICR_STOPCF;
            I2C1->CR2 = 0;
            return I2C_ERROR;
        }

        if(systick - start >= timeout) return I2C_ERROR;
    }

    return I2C_OK;
}

int i2c_check(uint8_t i2c_address, uint32_t start, uint32_t timeout)
{
    I2C1->CR2 = (i2c_address << 1) | (0 << I2C_CR2_NBYTES_Pos)  | I2C_CR2_AUTOEND | I2C_CR2_START;

    if(i2c_wait_for_stop(start, timeout)) {
        I2C1->ICR = I2C_ICR_STOPCF;
        I2C1->CR2 = 0;
        return I2C_OK;
    } else {
        return I2C_ERROR;
    }
}

int i2c_register_read(uint8_t i2c_address, uint16_t reg, uint8_t *buf, uint8_t num, uint32_t start, uint32_t timeout)
{
    I2C1->CR2 = (i2c_address << 1) | (2 << I2C_CR2_NBYTES_Pos)  | (0 << I2C_CR2_RD_WRN_Pos) | I2C_CR2_START;

    if(!i2c_wait_for_txis(start, timeout)) return I2C_ERROR;

    I2C1->TXDR = (reg >> 8) & 0xFF;

    if(!i2c_wait_for_txis(start, timeout)) return I2C_ERROR;

    I2C1->TXDR = reg & 0xFF;

    if(!i2c_wait_for_tc(start, timeout)) return I2C_ERROR;

    I2C1->CR2 = (i2c_address << 1) | (num << I2C_CR2_NBYTES_Pos)  | (1 << I2C_CR2_RD_WRN_Pos) | I2C_CR2_AUTOEND | I2C_CR2_START;

    for(int i = 0; i < num; i++) {
        if(!i2c_wait_for_rxne(start, timeout)) return I2C_ERROR;

        buf[i] = I2C1->RXDR;
    }

    if(!i2c_wait_for_stop(start, timeout)) return I2C_ERROR;

    I2C1->ICR = I2C_ICR_STOPCF;
    I2C1->CR2 = 0;

    return I2C_OK;
}


int i2c_register_write(uint8_t i2c_address, uint16_t reg, uint8_t *buf, uint8_t num, uint32_t start, uint32_t timeout)
{
    I2C1->CR2 = (i2c_address << 1) | ((num + 2) << I2C_CR2_NBYTES_Pos)  | (0 << I2C_CR2_RD_WRN_Pos) | I2C_CR2_AUTOEND | I2C_CR2_START;

    if(!i2c_wait_for_txis(start, timeout)) return I2C_ERROR;

    I2C1->TXDR = (reg >> 8) & 0xFF;

    if(!i2c_wait_for_txis(start, timeout)) return I2C_ERROR;

    I2C1->TXDR = reg & 0xFF;

    for(int i = 0; i < num; i++) {
        if(!i2c_wait_for_txis(start, timeout)) return I2C_ERROR;
        I2C1->TXDR = buf[i];
    }

    if(!i2c_wait_for_stop(start, timeout)) return I2C_ERROR;

    I2C1->ICR = I2C_ICR_STOPCF;
    I2C1->CR2 = 0;

    return I2C_OK;
}
