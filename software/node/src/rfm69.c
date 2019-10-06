#include <stdint.h>
#include <stdio.h>
#include "rfm69-registers.h"
#include "rfm69-hal.h"
#include "rfm69.h"

#define RFM69_OSC_FREQ 32000000UL
#define RFM69_FSTEP    (((double) RFM69_OSC_FREQ) / (1 << 19))

#define RFM69_BIT_RATE_DIV ((uint16_t) (((double) RFM69_OSC_FREQ / RFM69_BIT_RATE) + 0.5))
#define RFM69_FDEV_DIV ((uint16_t) ((RFM69_FDEV / RFM69_FSTEP) + 0.5))
#define RFM69_FREQ_DIV ((uint32_t) (RFM69_FREQUENCY / RFM69_FSTEP))

static uint8_t rfm69_sync_word[] = { 0x2D, 0xD4 };
static uint8_t rfm69_pa_boost;

uint8_t rfm69_packet_buf[64];
struct rfm69_packet rfm69_packet = {
    .len = 0,
    .buf = rfm69_packet_buf,
};

// Follow Adafruits circuit python driver
// https://github.com/adafruit/Adafruit_CircuitPython_RFM69/blob/master/adafruit_rfm69.py

static void rfm69_wait_irq1(uint8_t flag)
{
    while(!(rfm69_read_byte(RFM69_REG_IRQ_FLAGS1) & flag))
        ;
}

void rfm69_set_mode(uint8_t mode)
{
    // Note: does not support SequencerOff or Listen Mode
    rfm69_write_byte(RFM69_REG_OP_MODE, mode);

    rfm69_wait_irq1(RFM69_IRQ1_MODE_READY);
}

void rfm69_set_tx_power(int power)
{
    if(!((-2 <= power) && (power <= 20))) {
        // Out of range error
        return;
    }

    if(power <= 13) {
        rfm69_write_byte(RFM69_REG_PA_LEVEL, RFM69_PA_LEVEL_PA1 | (power + 18));
        rfm69_pa_boost = 0;
    }  else if(power <= 17) {
        rfm69_write_byte(RFM69_REG_PA_LEVEL, RFM69_PA_LEVEL_PA1 | RFM69_PA_LEVEL_PA2 | (power + 14));
        rfm69_pa_boost = 0;
    } else {
        // Need to turn on PA boost!
        rfm69_write_byte(RFM69_REG_PA_LEVEL, RFM69_PA_LEVEL_PA1 | RFM69_PA_LEVEL_PA2 | (power + 11));
        rfm69_pa_boost = 1;
    }
}

