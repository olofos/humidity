#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>

struct pkg_timestamp;

int rtc_is_rtc_clock_initialized(void);
int rtc_check_version(void);

void rtc_set_time(const struct pkg_timestamp *timestamp);
void rtc_get_time(struct pkg_timestamp *timestamp);

void rtc_set_periodic_wakeup(uint16_t seconds);

#endif
