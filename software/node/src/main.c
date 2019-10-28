#include <stdio.h>
#include <string.h>

#include "stm32l0xx.h"
#include "gpio.h"
#include "uart.h"
#include "systick.h"
#include "spi.h"
#include "spi-flash.h"
#include "rfm69.h"
#include "shtc3.h"
#include "i2c.h"
#include "adc.h"
#include "rfm69-registers.h"
#include "rfm69-hal.h"
#include "rtc.h"
#include "package.h"


#define GATEWAY_ADDRESS 0x01

// Check:
// How does the Clock Security System of the LSE work if the interrupt is disabled?


// https://lowpowerlab.com/forum/rf-range-antennas-rfm69-library/definition-of-rxbw-with-rfm69/


static void clocks_init(void)
{
    RCC->IOPENR = RCC_IOPENR_IOPAEN | RCC_IOPENR_IOPBEN;

    RCC->AHBENR = RCC_AHBENR_DMAEN;
    RCC->APB1ENR = RCC_APB1ENR_PWREN;
    RCC->APB2ENR = RCC_APB2ENR_DBGEN | RCC_APB2ENR_SYSCFGEN;

    PWR->CR |= PWR_CR_DBP;
    RCC->CSR |= RCC_CSR_RTCSEL_0 ;
    RCC->CSR |= RCC_CSR_LSEON | RCC_CSR_RTCEN;

    RCC->CCIPR = RCC_CCIPR_LPUART1SEL_0 | RCC_CCIPR_LPUART1SEL_1;
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
    GPIOB->PUPDR = (GPIOB->PUPDR & ~EXPAND_MASK(CONF_MASK)) |
        (GPIO_PUPDR_PU <<  6) |      // PB3: Config 0
        (GPIO_PUPDR_PU <<  8) |      // PB4: Config 1
        (GPIO_PUPDR_PU << 10) |      // PB5: Config 2
        (GPIO_PUPDR_PU << 12) |      // PB6: Config 3
        (GPIO_PUPDR_PU << 14) ;      // PB7: Config 4;

    GPIOB->MODER = (GPIOB->MODER & ~EXPAND_MASK(CONF_MASK)) |
        (GPIO_MODER_INPUT  <<  6) | // BP3: Config 0
        (GPIO_MODER_INPUT  <<  8) | // BP4: Config 1
        (GPIO_MODER_INPUT  << 10) | // BP5: Config 2
        (GPIO_MODER_INPUT  << 12) | // BP6: Config 3
        (GPIO_MODER_INPUT  << 14) ; // BP7: Config 4

    __NOP();

    uint8_t conf = (GPIOB->IDR & CONF_MASK) >> CONF_SHIFT;

    GPIOB->MODER |= EXPAND_MASK(CONF_MASK);
    GPIOB->PUPDR &= ~EXPAND_MASK(CONF_MASK);

    return conf;
}

void print_temperature(int16_t temperature)
{
    uint32_t t;
    char s;

    if(temperature >= 0) {
        s = ' ';
        t = temperature;
    } else {
        s = '-';
        t = -temperature;
    }

    int integer = t  >> SHTC3_TEMPERATURE_SHIFT;
    int fraction = (100 * (t & 0x00FF)) >> SHTC3_TEMPERATURE_SHIFT;

    printf("Temperature: %c%d.%02dC\r\n", s, integer, fraction);
}

void print_humidity(uint16_t humidity)
{
    uint32_t h = humidity * 100;
    int integer = h  >> 16;
    int fraction = (100 * (h & 0x0000FFFF)) >> 16;

    printf("Humidity:     %d.%02d%%\r\n", integer, fraction);
}

void print_measurement(struct shtc3_measurement measurement)
{
    print_temperature(measurement.temperature);
    print_humidity(measurement.humidity);
}

