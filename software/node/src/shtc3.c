#include <stdint.h>

#include "stm32l0xx.h"
#include "shtc3.h"
#include "shtc3-crc.h"
#include "shtc3-registers.h"
#include "i2c.h"
#include "systick.h"

int shtc3_read(struct shtc3_measurement *measurement)
{
    uint32_t start = systick;

    uint8_t buf[6];

    while(!i2c_register_read(SHTC3_I2C_ADDRESS, SHTC3_COMMAND_READ, buf, sizeof(buf), start, SHTC3_TIMEOUT)) {
        if(systick - start >= SHTC3_TIMEOUT) return I2C_ERROR;
    }

    const uint32_t t = (buf[0] << 8) | buf[1];
    const uint32_t h = (buf[3] << 8) | buf[4];

    if(buf[2] != shtc3_crc(t)) return I2C_ERROR;
    if(buf[5] != shtc3_crc(h)) return I2C_ERROR;

    measurement->temperature = (t * 175 - (45 << 16)) >> (16 - SHTC3_TEMPERATURE_SHIFT);
    measurement->humidity = h;

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

    return buf[2] == shtc3_crc(*id);
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
