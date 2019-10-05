#ifndef RFM69_REGISTERS_H_
#define RFM69_REGISTERS_H_

#define RFM69_REG_FIFO           0x00
#define RFM69_REG_OP_MODE        0x01
#define RFM69_REG_DATA_MODUL     0x02
#define RFM69_REG_BITRATE_MSB    0x03
#define RFM69_REG_BITRATE_LSB    0x04
#define RFM69_REG_FDEV_MSB       0x05
#define RFM69_REG_FDEV_LSB       0x06
#define RFM69_REG_FRF_MSB        0x07
#define RFM69_REG_FRF_MID        0x08
#define RFM69_REG_FRF_LSB        0x09
#define RFM69_REG_OSC1           0x0A
#define RFM69_REG_AFC_CTRL       0x0B
#define RFM69_REG_LISTEN1        0x0D
#define RFM69_REG_LISTEN2        0x0E
#define RFM69_REG_LISTEN3        0x0F
#define RFM69_REG_VERSION        0x10
#define RFM69_REG_PA_LEVEL       0x11
#define RFM69_REG_PA_RAMP        0x12
#define RFM69_REG_OCP            0x13
#define RFM69_REG_LNA            0x18
#define RFM69_REG_RX_BW          0x19
#define RFM69_REG_AFC_BW         0x1A
#define RFM69_REG_OOK_PEAK       0x1B
#define RFM69_REG_OOK_AVG        0x1C
#define RFM69_REG_OOK_FIX        0x1D
#define RFM69_REG_AFC_FEI        0x1E
#define RFM69_REG_AFC_MSB        0x1F
#define RFM69_REG_AFC_LSB        0x20
#define RFM69_REG_FEI_MSB        0x21
#define RFM69_REG_FEI_LSB        0x22
#define RFM69_REG_RSSI_CONFIG    0x23
#define RFM69_REG_RSSI_VALUE     0x24
#define RFM69_REG_DIO_MAPPING1   0x25
#define RFM69_REG_DIO_MAPPING2   0x26
#define RFM69_REG_IRQ_FLAGS1     0x27
#define RFM69_REG_IRQ_FLAGS2     0x28
#define RFM69_REG_RSSI_THRESH    0x29
#define RFM69_REG_RX_TIMEOUT1    0x2A
#define RFM69_REG_RX_TIMEOUT2    0x2B
#define RFM69_REG_PREAMBLE_MSB   0x2C
#define RFM69_REG_PREAMBLE_LSB   0x2D
#define RFM69_REG_SYNC_CONFIG    0x2E
#define RFM69_REG_SYNC_VALUE1    0x2F
#define RFM69_REG_SYNC_VALUE2    0x30
#define RFM69_REG_SYNC_VALUE3    0x31
#define RFM69_REG_SYNC_VALUE4    0x32
#define RFM69_REG_SYNC_VALUE5    0x33
#define RFM69_REG_SYNC_VALUE6    0x34
#define RFM69_REG_SYNC_VALUE7    0x35
#define RFM69_REG_SYNC_VALUE8    0x36
#define RFM69_REG_PACKET_CONFIG1 0x37
#define RFM69_REG_PAYLOAD_LENGTH 0x38
#define RFM69_REG_NODE_ADRS      0x39
#define RFM69_REG_BROADCAST_ADRS 0x3A
#define RFM69_REG_AUTO_MODES     0x3B
#define RFM69_REG_FIFO_THRESH    0x3C
#define RFM69_REG_PACKET_CONFIG2 0x3D
#define RFM69_REG_AES_KEY1       0x3E
#define RFM69_REG_AES_KEY2       0x3F
#define RFM69_REG_AES_KEY3       0x40
#define RFM69_REG_AES_KEY4       0x41
#define RFM69_REG_AES_KEY5       0x42
#define RFM69_REG_AES_KEY6       0x43
#define RFM69_REG_AES_KEY7       0x44
#define RFM69_REG_AES_KEY8       0x45
#define RFM69_REG_AES_KEY9       0x46
#define RFM69_REG_AES_KEY10      0x47
#define RFM69_REG_AES_KEY11      0x48
#define RFM69_REG_AES_KEY12      0x49
#define RFM69_REG_AES_KEY13      0x4A
#define RFM69_REG_AES_KEY14      0x4B
#define RFM69_REG_AES_KEY15      0x4C
#define RFM69_REG_AES_KEY16      0x4D
#define RFM69_REG_TEMP1          0x4E
#define RFM69_REG_TEMP2          0x4F
#define RFM69_REG_TEST_LNA       0x58
#define RFM69_REG_TEST_PA1       0x5A
#define RFM69_REG_TEST_PA2       0x5C
#define RFM69_REG_TEST_DAGC      0x6F
#define RFM69_REG_TEST_AFC       0x71

