#include "stm32l0xx.h"
#include "rtc.h"
#include "vector.h"
#include "systick.h"

#define RTC_UNLOCK_MAGIC1 0xCA
#define RTC_UNLOCK_MAGIC2 0x53

#define RTC_LOCK_MAGIC    0xFF

#define RTC_EXTI (1 << 20)

static void rtc_write_protect_unlock(void)
{
    RTC->WPR = RTC_UNLOCK_MAGIC1;
    RTC->WPR = RTC_UNLOCK_MAGIC2;
}

static void rtc_write_protect_lock(void)
{
    RTC->WPR = RTC_LOCK_MAGIC;
}

int rtc_is_rtc_clock_initialized(void)
{
    return RTC->ISR & RTC_ISR_INITS;
}

void rtc_wait_for_lse(void)
{
    while(!(RCC->CSR & RCC_CSR_LSERDY)) {
        GPIOA->BSRR = GPIO_BSRR_BS_15;
        delay(100);

        GPIOA->BSRR = GPIO_BSRR_BR_15;
        delay(100);
    }
}

void rtc_set_time(struct rtc_timestamp *timestamp)
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

void_timestamp rtc_get_time(struct rtc_timestamp *timestamp)
{
    while(!(RTC->ISR & RTC_ISR_RSF)) {
    }

    timestamp->time = RTC->TR & 0x003F7F7F;
    timestamp->date = RTC->DR & 0x00FF1F3F;
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

    EXTI->IMR |= RTC_EXTI;
    EXTI->RTSR |= RTC_EXTI;

    NVIC_EnableIRQ(RTC_IRQn);

    RTC->ISR = 0;
}

void RTC_IRQHandler(void)
{
    EXTI->PR = RTC_EXTI;
}
