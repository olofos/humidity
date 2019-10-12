#include "stm32l0xx.h"
#include "rtc.h"
#include "vector.h"

// Checksum generated during build
static uint32_t __attribute__((section(".checksum"))) rtc_checksum[2];

static void rtc_write_protect_unlock(void)
{
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
}

static void rtc_write_protect_lock(void)
{
    RTC->WPR = 0xFF;
}

int rtc_is_rtc_clock_initialized(void)
{
    return RTC->ISR & RTC_ISR_INITS;
}

int rtc_are_peripherals_initialized(void)
{
    // Check if the checksum of the binary matches the previously seen one
    int match = (rtc_checksum[0] == RTC->BKP0R) && (rtc_checksum[1] == RTC->BKP1R);
    if(!match) {
        // Save checksum in backup registers
        RTC->BKP0R = rtc_checksum[0];
        RTC->BKP1R = rtc_checksum[1];
    }

    return match;
}

void rtc_set_time(struct rtc_timestamp timestamp)
{
    rtc_write_protect_unlock();

    RTC->ISR |= RTC_ISR_INIT;

    while(!(RTC->ISR & RTC_ISR_INITF)) {
    }

    RTC->TR = timestamp.time;
    RTC->DR = timestamp.date;

    RTC->ISR &= ~RTC_ISR_INIT;

    rtc_write_protect_lock();
}

struct rtc_timestamp rtc_get_time(void)
{
    while(!(RTC->ISR & RTC_ISR_RSF)) {
    }

    struct rtc_timestamp timestamp;
    timestamp.time = RTC->TR & 0x003F7F7F;
    timestamp.date = RTC->DR & 0x00FF1F3F;

    return timestamp;
}

void rtc_set_periodic_wakeup(uint16_t seconds)
{
    rtc_write_protect_unlock();

    RTC->CR &= ~RTC_CR_WUTE;

    while(!(RTC->ISR & RTC_ISR_WUTWF)) {
    }

    RTC->CR = (RTC->CR & ~(RTC_CR_WUCKSEL_Msk)) | (0x04 << RTC_CR_WUCKSEL_Pos) | RTC_CR_WUTIE;
    RTC->WUTR = seconds - 1;

    RTC->CR |= RTC_CR_WUTE;

    rtc_write_protect_lock();

    EXTI->IMR |= 1 << 20;
    EXTI->RTSR |= 1 << 20;

    NVIC_EnableIRQ(RTC_IRQn);

    RTC->ISR = 0;
}

void RTC_IRQHandler(void)
{
    EXTI->PR = 1 << 20;
}