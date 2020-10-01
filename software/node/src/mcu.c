#include <stdio.h>

#include "stm32l0xx.h"
#include "gpio.h"
#include "systick.h"
#include "mcu.h"
#include "rtc.h"
#include "uart.h"
#include "spi.h"


// Check:
// How does the Clock Security System of the LSE work if the interrupt is disabled?

// https://lowpowerlab.com/forum/rf-range-antennas-rfm69-library/definition-of-rxbw-with-rfm69/

static void clocks_init(void)
{
    RCC->IOPENR = RCC_IOPENR_IOPAEN | RCC_IOPENR_IOPBEN;

    RCC->AHBENR = RCC_AHBENR_DMAEN;
    RCC->APB1ENR = RCC_APB1ENR_PWREN;
    RCC->APB2ENR = RCC_APB2ENR_DBGEN | RCC_APB2ENR_SYSCFGEN;

    PWR->CR = PWR_CR_DBP | PWR_CR_LPSDSR | PWR_CR_CWUF | PWR_CR_CSBF;

    SCB->SCR = 0;

    // Clock RTC from from 32768 Hz LSE clock
    RCC->CSR |= RCC_CSR_RTCSEL_0 | RCC_CSR_LSEON | RCC_CSR_RTCEN;

    // Clock LPUART from 32768 Hz LSE clock
    RCC->CCIPR = RCC_CCIPR_LPUART1SEL_0 | RCC_CCIPR_LPUART1SEL_1;

    RTC->ISR = 0;
}

static void gpio_init(void)
{
    GPIOA->AFR[0] =
        (6UL <<  8) | // PA2:  LPUART1 TX
        (6UL << 12) | // PA3:  LPUART1 RX
        (0UL << 20) | // PA5:  SPI1 SCK
        (0UL << 24) | // PA6:  SPI1 MISO
        (0UL << 28) ; // PA7:  SPI1 MOSI

    GPIOA->AFR[1] =
        (1UL <<  4) | // PA9:  I2C1 SCL
        (1UL <<  8) | // PA10: I2C1 SCL
        (0UL << 20) | // PA13: SWDIO
        (0UL << 24) ; // PA14: SWCLK

    GPIOA->OTYPER =
        (GPIO_OTYPER_OD <<  9) |   // PA9:  I2C1 SCL
        (GPIO_OTYPER_OD << 10) |   // PA10: I2C1 SDA
        (GPIO_OTYPER_OD << 11) ;   // PA11: RFM69 Reset

    GPIOA->OSPEEDR =
        (GPIO_OSPEEDR_MID <<  2) | // PA1:  LEDG
        (GPIO_OSPEEDR_MID <<  4) | // PA2:  USRT2 TX
        (GPIO_OSPEEDR_HI  <<  8) | // PA4:  RFM69 CS
        (GPIO_OSPEEDR_VHI << 10) | // PA5:  SPI1 SCK
        (GPIO_OSPEEDR_VHI << 14) | // PA7:  SPI1 MOSI
        (GPIO_OSPEEDR_MID << 18) | // PA9:  I2C1 SCL
        (GPIO_OSPEEDR_MID << 20) | // PA10: I2C1 SDA
        (GPIO_OSPEEDR_HI  << 22) | // PA11: RFM69 Reset
        (GPIO_OSPEEDR_VHI << 26) | // PA13: SWDIO
        (GPIO_OSPEEDR_VHI << 30) ; // PA15: LEDR

    GPIOA->PUPDR =
        (GPIO_PUPDR_PU << 26) | // PA13: SWDIO
        (GPIO_PUPDR_PD << 28) ; // PA14: SWCLK

    GPIOA->MODER =
        (GPIO_MODER_INPUT  <<  0) | // PA0:  Switch
        (GPIO_MODER_ANALOG <<  2) | // PA1:  LEDG
        (GPIO_MODER_AF     <<  4) | // PA2:  LPUART1 TX
        (GPIO_MODER_AF     <<  6) | // PA3:  LPUART1 RX
        (GPIO_MODER_OUTPUT <<  8) | // PA4:  RFM69 CS
        (GPIO_MODER_AF     << 10) | // PA5:  SPI1 SCK
        (GPIO_MODER_AF     << 12) | // PA6:  SPI1 MISO
        (GPIO_MODER_AF     << 14) | // PA7:  SPI1 MOSI
        (GPIO_MODER_ANALOG << 16) | // PA8:  RFM69 Interrupt
        (GPIO_MODER_AF     << 18) | // PA9:  I2C1 SCL
        (GPIO_MODER_AF     << 20) | // PA10: I2C1 SDA
        (GPIO_MODER_ANALOG << 22) | // PA11: RFM69 Reset
        (GPIO_MODER_ANALOG << 24) | // PA12: unused
        (GPIO_MODER_AF     << 26) | // PA13: SWDIO
        (GPIO_MODER_AF     << 28) | // PA14: SWCLK
        (GPIO_MODER_OUTPUT << 30) ; // PA15: LEDR

    GPIOB->OTYPER = 0x0000;
    GPIOB->AFR[0] = 0x0000;

    GPIOB->OSPEEDR =
        (GPIO_OSPEEDR_HI << 0) ;    // PB0: Flash CS

    GPIOB->PUPDR = 0x0000;

    GPIOB->MODER =
        (GPIO_MODER_OUTPUT <<  0) | // PB0: Flash CS
        (GPIO_MODER_ANALOG <<  2) | // BP1: Bat Mid ADC
        (GPIO_MODER_ANALOG <<  6) | // BP3: Config 0
        (GPIO_MODER_ANALOG <<  8) | // BP4: Config 1
        (GPIO_MODER_ANALOG << 10) | // BP5: Config 2
        (GPIO_MODER_ANALOG << 12) | // BP6: Config 3
        (GPIO_MODER_ANALOG << 14) ; // BP7: Config 4

    GPIOB->BSRR = GPIO_BSRR_BS_0;
}