void rfm69_init(void)
{
    rfm69_set_mode(RFM69_MODE_STANDBY);

    rfm69_write_byte(RFM69_REG_FIFO_THRESH, 0x8F);          // Start packet transmission when FIFO not empty
    rfm69_write_byte(RFM69_REG_TEST_DAGC, 0x30);            // Disable low beta
    rfm69_write_byte(RFM69_REG_TEST_PA1, RFM69_PA1_NORMAL); // Disable boost
    rfm69_write_byte(RFM69_REG_TEST_PA2, RFM69_PA2_NORMAL);
    rfm69_write(RFM69_REG_SYNC_VALUE1, rfm69_sync_word, sizeof(rfm69_sync_word));
    rfm69_write_byte(RFM69_REG_SYNC_CONFIG, RFM69_SYNC_CONFIG_SYNC_ON | ((sizeof(rfm69_sync_word) - 1) << RFM69_SYNC_CONFIG_SIZE_POS));

    rfm69_write_byte(RFM69_REG_DATA_MODUL, RFM69_DATA_MODUL_PACKET_MODE | RFM69_DATA_MODUL_FSK | RFM69_DATA_MODUL_GAUSSIAN_10);

    rfm69_write_byte(RFM69_REG_BITRATE_MSB, (RFM69_BIT_RATE_DIV >> 8) & 0xFF);
    rfm69_write_byte(RFM69_REG_BITRATE_LSB, RFM69_BIT_RATE_DIV & 0xFF);

    rfm69_write_byte(RFM69_REG_FDEV_MSB, (RFM69_FDEV_DIV >> 8) & 0xFF);
    rfm69_write_byte(RFM69_REG_FDEV_LSB, RFM69_FDEV_DIV & 0xFF);

    rfm69_write_byte(RFM69_REG_RX_BW, 0xE0); // ??
    rfm69_write_byte(RFM69_REG_AFC_BW, 0xE0); // ??

    rfm69_write_byte(RFM69_REG_PACKET_CONFIG1, RFM69_PACKET_CONFIG1_FORMAT_VARIABLE | RFM69_PACKET_CONFIG1_DC_WHITENING | RFM69_PACKET_CONFIG1_CRC_ON | RFM69_PACKET_CONFIG1_CRC_CLEAR | RFM69_PACKET_CONFIG1_ADDRESS_FILTER_NONE);

    rfm69_write_byte(RFM69_REG_PREAMBLE_MSB, (RFM69_PREAMBLE_LEN >> 8) & 0xFF);
    rfm69_write_byte(RFM69_REG_PREAMBLE_LSB, RFM69_PREAMBLE_LEN & 0xFF);

    rfm69_write_byte(RFM69_REG_FRF_MSB, (RFM69_FREQ_DIV >> 16) & 0xFF);
    rfm69_write_byte(RFM69_REG_FRF_MID, (RFM69_FREQ_DIV >> 8) & 0xFF);
    rfm69_write_byte(RFM69_REG_FRF_LSB, RFM69_FREQ_DIV & 0xFF);

    rfm69_write_byte(RFM69_REG_PACKET_CONFIG2, RFM69_PACKET_CONFIG2_AUTO_RX_RESTART_ON); // Keep default

    rfm69_set_tx_power(13);
}

uint8_t rfm69_get_version(void)
{
    return rfm69_read_byte(RFM69_REG_VERSION);
}




void rfm69_send(uint8_t *buf, uint8_t len)
{
    uint8_t header[5] = { len + 4, 0xFF, 0xFF, 0x00, 0x00 };

    rfm69_write(RFM69_REG_FIFO, header, sizeof(header));
    rfm69_write(RFM69_REG_FIFO, buf, len);

    if(rfm69_pa_boost) {
        rfm69_write_byte(RFM69_REG_TEST_PA1, RFM69_PA1_BOOST);
        rfm69_write_byte(RFM69_REG_TEST_PA2, RFM69_PA2_BOOST);
    }

    rfm69_write_byte(RFM69_REG_DIO_MAPPING1, RFM69_DIO0_MAP_TX);
    rfm69_set_mode(RFM69_MODE_TX);

    rfm69_wait_for_packet_sent();

    printf("RFM69 Flags: %02X %02X\r\n", rfm69_read_byte(RFM69_REG_IRQ_FLAGS1), rfm69_read_byte(RFM69_REG_IRQ_FLAGS2));

    rfm69_set_mode(RFM69_MODE_STANDBY);

    if(rfm69_pa_boost) {
        rfm69_write_byte(RFM69_REG_TEST_PA1, RFM69_PA1_NORMAL);
        rfm69_write_byte(RFM69_REG_TEST_PA2, RFM69_PA2_NORMAL);
    }
}

struct rfm69_packet *rfm69_receive(void)
{
    rfm69_write_byte(RFM69_REG_DIO_MAPPING1, RFM69_DIO0_MAP_RX);
    rfm69_set_mode(RFM69_MODE_RX);

    if(!rfm69_wait_for_payload_ready()) {
        rfm69_set_mode(RFM69_MODE_STANDBY);
        return NULL;
    }

    rfm69_set_mode(RFM69_MODE_STANDBY);

    uint8_t len = rfm69_read_byte(RFM69_REG_FIFO);

    if(len < 4) {
        // Handle invalid packet
        return NULL;
    } else {
        rfm69_read(RFM69_REG_FIFO, rfm69_packet.buf, len);
        rfm69_packet.len = len;

        return &rfm69_packet;
    }
}
