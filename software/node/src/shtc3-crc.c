#include <stdint.h>

// Algorithm from https://stackoverflow.com/questions/51752284/how-to-calculate-crc8-in-c

uint8_t shtc3_crc(uint16_t data)
{
    const uint8_t poly = 0x31;
    uint8_t crc = 0xFF;

    crc ^= data >> 8;

    for(int j = 0; j < 8; j++) {
        if(crc & 0x80) {
            crc = (crc << 1) ^ poly;
        } else {
            crc <<= 1;
        }
    }

    crc ^= data & 0xFF;

    for(int j = 0; j < 8; j++) {
        if(crc & 0x80) {
            crc = (crc << 1) ^ poly;
        } else {
            crc <<= 1;
        }
    }

    return crc;
}
