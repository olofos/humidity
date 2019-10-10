#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>

struct rtc_timestamp {
    uint32_t time;
    uint32_t date;
};


int rtc_is_initialized(void);

void rtc_set_time(struct rtc_timestamp timestamp);
struct rtc_timestamp rtc_get_time(void);


#endif
