#ifndef RFM69_HAL_H_
#define RFM69_HAL_H_

void rfm69_write_byte(uint8_t reg, uint8_t val);
void rfm69_write(uint8_t reg, uint8_t *buf, uint8_t len);

uint8_t rfm69_read_byte(uint8_t reg);
void rfm69_read(uint8_t reg, uint8_t *buf, uint8_t len);

void rfm69_fifo_write_begin(void);
void rfm69_fifo_write_byte(uint8_t val);
void rfm69_fifo_write(uint8_t *buf, uint8_t len);
void rfm69_fifo_write_end(void);

void rfm69_fifo_read_begin(void);
uint8_t rfm69_fifo_read_byte(void);
void rfm69_fifo_read(uint8_t *buf, uint8_t len);
void rfm69_fifo_read_end(void);

int rfm69_wait_for_packet(void);

#endif
