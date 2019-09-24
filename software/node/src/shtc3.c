#include <stdint.h>

#include "stm32l0xx.h"
#include "shtc3.h"
#include "shtc3-registers.h"
#include "i2c.h"
#include "systick.h"

int shtc3_read(int32_t *temperature, uint32_t *humidity)
{
    uint32_t start = systick;

    uint8_t buf[6];

    while(!i2c_register_read(SHTC3_I2C_ADDRESS, SHTC3_COMMAND_READ, buf, sizeof(buf), start, SHTC3_TIMEOUT)) {
        if(systick - start >= SHTC3_TIMEOUT) return I2C_ERROR;
    }

    const uint8_t temp_hi = buf[0];
    const uint8_t temp_lo = buf[1];
    const uint8_t humidity_hi = buf[3];
    const uint8_t humidity_lo = buf[4];

    *temperature = ((temp_hi << 8) | temp_lo) * 175 - (45 << 16);
    *humidity = (humidity_hi << 8) | humidity_lo;

    return I2C_OK;
}

int shtc3_read_id(uint16_t *id)
{
    uint32_t start = systick;

    uint8_t buf[3];

    while(!i2c_register_read(SHTC3_I2C_ADDRESS, SHTC3_COMMAND_ID, buf, sizeof(buf), start, SHTC3_TIMEOUT)) {
        if(systick - start >= SHTC3_TIMEOUT) return I2C_ERROR;
    }

    *id = (buf[0] << 8) | buf[1];

    return I2C_OK;
}

int shtc3_wakeup(void)
{
    return i2c_register_write(SHTC3_I2C_ADDRESS, SHTC3_COMMAND_WAKEUP, 0, 0, systick, SHTC3_TIMEOUT);
}

int shtc3_sleep(void)
{
    return i2c_register_write(SHTC3_I2C_ADDRESS, SHTC3_COMMAND_SLEEP, 0, 0, systick, SHTC3_TIMEOUT);
}

uint16_t shtc3_test(void)
{
    uint16_t id;

    if(shtc3_read_id(&id)) {
        if((id & SHTC3_ID_MASK) == SHTC3_ID) {
            return id;
        }
    }

    return I2C_ERROR;
}
