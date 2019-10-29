#include <stdint.h>
#include <stdio.h>

#include "shtc3.h"
#include "package-protocol.h"
#include "adc.h"
#include "pretty-print.h"

static void print_temperature(int16_t temperature)
{
    uint32_t t;
    char s;

    if(temperature >= 0) {
        s = ' ';
        t = temperature;
    } else {
        s = '-';
        t = -temperature;
    }

    int integer = t  >> SHTC3_TEMPERATURE_SHIFT;
    int fraction = (100 * (t & 0x00FF)) >> SHTC3_TEMPERATURE_SHIFT;

    printf("Temperature: %c%d.%02dC\r\n", s, integer, fraction);
}

static void print_humidity(uint16_t humidity)
{
    uint32_t h = humidity * 100;
    int integer = h  >> 16;
    int fraction = (100 * (h & 0x0000FFFF)) >> 16;

    printf("Humidity:     %d.%02d%%\r\n", integer, fraction);
}

void print_measurement(struct shtc3_measurement measurement)
{
    print_temperature(measurement.temperature);
    print_humidity(measurement.humidity);
}

void print_voltages(struct adc_supply_voltages voltages)
{
    printf("Vcc:          %d.%dV\r\n", voltages.vcc >> ADC_VOLTAGE_SHIFT, (100 * (voltages.vcc & ((1<<ADC_VOLTAGE_SHIFT)-1))) >> ADC_VOLTAGE_SHIFT);
    printf("Vmid:         %d.%dV\r\n", voltages.vmid >> ADC_VOLTAGE_SHIFT, (100 * (voltages.vmid & ((1<<ADC_VOLTAGE_SHIFT)-1))) >> ADC_VOLTAGE_SHIFT);
}

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
