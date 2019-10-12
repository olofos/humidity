#ifndef SHTC3_H_
#define SHTC3_H_

struct shtc3_measurement {
    uint16_t humidity;
    uint16_t temperature;
};

int shtc3_read(struct shtc3_measurement *measurement);
int shtc3_wakeup(void);
int shtc3_sleep(void);
int shtc3_read_id(uint16_t *id);
uint16_t shtc3_test(void);

#endif
