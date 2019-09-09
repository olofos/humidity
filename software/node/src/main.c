#include "stm32l0xx.h"

// Check:
// How does the Clock Security System of the LSE work if the interrupt is disabled?


// https://lowpowerlab.com/forum/rf-range-antennas-rfm69-library/definition-of-rxbw-with-rfm69/


void delay(uint32_t millis)
{
    // for(uint32_t tick = systick; systick - tick < millis;) {
    //     __WFI();
    // }
    for(uint32_t i = 0; i < millis * 1000; i++) {
        __asm__("nop");
    }
}


static void init_clocks(void)
{
    RCC->IOPENR = RCC_IOPENR_IOPAEN;
}

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

static void init_gpio(void)
{
    // GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE15_Msk) | (0x01 << GPIO_MODER_MODE15_Pos);

    GPIOA->AFR[0] =
        (4UL <<  8) | // PA2:  USART2 TX
        (4UL << 12) | // PA3:  USART2 RX
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
        (GPIO_MODER_AF     <<  4) | // PA2:  USART2 TX
        (GPIO_MODER_AF     <<  6) | // PA3:  USART2 RX
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

    GPIOB->OTYPER = 0x00000000;
    GPIOB->AFR[0] = 0x00000000;

    GPIOB->OSPEEDR =
        (GPIO_OSPEEDR_HI << 0) ;    // PB0: Flash CS

    GPIOA->PUPDR =
        (GPIO_PUPDR_PU <<  4) |      // PB2: Config 0
        (GPIO_PUPDR_PU <<  6) |      // PB3: Config 1
        (GPIO_PUPDR_PU <<  8) |      // PB4: Config 2
        (GPIO_PUPDR_PU << 10) |      // PB5: Config 3
        (GPIO_PUPDR_PU << 12) |      // PB6: Config 4
        (GPIO_PUPDR_PU << 14) ;      // PB7: Config 5;

    GPIOB->MODER =
        (GPIO_MODER_OUTPUT <<  0) | // PB0: Flash CS
        (GPIO_MODER_ANALOG <<  2) | // BP1: Bat Mid ADC
        (GPIO_MODER_INPUT  <<  4) | // BP2: Config 0
        (GPIO_MODER_INPUT  <<  6) | // BP3: Config 1
        (GPIO_MODER_INPUT  <<  8) | // BP4: Config 2
        (GPIO_MODER_INPUT  << 10) | // BP5: Config 3
        (GPIO_MODER_INPUT  << 12) | // BP6: Config 4
        (GPIO_MODER_INPUT  << 14) ; // BP7: Config 5
}

void init_hw69(void)
{
}

void init_shtc3(void)
{
}

uint8_t read_config(void)
{
    GPIOB->MODER = (GPIOB->MODER & ~0xFC) |
        (GPIO_MODER_OUTPUT <<  0) | // PB0: Flash CS
        (GPIO_MODER_ANALOG <<  2) | // BP1: Bat Mid ADC
        (GPIO_MODER_INPUT  <<  4) | // BP2: Config 0
        (GPIO_MODER_INPUT  <<  6) | // BP3: Config 1
        (GPIO_MODER_INPUT  <<  8) | // BP4: Config 2
        (GPIO_MODER_INPUT  << 10) | // BP5: Config 3
        (GPIO_MODER_INPUT  << 12) | // BP6: Config 4
        (GPIO_MODER_INPUT  << 14) ; // BP7: Config 5

    GPIOA->PUPDR = (GPIOA->PUPDR & ~0xFC) |
        (GPIO_PUPDR_PU <<  4) |      // PB2: Config 0
        (GPIO_PUPDR_PU <<  6) |      // PB3: Config 1
        (GPIO_PUPDR_PU <<  8) |      // PB4: Config 2
        (GPIO_PUPDR_PU << 10) |      // PB5: Config 3
        (GPIO_PUPDR_PU << 12) |      // PB6: Config 4
        (GPIO_PUPDR_PU << 14) ;      // PB7: Config 5;

    uint8_t conf = (GPIOB->IDR & 0xFC) >> 2;

    GPIOA->PUPDR &= ~0xFC;
    GPIOA->MODER |= 0xFC;

    return conf;
}

void init(void)
{
    init_clocks();
    init_gpio();

//     init_hw69();
//     init_shtc3();
//     init_flash();
}

int main(void)
{
    init();

    for(;;) {
    //     measure_supply();

    //     get_timestamp();

    //     measure_temperature();


    //     sleep();
    //     wakeup();

        GPIOA->BSRR = GPIO_BSRR_BR_15;
        delay(500);

        GPIOA->BSRR = GPIO_BSRR_BS_15;
        delay(500);
    }
}

// void _exit (int status)
// {
//     while (1) {}		/* Make sure we hang here */
// }
// void __register_exitproc(void) { }
