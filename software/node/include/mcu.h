#ifndef MCU_H_
#define MCU_H_

#define SLEEP_MODE_NONE    0x00
#define SLEEP_MODE_SLEEP   0x01
#define SLEEP_MODE_DEEP    0x02
#define SLEEP_MODE_STANDBY 0x03

uint8_t read_config(void);
void sleep(uint8_t mode, uint16_t period);
uint32_t mcu_init(void);

void ledr_on(void);
void ledr_off(void);
uint32_t button_pushed(void);


#endif
