#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

struct measurement {
    struct pkg_timestamp timestamp;
    struct shtc3_measurement humidity_temperature;
    struct adc_supply_voltages voltages;
};

void measurement_save(void);
void measurement_restore(void);

int measurement_add(const struct measurement *m);
int measurement_get(struct measurement *m);

#endif