void print_voltages(struct adc_supply_voltages voltages)
{
    printf("Vcc:          %d.%dV\r\n", voltages.vcc >> ADC_VOLTAGE_SHIFT, (100 * (voltages.vcc & ((1<<ADC_VOLTAGE_SHIFT)-1))) >> ADC_VOLTAGE_SHIFT);
    printf("Vmid:         %d.%dV\r\n", voltages.vmid >> ADC_VOLTAGE_SHIFT, (100 * (voltages.vmid & ((1<<ADC_VOLTAGE_SHIFT)-1))) >> ADC_VOLTAGE_SHIFT);
}

void print_timestamp(const struct pkg_timestamp *timestamp)
{
    printf("20%02X-%02X-%02X %02X:%02X:%02X\r\n",
           timestamp->year,
           timestamp->month,
           timestamp->day,
           timestamp->hour,
           timestamp->minute,
           timestamp->second);
}

void sleep(void)
{
    systick_pause();
    while(!(RTC->ISR & RTC_ISR_WUTF)) {
        __WFI();
    }
    RTC->ISR = 0;
    systick_resume();
}

static const uint8_t aes_key[16] = { 0xc6, 0xe0, 0xca, 0x0a, 0xbd, 0x23, 0x3d, 0x84, 0x5d, 0x06, 0x8f, 0x0f, 0x8c, 0x5d, 0xa8, 0xf3 };

void init_always(void)
{
    clocks_init();
    gpio_init();
    systick_init();
    rtc_wait_for_lse();
    uart_init_dma();
    spi_init();
}

void init_full(void)
{
    i2c_init();
    shtc3_wakeup();

    uint16_t shtc3_id = shtc3_test();
    if(shtc3_id) {
        printf("SHTC3 detected (%04X)\r\n", shtc3_id);
    } else {
        printf("No SHTC3 detected\r\n");
    }

    shtc3_sleep();
    i2c_deinit();

    if(rfm69_test()) {
        printf("RFM69 detected\r\n");
    } else {
        printf("No RFM69 detected\r\n");
    }

    rfm69_init();
    rfm69_set_aes_key(aes_key);
    rfm69_set_mode(RFM69_MODE_SLEEP);

    spi_flash_wakeup();
    if(spi_flash_test()) {
        printf("SPI Flash detected\r\n");
    } else {
        printf("No SPI Flash detected\r\n");
    }
    spi_flash_sleep();

    struct rtc_timestamp timestamp = {
        .time = 0,
        .date = 0,
    };

    rtc_set_time(timestamp);
}

void rtc_set_timestamp(const struct pkg_timestamp *pkg_timestamp)
{
    struct rtc_timestamp rtc_timestamp = {
        .time = ((uint32_t) pkg_timestamp->hour << 16) | ((uint32_t) pkg_timestamp->minute << 8) | pkg_timestamp->second,
        .date = ((uint32_t) pkg_timestamp->year << 16) | ((uint32_t) pkg_timestamp->month << 8) | pkg_timestamp->day,
    };

    rtc_set_time(rtc_timestamp);
}

void rtc_get_timestamp(struct pkg_timestamp *pkg_timestamp)
{
    const struct rtc_timestamp rtc_timestamp = rtc_get_time();
    pkg_timestamp->year = (rtc_timestamp.date >> 16) & 0x000000FF;
    pkg_timestamp->month = (rtc_timestamp.date >> 8) & 0x000000FF;
    pkg_timestamp->day = rtc_timestamp.date & 0x000000FF;
    pkg_timestamp->hour = (rtc_timestamp.time >> 16) & 0x000000FF;
    pkg_timestamp->minute = (rtc_timestamp.time >> 8) & 0x000000FF;
    pkg_timestamp->second = rtc_timestamp.time & 0x000000FF;
}


enum state {
    STATE_REGISTER,
    STATE_MEASURE,
    STATE_UPDATE,

    STATE_NUM,
};

typedef enum state state_handler_t(void);

enum state do_register(void);
enum state do_measure(void);
enum state do_update(void);

state_handler_t *state_handlers[STATE_NUM] = {
    [STATE_REGISTER] = do_register,
    [STATE_MEASURE] = do_measure,
    [STATE_UPDATE] = do_update,
};

extern uint32_t rtc_checksum[2];

static struct pkg_buffer pkg_buffer;

