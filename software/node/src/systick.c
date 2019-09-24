#include <stdint.h>

#include "stm32l0xx.h"
#include "systick.h"
#include "vector.h"

volatile uint32_t systick = 100000;

void systick_init(void)
{
    SysTick->CTRL = 0;
    SysTick->LOAD = 2097;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk;
}

void delay(uint32_t millis)
{
    for(uint32_t tick = systick; systick - tick < millis;) {
        __WFI();
    }
}

void SysTick_Handler(void)
{
    systick++;
}
