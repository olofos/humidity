#ifndef RFM69_HAL_H_
#define RFM69_HAL_H_

void rfm69_write_byte(uint8_t reg, uint8_t val);
void rfm69_write(uint8_t reg, uint8_t *buf, uint8_t len);

uint8_t rfm69_read_byte(uint8_t reg);
void rfm69_read(uint8_t reg, uint8_t *buf, uint8_t len);

int rfm69_wait_for_payload_ready(void);
int rfm69_wait_for_packet_sent(void);

#endif
