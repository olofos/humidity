#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "rfm69.h"
#include "rtc.h"
#include "adc.h"
#include "shtc3.h"
#include "package.h"
#include "measurement.h"
#include "pretty-print.h"
#include "state.h"

#define PKG_VERSION 1

void construct_registration_package(struct pkg_buffer *p, uint8_t node_type, uint64_t hash)
{
    pkg_write_byte(p, PKG_REGISTER);
    pkg_write_byte(p, node_type);
    pkg_write_dword(p, (hash >> 32) & 0xFFFFFFFF);
    pkg_write_dword(p, hash & 0xFFFFFFFF);
    pkg_write_byte(p, PKG_VERSION);
}

void construct_measurement_package(struct pkg_buffer *p, struct measurement *measurement)
{
    pkg_write_byte(p, (measurement->retries == 0) ? PKG_MEASUREMENT : PKG_MEASUREMENT_REPEAT);
    pkg_write_timestamp(p, &measurement->timestamp);
    pkg_write_word(p, measurement->humidity_temperature.humidity);
    pkg_write_word(p, measurement->humidity_temperature.temperature);
    pkg_write_word(p, measurement->voltages.vcc);
    pkg_write_word(p, measurement->voltages.vmid);
}

void construct_debug_package(struct pkg_buffer *p, const struct pkg_timestamp *timestamp, const char *msg)
{
    pkg_write_byte(p, PKG_DEBUG);
    pkg_write_timestamp(p, timestamp);

    const int max_len = sizeof(p->buf) - 2 - sizeof(*timestamp) - 1;

    for(int n = 0; msg[n] && (n < max_len); n++) {
        pkg_write_byte(p, msg[n]);
    }
}

void construct_update_request_package(struct pkg_buffer *p, uint64_t old_hash, uint64_t new_hash, uint16_t address)
{
    pkg_write_byte(p, PKG_UPDATE_REQUEST);
    pkg_write_word(p, address);
    pkg_write_dword(p, (old_hash >> 32) & 0xFFFFFFFF);
    pkg_write_dword(p, old_hash & 0xFFFFFFFF);
    pkg_write_dword(p, (new_hash >> 32) & 0xFFFFFFFF);
    pkg_write_dword(p, new_hash & 0xFFFFFFFF);
}