#define RFM69_REG_READ           0x00
#define RFM69_REG_WRITE          0x80

#define RFM69_PA1_NORMAL 0x55
#define RFM69_PA1_BOOST  0x5D
#define RFM69_PA2_NORMAL 0x70
#define RFM69_PA2_BOOST  0x7C

#define RFM69_OP_MODE_SEQ_OFF 0x80
#define RFM69_OP_MODE_LISTEN_ON 0x40
#define RFM69_OP_MODE_LISTEN_ABORT 0x20
#define RFM69_OP_MODE_MASK 0x1C

#define RFM69_DATA_MODUL_PACKET_MODE    (0x00 << 5)
#define RFM69_DATA_MODUL_CONT_SYNC_MODE (0x10 << 5)
#define RFM69_DATA_MODUL_CONT_MODE      (0x11 << 5)
#define RFM69_DATA_MODUL_FSK            (0x00 << 3)
#define RFM69_DATA_MODUL_OOK            (0x01 << 3)
#define RFM69_DATA_MODUL_NO_SHAPING     0x00
#define RFM69_DATA_MODUL_GAUSSIAN_10    0x01
#define RFM69_DATA_MODUL_GAUSSIAN_05    0x02
#define RFM69_DATA_MODUL_GAUSSIAN_03    0x03
#define RFM69_DATA_MODUL_FILTER_BR      0x01
#define RFM69_DATA_MODUL_FILTER_2BR     0x02

#define RFM69_PACKET_CONFIG1_FORMAT_FIXED             (0 << 7)
#define RFM69_PACKET_CONFIG1_FORMAT_VARIABLE          (1 << 7)

#define RFM69_PACKET_CONFIG1_DC_NONE                  (0 << 5)
#define RFM69_PACKET_CONFIG1_DC_MANCHESTER            (1 << 5)
#define RFM69_PACKET_CONFIG1_DC_WHITENING             (2 << 5)

#define RFM69_PACKET_CONFIG1_CRC_OFF                  (0 << 4)
#define RFM69_PACKET_CONFIG1_CRC_ON                   (1 << 4)

#define RFM69_PACKET_CONFIG1_CRC_CLEAR                (0 << 3)
#define RFM69_PACKET_CONFIG1_CRC_NOCLEAR              (1 << 3)

#define RFM69_PACKET_CONFIG1_ADDRESS_FILTER_NONE      (0 << 1)
#define RFM69_PACKET_CONFIG1_ADDRESS_FILTER           (1 << 1)
#define RFM69_PACKET_CONFIG1_ADDRESS_FILTER_BROADCAST (2 << 1)


#define RFM69_PACKET_CONFIG2_AES_OFF  0x00
#define RFM69_PACKET_CONFIG2_AES_ON   0x01
#define RFM69_PACKET_CONFIG2_AUTO_RX_RESTART_OFF  0x02
#define RFM69_PACKET_CONFIG2_AUTO_RX_RESTART_ON  0x02
#define RFM69_PACKET_CONFIG2_RX_RESTART  0x04

#define RFM69_PA_LEVEL_PA0 0x80
#define RFM69_PA_LEVEL_PA1 0x40
#define RFM69_PA_LEVEL_PA2 0x20

#define RFM69_SYNC_CONFIG_SYNC_ON   0x80
#define RFM69_SYNC_CONFIG_SIZE_POS  3
#define RFM69_SYNC_CONFIG_SIZE_MASK (0x07 << RFM69_SYNC_CONFIG_SIZE_POS)

#define RFM69_IRQ1_MODE_READY 0x80
#define RFM69_IRQ1_RX_READY   0x40
#define RFM69_IRQ1_TX_READY   0x20
#define RFM69_IRQ1_PLL_LOCK   0x10
#define RFM69_IRQ1_RSSI       0x08
#define RFM69_IRQ1_TIMEOUT    0x04
#define RFM69_IRQ1_AUTO_MODE  0x02
#define RFM69_IRQ1_SYNC_ADDR  0x01

#define RFM69_IRQ2_FIFO_FULL      0x80
#define RFM69_IRQ2_FIFO_NOT_EMPTY 0x40
#define RFM69_IRQ2_FIFO_LEVEL     0x20
#define RFM69_IRQ2_FIFO_OVERRUN   0x10
#define RFM69_IRQ2_PACKET_SENT    0x08
#define RFM69_IRQ2_PAYLOAD_READY  0x04
#define RFM69_IRQ2_CRC_OK         0x02

#define RFM69_DIO0_MAP_TX 0x00
#define RFM69_DIO0_MAP_RX 0x01

#define RFM69_BIT_RATE 250000UL
#define RFM69_FDEV     250000UL
#define RFM69_FREQUENCY 433000000UL

#define RFM69_PREAMBLE_LEN 4

#endif
