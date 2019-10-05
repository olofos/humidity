#ifndef RFM69_H_
#define RFM69_H_

struct rfm69_packet {
    uint8_t len;
    uint8_t *buf;
};

void rfm69_init(void);
uint8_t rfm69_get_version(void);
void rfm69_set_mode(uint8_t mode);
void rfm69_send(uint8_t *buf, uint8_t len);
struct rfm69_packet *rfm69_receive(void);

#define RFM69_MODE_SLEEP   (0x0 << 2)
#define RFM69_MODE_STANDBY (0x1 << 2)
#define RFM69_MODE_FS      (0x2 << 2)
#define RFM69_MODE_TX      (0x3 << 2)
#define RFM69_MODE_RX      (0x4 << 2)

#endif
