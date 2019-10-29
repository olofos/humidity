#include <stdint.h>
#include <stdio.h>

#include "shtc3.h"
#include "package-protocol.h"
#include "adc.h"
#include "measurement.h"
#include "pretty-print.h"

void print_timestamp(const struct pkg_timestamp *timestamp)
{
    printf("20%02X-%02X-%02X %02X:%02X:%02X\r\n",
           timestamp->year,
           timestamp->month,
           timestamp->day,
           timestamp->hour,
           timestamp->minute,
           timestamp->second);
}

void print_measurement(const struct measurement *measurement)
{
    printf("Timestamp:    ");
    print_timestamp(&measurement->timestamp);
    print_temperature(measurement->humidity_temperature.temperature);
    print_humidity(measurement->humidity_temperature.humidity);
    printf("Vcc:          %d.%dV\r\n", measurement->voltages.vcc >> ADC_VOLTAGE_SHIFT, (100 * (measurement->voltages.vcc & ((1<<ADC_VOLTAGE_SHIFT)-1))) >> ADC_VOLTAGE_SHIFT);
    printf("Vmid:         %d.%dV\r\n", measurement->voltages.vmid >> ADC_VOLTAGE_SHIFT, (100 * (measurement->voltages.vmid & ((1<<ADC_VOLTAGE_SHIFT)-1))) >> ADC_VOLTAGE_SHIFT);
}
