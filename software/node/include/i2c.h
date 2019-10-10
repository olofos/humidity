#ifndef I2C_H_
#define I2C_H_

#define I2C_OK 1
#define I2C_ERROR 0

void i2c_init(void);
void i2c_deinit(void);

int i2c_check(uint8_t i2c_address, uint32_t start, uint32_t timeout);
int i2c_register_read(uint8_t i2c_address, uint16_t reg, uint8_t *buf, uint8_t num, uint32_t start, uint32_t timeout);
int i2c_register_write(uint8_t i2c_address, uint16_t reg, const uint8_t *buf, uint8_t num, uint32_t start, uint32_t timeout);

#endif
