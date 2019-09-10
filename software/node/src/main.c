#include <stdio.h>

#include "stm32l0xx.h"
#include "vector.h"

#define GPIO_MODER_INPUT  0x0UL
#define GPIO_MODER_OUTPUT 0x1UL
#define GPIO_MODER_AF     0x2UL
#define GPIO_MODER_ANALOG 0x3UL

#define GPIO_OTYPER_PP 0x0UL
#define GPIO_OTYPER_OD 0x1UL

// VDD = 1.65 - 2.7 V
// Low:       100 kHz
// Mid:       600 kHz
// High:        2 MHz
// Very High:  10 MHz

#define GPIO_OSPEEDR_LOW 0x0UL
#define GPIO_OSPEEDR_MID 0x1UL
#define GPIO_OSPEEDR_HI  0x2UL
#define GPIO_OSPEEDR_VHI 0x3UL

#define GPIO_PUPDR_NONE 0x00
#define GPIO_PUPDR_PU   0x01
#define GPIO_PUPDR_PD   0x02

#define EXPAND_MASK(MASK) (                     \
        (((MASK) & 0x0001) ? 0x00000003 : 0) |  \
        (((MASK) & 0x0002) ? 0x0000000C : 0) |  \
        (((MASK) & 0x0004) ? 0x00000030 : 0) |  \
        (((MASK) & 0x0008) ? 0x000000C0 : 0) |  \
        (((MASK) & 0x0010) ? 0x00000300 : 0) |  \
        (((MASK) & 0x0020) ? 0x00000C00 : 0) |  \
        (((MASK) & 0x0040) ? 0x00003000 : 0) |  \
        (((MASK) & 0x0080) ? 0x0000C000 : 0) |  \
        (((MASK) & 0x0100) ? 0x00030000 : 0) |  \
        (((MASK) & 0x0200) ? 0x000C0000 : 0) |  \
        (((MASK) & 0x0400) ? 0x00300000 : 0) |  \
        (((MASK) & 0x0800) ? 0x00C00000 : 0) |  \
        (((MASK) & 0x1000) ? 0x03000000 : 0) |  \
        (((MASK) & 0x2000) ? 0x0C000000 : 0) |  \
        (((MASK) & 0x4000) ? 0x30000000 : 0) |  \
        (((MASK) & 0x8000) ? 0xC0000000 : 0) )


volatile uint32_t systick;



// Check:
// How does the Clock Security System of the LSE work if the interrupt is disabled?


// https://lowpowerlab.com/forum/rf-range-antennas-rfm69-library/definition-of-rxbw-with-rfm69/


void delay(uint32_t millis)
{
    for(uint32_t tick = systick; systick - tick < millis;) {
        __WFI();
    }
    // for(uint32_t i = 0; i < millis * 1000; i++) {
    //     __asm__("nop");
    // }
}


static void init_clocks(void)
{
    RCC->IOPENR = RCC_IOPENR_IOPAEN | RCC_IOPENR_IOPBEN;

    RCC->APB1ENR = RCC_APB1ENR_LPUART1EN | RCC_APB1ENR_PWREN | RCC_APB1ENR_LPUART1EN;
    RCC->APB2ENR = RCC_APB2ENR_DBGEN | RCC_APB2ENR_SYSCFGEN;

    SysTick->CTRL = 0;
    SysTick->LOAD = 2097;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk;

    PWR->CR |= PWR_CR_DBP;
    RCC->CSR |= RCC_CSR_LSEON | RCC_CSR_LSEDRV_0;

    RCC->CCIPR = RCC_CCIPR_LPUART1SEL_0 | RCC_CCIPR_LPUART1SEL_1;
}

static void init_uart(void)
{
    LPUART1->BRR = 0x369;
    LPUART1->CR1 = USART_CR1_TE | USART_CR1_UE;
}

