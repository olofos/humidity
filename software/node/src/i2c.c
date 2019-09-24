#include <stdint.h>

#include "stm32l0xx.h"
#include "i2c.h"


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

static int i2c_check_nackf(void)
{
    if(I2C1->ISR & I2C_ISR_NACKF) {
        while(!(I2C1->ISR & I2C_ISR_STOPF)) {
        }

        I2C1->ICR = I2C_ICR_STOPCF | I2C_ICR_NACKCF;
        I2C1->CR2 = 0;

        return I2C_ERROR;
    }

    return I2C_OK;
}

static int i2c_wait_for_txis(void)
{
    while(!(I2C1->ISR & I2C_ISR_TXIS)) {
        if(i2c_check_nackf() == I2C_ERROR) return I2C_ERROR;
    }
    return I2C_OK;
}

static int i2c_wait_for_tc(void)
{
    while(!(I2C1->ISR & I2C_ISR_TC)) {
        if(i2c_check_nackf() == I2C_ERROR) return I2C_ERROR;
    }
    return I2C_OK;
}

static int i2c_wait_for_stop(void)
{
    while(!(I2C1->ISR & I2C_ISR_STOPF)) {
        if(i2c_check_nackf() == I2C_ERROR) return I2C_ERROR;
    }
    return I2C_OK;
}

static int i2c_wait_for_rxne(void)
{
    while(!(I2C1->ISR & I2C_ISR_RXNE)) {
        if(i2c_check_nackf() == I2C_ERROR) return I2C_ERROR;

        if(I2C1->ISR & I2C_ISR_STOPF) {
            if(I2C1->ISR & I2C_ISR_RXNE) {
                return I2C_OK;
            }
            I2C1->ICR = I2C_ICR_STOPCF;
            I2C1->CR2 = 0;
            return I2C_ERROR;
        }
    }

    return I2C_OK;
}

int i2c_check(uint8_t i2c_address)
{
    I2C1->CR2 = (i2c_address << 1) | (0 << I2C_CR2_NBYTES_Pos)  | I2C_CR2_AUTOEND | I2C_CR2_START;

    if(i2c_wait_for_stop()) {
        I2C1->ICR = I2C_ICR_STOPCF;
        I2C1->CR2 = 0;
        return I2C_OK;
    } else {
        return I2C_ERROR;
    }
}

int i2c_register_read(uint8_t i2c_address, uint16_t reg, uint8_t *buf, uint8_t num)
{
    I2C1->CR2 = (i2c_address << 1) | (2 << I2C_CR2_NBYTES_Pos)  | (0 << I2C_CR2_RD_WRN_Pos) | I2C_CR2_START;

    if(!i2c_wait_for_txis()) return I2C_ERROR;

    I2C1->TXDR = (reg >> 8) & 0xFF;

    if(!i2c_wait_for_txis()) return I2C_ERROR;

    I2C1->TXDR = reg & 0xFF;

    if(!i2c_wait_for_tc()) return I2C_ERROR;

    I2C1->CR2 = (i2c_address << 1) | (num << I2C_CR2_NBYTES_Pos)  | (1 << I2C_CR2_RD_WRN_Pos) | I2C_CR2_AUTOEND | I2C_CR2_START;

    for(int i = 0; i < num; i++) {
        if(!i2c_wait_for_rxne()) return I2C_ERROR;

        buf[i] = I2C1->RXDR;
    }

    if(!i2c_wait_for_stop()) return I2C_ERROR;

    I2C1->ICR = I2C_ICR_STOPCF;
    I2C1->CR2 = 0;

    return I2C_OK;
}


int i2c_register_write(uint8_t i2c_address, uint16_t reg, uint8_t *buf, uint8_t num)
{
    I2C1->CR2 = (i2c_address << 1) | ((num + 2) << I2C_CR2_NBYTES_Pos)  | (0 << I2C_CR2_RD_WRN_Pos) | I2C_CR2_AUTOEND | I2C_CR2_START;

    if(!i2c_wait_for_txis()) return I2C_ERROR;

    I2C1->TXDR = (reg >> 8) & 0xFF;

    if(!i2c_wait_for_txis()) return I2C_ERROR;

    I2C1->TXDR = reg & 0xFF;

    for(int i = 0; i < num; i++) {
        if(!i2c_wait_for_txis()) return I2C_ERROR;
        I2C1->TXDR = buf[i];
    }

    if(!i2c_wait_for_stop()) return I2C_ERROR;

    I2C1->ICR = I2C_ICR_STOPCF;
    I2C1->CR2 = 0;

    return I2C_OK;
}
