#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>

struct rtc_timestamp {
    uint32_t time;
    uint32_t date;
};

int rtc_is_rtc_clock_initialized(void);
int rtc_are_peripherals_initialized(void);
void rtc_wait_for_lse(void);
int rtc_check_version(void);

void rtc_set_time(struct rtc_timestamp *timestamp);
void rtc_get_time(struct rtc_timestamp *timestamp);

void rtc_set_periodic_wakeup(uint16_t seconds);

#endif
