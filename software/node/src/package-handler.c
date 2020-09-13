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
