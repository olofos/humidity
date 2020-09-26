#include <stdint.h>
#include "crc32.h"

// Reflection of 0x04C11DB7
#define POLY 0xEDB88320

#if defined(CRC32_USE_TABLE) && CRC32_USE_TABLE

static uint32_t crc32_tab[256];
static uint8_t crc32_tab_init = 0;

void init_crc32_tab(void)
{
    for(int i = 0; i < 256; i++) {
        uint32_t c = i;
        uint32_t crc = 0;
        for(int j = 0; j < 8; j++) {
            if((c ^ crc) & 1) {
                crc = (crc >> 1) ^ POLY;
            } else {
                crc >>= 1;
            }
            c >>= 1;
        }
        crc32_tab[i] = crc;
    }
    crc32_tab_init = 1;
}

uint32_t crc32(uint8_t *buf, uint32_t len)
{
    if(!crc32_tab_init) init_crc32_tab();

    uint32_t crc = 0xFFFFFFFF;

    for(uint32_t i = 0; i < len; i++) {
        int index = (buf[i] ^ crc) & 0xFF;
        crc = (crc >> 8) ^ crc32_tab[index];
    }
    return ~crc;
}


#else

uint32_t crc32(uint8_t *buf, uint32_t len)
{
    uint32_t crc = 0xFFFFFFFF;

    for(uint32_t i = 0; i < len; i++) {
        uint32_t c = buf[i];
        for(int j = 0; j < 8; j++) {
            if((c ^ crc) & 1) {
                crc = (crc >> 1) ^ POLY;
            } else {
                crc >>= 1;
            }
            c >>= 1;
        }
    }
    return ~crc;
}

#endif
