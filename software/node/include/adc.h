#ifndef ADC_H_
#define ADC_H_

#define ADC_VOLTAGE_SHIFT 12

struct supply_voltages {
    uint16_t vcc;
    uint16_t vmid;
};

void adc_init(void);
void adc_deinit(void);
int adc_measure_voltages(struct supply_voltages *voltages);

#endif
