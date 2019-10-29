#ifndef PRETTY_PRINT_H_
#define PRETTY_PRINT_H_

void print_measurement(struct shtc3_measurement measurement);
void print_voltages(struct adc_supply_voltages voltages);
void print_timestamp(const struct pkg_timestamp *timestamp);

#endif
