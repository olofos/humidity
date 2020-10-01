#include <stdint.h>
#include <string.h>

#include "stm32l0xx.h"
#include "state.h"

void state_init(void)
{
    // Assume that state is in BSS
}

void state_save(void)
{
    RTC->BKP0R = state.flags;
    RTC->BKP1R = ((uint32_t) state.timer.take_measurement << 16) | state.timer.send_measurement;
    RTC->BKP2R = ((uint32_t) state.timer.send_debug << 16) | state.timer.send_update;
}

void state_load(void)
{
    state.flags = RTC->BKP0R & 0x000000FF;
    state.timer.take_measurement = (RTC->BKP1R >> 16) & 0x0000FFFF;
    state.timer.send_measurement = RTC->BKP1R & 0x0000FFFF;
    state.timer.send_debug = (RTC->BKP2R >> 16) & 0x0000FFFF;
    state.timer.send_update = RTC->BKP2R & 0x0000FFFF;
}
