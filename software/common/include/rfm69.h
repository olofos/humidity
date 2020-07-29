#ifndef RFM69_H_
#define RFM69_H_

void rfm69_init(void);
void rfm69_deinit(void);
void rfm69_set_mode(uint8_t mode);

int rfm69_test(void);

uint8_t rfm69_get_version(void);
int rfm69_get_rssi(void);

void rfm69_set_node_address(uint8_t address);
void rfm69_set_aes_key(const uint8_t* key);

int rfm69_write(uint8_t address, const uint8_t *buf, uint8_t len);
int rfm69_read(uint8_t *buf, uint8_t len);

#define RFM69_MODE_SLEEP   (0x0 << 2)
#define RFM69_MODE_STANDBY (0x1 << 2)
#define RFM69_MODE_FS      (0x2 << 2)
#define RFM69_MODE_TX      (0x3 << 2)
#define RFM69_MODE_RX      (0x4 << 2)

#endif