enum state do_register(void)
{
    struct pkg_buffer *p = &pkg_buffer;

    pkg_init(p);

    pkg_write_byte(p, PKG_REGISTER);
    pkg_write_byte(p, PKG_NODE_TYPE_HUMIDITY);
    pkg_write_dword(p, rtc_checksum[0]);
    pkg_write_dword(p, rtc_checksum[1]);

    rfm69_set_mode(RFM69_MODE_STANDBY);

    if(pkg_write(GATEWAY_ADDRESS, p) > 0) {
        if(pkg_read(p) > 0) {
            rfm69_set_mode(RFM69_MODE_SLEEP);

            uint8_t response = pkg_read_byte(p);

            if(response == PKG_SET_TIME) {
                struct pkg_timestamp pkg_timestamp;
                pkg_read_timestamp(p, &pkg_timestamp);
                rtc_set_timestamp(&pkg_timestamp);

                printf("New time: ");
                print_timestamp(&pkg_timestamp);

                return STATE_MEASURE;
            } else if(response == PKG_NACK) {
                printf("Registration failed\r\n");
            } else {
                printf("Unexpected response %02X\r\n", response);
            }
        } else {
            printf("Read failed\r\n");
        }
    } else {
        printf("Write failed\r\n");
    }

    return STATE_REGISTER;
}

enum state do_measure(void)
{
    int measurement_failed = 0;

    printf("\r\n");

    struct pkg_timestamp pkg_timestamp;
    rtc_get_timestamp(&pkg_timestamp);

    printf("Timestamp:    ");
    print_timestamp(&pkg_timestamp);

    i2c_init();
    shtc3_wakeup();

    struct shtc3_measurement measurement;
    if(shtc3_read(&measurement)) {
        print_measurement(measurement);
    } else {
        measurement_failed = 1;
        printf("Reading temperature and humidity failed\r\n");
    }

    shtc3_sleep();
    i2c_deinit();

    adc_init();
    struct adc_supply_voltages voltages;

    if(adc_measure_voltages(&voltages)) {
        print_voltages(voltages);
    } else {
        measurement_failed = 1;
        printf("Reading voltages failed\r\n");
    }
    adc_deinit();


    if(measurement_failed) {
        printf("Measurement failed\r\n");
    } else {
        struct pkg_buffer *p = &pkg_buffer;

        pkg_init(p);

        pkg_write_byte(p, PKG_MEASUREMENT);

        pkg_write_timestamp(p, &pkg_timestamp);
        pkg_write_word(p, measurement.humidity);
        pkg_write_word(p, measurement.temperature);
        pkg_write_word(p, voltages.vcc);
        pkg_write_word(p, voltages.vmid);

        rfm69_set_mode(RFM69_MODE_STANDBY);

        if(pkg_write(GATEWAY_ADDRESS, p) > 0) {
            if(pkg_read(p) > 0) {
                rfm69_set_mode(RFM69_MODE_SLEEP);

                uint8_t response = pkg_read_byte(p);

                if(response == PKG_ACK) {
                    uint8_t flags = pkg_read_byte(p);

                    if(flags & PKG_FLAG_UPDATE_AVAILABLE) {
                        printf("Note:         New firmware version available\r\n");
                    }
                } else {
                    printf("Did not receive ack\r\n");
                }
            } else {
                printf("Read failed\r\n");
            }
        } else {
            printf("Write failed\r\n");
        }
    }

    return STATE_MEASURE;
}

enum state do_update(void)
{
    return STATE_MEASURE;
}


int main(void)
{
    DBGMCU->CR = DBGMCU_CR_DBG;

    init_always();

    printf("\r\n\r\n");

    uint8_t conf = read_config();
    printf("Config: %d\r\n", conf);

    if(!rtc_are_peripherals_initialized()) {
        init_full();
    }

    rtc_set_periodic_wakeup(5);
    rfm69_set_node_address((PKG_NODE_TYPE_HUMIDITY << 6) | conf);

    enum state state = STATE_REGISTER;

    for(;;) {
        state = state_handlers[state]();
        sleep();
    }
}
