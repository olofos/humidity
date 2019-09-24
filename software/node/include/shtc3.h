#ifndef SHTC3_H_
#define SHTC3_H_

int shtc3_read(int32_t *temperature, uint32_t *humidity);
int shtc3_wakeup(void);
int shtc3_sleep(void);
int shtc3_read_id(uint16_t *id);
uint16_t shtc3_test(void);

#endif