#define CONF_MASK 0xF8UL
#define CONF_SHIFT 3

uint8_t read_config(void)
{
    GPIOB->PUPDR = (GPIOB->PUPDR & ~EXPAND_MASK(CONF_MASK)) |
        (GPIO_PUPDR_PU <<  6) |      // PB3: Config 0
        (GPIO_PUPDR_PU <<  8) |      // PB4: Config 1
        (GPIO_PUPDR_PU << 10) |      // PB5: Config 2
        (GPIO_PUPDR_PU << 12) |      // PB6: Config 3
        (GPIO_PUPDR_PU << 14) ;      // PB7: Config 4

    GPIOB->MODER = (GPIOB->MODER & ~EXPAND_MASK(CONF_MASK)) |
        (GPIO_MODER_INPUT  <<  6) | // BP3: Config 0
        (GPIO_MODER_INPUT  <<  8) | // BP4: Config 1
        (GPIO_MODER_INPUT  << 10) | // BP5: Config 2
        (GPIO_MODER_INPUT  << 12) | // BP6: Config 3
        (GPIO_MODER_INPUT  << 14) ; // BP7: Config 4

    // Wait a bit so that we can correctly read the pins
    __NOP();

    uint8_t conf = (GPIOB->IDR & CONF_MASK) >> CONF_SHIFT;

    GPIOB->MODER |= EXPAND_MASK(CONF_MASK);
    GPIOB->PUPDR &= ~EXPAND_MASK(CONF_MASK);

    return conf;
}

static void sleep_do_sleep(void)
{
    systick_pause();
    while(!(RTC->ISR & RTC_ISR_WUTF)) {
        __WFI();
    }

    RTC->ISR = 0;
    PWR->CR |= PWR_CR_CWUF;
    systick_resume();
}

void sleep(uint8_t mode, uint16_t period)
{
    rtc_set_periodic_wakeup(period);

    if(mode == SLEEP_MODE_NONE) {
        return;
    } else if(mode == SLEEP_MODE_DEEP) {
        SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
        PWR->CR |= PWR_CR_ULP;
    } else if(mode == SLEEP_MODE_STANDBY) {
        SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
        PWR->CR |= PWR_CR_ULP | PWR_CR_PDDS;
    }

    sleep_do_sleep();

    PWR->CR &= ~(PWR_CR_PDDS | PWR_CR_ULP);
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
}

static void wait_for_lse(void)
{
    while(!(RCC->CSR & RCC_CSR_LSERDY)) {
        GPIOA->BSRR = GPIO_BSRR_BS_15;
        delay(100);

        GPIOA->BSRR = GPIO_BSRR_BR_15;
        delay(100);
    }
}



uint32_t mcu_init(void)
{
    DBGMCU->CR = DBGMCU_CR_DBG;
    uint32_t woke_from_standby = PWR->CSR & PWR_CSR_SBF;

    clocks_init();
    gpio_init();
    systick_init();
    wait_for_lse();
    uart_init_dma();
    spi_init();

    return woke_from_standby;
}


void ledr_on(void)
{
    GPIOA->BSRR = GPIO_BSRR_BS_15;
}

void ledr_off(void)
{
    GPIOA->BSRR = GPIO_BSRR_BR_15;
}

uint32_t button_pushed(void)
{
    return GPIOA->IDR & GPIO_IDR_ID0;
}
