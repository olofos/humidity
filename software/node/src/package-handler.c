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


void construct_measurement_package(struct pkg_buffer *p, struct measurement *measurement)
{
    pkg_write_byte(p, (measurement->retries == 0) ? PKG_MEASUREMENT : PKG_MEASUREMENT_REPEAT);
    pkg_write_timestamp(p, &measurement->timestamp);
    pkg_write_word(p, measurement->humidity_temperature.humidity);
    pkg_write_word(p, measurement->humidity_temperature.temperature);
    pkg_write_word(p, measurement->voltages.vcc);
    pkg_write_word(p, measurement->voltages.vmid);
}
