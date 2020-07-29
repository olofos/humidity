#ifndef RFM69_HAL_H_
#define RFM69_HAL_H_

void rfm69_hal_init(void);
void rfm69_hal_deinit(void);

void rfm69_hal_write_byte(uint8_t reg, uint8_t val);
void rfm69_hal_write(uint8_t reg, const uint8_t *buf, uint8_t len);

uint8_t rfm69_hal_read_byte(uint8_t reg);
void rfm69_hal_read(uint8_t reg, uint8_t *buf, uint8_t len);

// Wait for interrupts (two separate functions so that we can set separate timouts)
// Returns:
//   > 0  if interrupt fired
//   = 0  if timed out
//   < 0  on error

int rfm69_wait_for_payload_ready(void);
int rfm69_wait_for_packet_sent(void);

#endif
