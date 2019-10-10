#include "stm32l0xx.h"
#include "rtc.h"

int rtc_is_initialized(void)
{
    return RTC->ISR & RTC_ISR_INITS;
}

static void rtc_write_protect_unlock(void)
{
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
}

static void rtc_write_protect_lock(void)
{
    RTC->WPR = 0xFF;
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
