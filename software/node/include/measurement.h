#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

struct measurement {
    struct pkg_timestamp timestamp;
    struct shtc3_measurement humidity_temperature;
    struct adc_supply_voltages voltages;
    uint8_t retries;
};

int measurement_add(const struct measurement *m);
struct measurement *measurement_get(void);
void measurement_handled(void);
int measurement_empty(void);

#endif