static void init_gpio(void)
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
        (GPIO_OSPEEDR_MID <<  2) | // PA1:  LEDR
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
        (GPIO_MODER_ANALOG <<  8) | // PA4:  RFM69 CS
        (GPIO_MODER_AF     << 10) | // PA5:  SPI1 SCK
        (GPIO_MODER_AF     << 12) | // PA6:  SPI1 MISO
        (GPIO_MODER_AF     << 14) | // PA7:  SPI1 MOSI
        (GPIO_MODER_ANALOG << 16) | // PA8:  RFM69 Interrupt
        (GPIO_MODER_ANALOG << 18) | // PA9:  I2C1 SCL
        (GPIO_MODER_ANALOG << 20) | // PA10: I2C1 SDA
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
        (GPIO_MODER_ANALOG  <<  6) | // BP3: Config 0
        (GPIO_MODER_ANALOG  <<  8) | // BP4: Config 1
        (GPIO_MODER_ANALOG  << 10) | // BP5: Config 2
        (GPIO_MODER_ANALOG  << 12) | // BP6: Config 3
        (GPIO_MODER_ANALOG  << 14) ; // BP7: Config 4
}

void init_hw69(void)
{
}

void init_shtc3(void)
{
}

#define CONF_MASK 0xF8UL
#define CONF_SHIFT 3

uint8_t read_config(void)
{
    GPIOB->MODER = (GPIOB->MODER & ~EXPAND_MASK(CONF_MASK)) |
        (GPIO_MODER_INPUT  <<  6) | // BP3: Config 0
        (GPIO_MODER_INPUT  <<  8) | // BP4: Config 1
        (GPIO_MODER_INPUT  << 10) | // BP5: Config 2
        (GPIO_MODER_INPUT  << 12) | // BP6: Config 3
        (GPIO_MODER_INPUT  << 14) ; // BP7: Config 4

    GPIOB->PUPDR = (GPIOB->PUPDR & ~EXPAND_MASK(CONF_MASK)) |
        (GPIO_PUPDR_PU <<  6) |      // PB3: Config 0
        (GPIO_PUPDR_PU <<  8) |      // PB4: Config 1
        (GPIO_PUPDR_PU << 10) |      // PB5: Config 2
        (GPIO_PUPDR_PU << 12) |      // PB6: Config 3
        (GPIO_PUPDR_PU << 14) ;      // PB7: Config 4;

    uint8_t conf = (GPIOB->IDR & CONF_MASK) >> CONF_SHIFT;

    GPIOB->PUPDR &= ~EXPAND_MASK(CONF_MASK);
    GPIOB->MODER |= EXPAND_MASK(CONF_MASK);

    return conf;
}

void init(void)
{
    init_clocks();
    init_gpio();
    init_uart();

//     init_hw69();
//     init_shtc3();

//     init_flash();
}

void print_char(char c)
{
    while(!(LPUART1->ISR & USART_ISR_TXE)) {
    }
    LPUART1->TDR = c;
}

void print_string(char *s)
{
    while(*s) {
        print_char(*s++);
    }
}

ssize_t _write_r(struct _reent *reent, int fd, const void *buf, size_t count)
{
    (void) reent;

    if(fd == 1) {
        const char *s = buf;
        for(unsigned i = 0; i < count; i++) {
            print_char(s[i]);
        }

        return count;
    } else {
        return -1;
    }
}

int main(void)
{
    init();

    volatile uint8_t conf = read_config();
    (void) conf;

    while(!(RCC->CSR & RCC_CSR_LSERDY)) {
        GPIOA->BSRR = GPIO_BSRR_BS_15;
        delay(100);

        GPIOA->BSRR = GPIO_BSRR_BR_15;
        delay(100);
    }

    uint32_t tick = systick;
    uint8_t led = 1;

    for(int i = 0, j = 0; ; i++, j++) {
        printf("i = %d\r\n", i);

        if(systick - tick > 500) {
            if(led) {
                GPIOA->BSRR = GPIO_BSRR_BS_15;
            } else {
                GPIOA->BSRR = GPIO_BSRR_BR_15;
            }
            tick = systick;
            led = !led;
            printf("--------------------- %d\r\n", j);
            j = 0;
        }

        // delay(500);
        // delay(500);

    }
}

void SysTick_Handler(void)
{
    systick++;
}
