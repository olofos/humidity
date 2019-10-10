#include <stdint.h>
#include <errno.h>

#include "rfm69-config.h"
#include "rfm69-registers.h"
#include "rfm69-hal.h"
#include "rfm69.h"

#define RFM69_OSC_FREQ 32000000UL
#define RFM69_FSTEP    (((double) RFM69_OSC_FREQ) / (1 << 19))

#define RFM69_BIT_RATE_DIV ((uint16_t) (((double) RFM69_OSC_FREQ / RFM69_BIT_RATE) + 0.5))
#define RFM69_FDEV_DIV ((uint16_t) ((RFM69_FDEV / RFM69_FSTEP) + 0.5))
#define RFM69_FREQ_DIV ((uint32_t) (RFM69_FREQUENCY / RFM69_FSTEP))

static uint8_t rfm69_sync_word[] = RFM69_SYNC_WORD;
static uint8_t rfm69_pa_boost;
static uint8_t rfm69_temp_buf[64];

// Follow Adafruits circuit python driver
// https://github.com/adafruit/Adafruit_CircuitPython_RFM69/blob/master/adafruit_rfm69.py

static void rfm69_wait_irq1(uint8_t flag)
{
    while(!(rfm69_hal_read_byte(RFM69_REG_IRQ_FLAGS1) & flag))
        ;
}

void rfm69_set_mode(uint8_t mode)
{
    // Note: does not support SequencerOff or Listen Mode
    rfm69_hal_write_byte(RFM69_REG_OP_MODE, mode);

    rfm69_wait_irq1(RFM69_IRQ1_MODE_READY);
}

void rfm69_set_tx_power(int power)
{
    if(!((-2 <= power) && (power <= 20))) {
        // Out of range error
        return;
    }

    if(power <= 13) {
        rfm69_hal_write_byte(RFM69_REG_PA_LEVEL, RFM69_PA_LEVEL_PA1 | (power + 18));
        rfm69_pa_boost = 0;
    }  else if(power <= 17) {
        rfm69_hal_write_byte(RFM69_REG_PA_LEVEL, RFM69_PA_LEVEL_PA1 | RFM69_PA_LEVEL_PA2 | (power + 14));
        rfm69_pa_boost = 0;
    } else {
        // Need to turn on PA boost!
        rfm69_hal_write_byte(RFM69_REG_PA_LEVEL, RFM69_PA_LEVEL_PA1 | RFM69_PA_LEVEL_PA2 | (power + 11));
        rfm69_pa_boost = 1;
    }
}

void rfm69_init(void)
{
    rfm69_hal_init();

    rfm69_set_mode(RFM69_MODE_STANDBY);

    rfm69_hal_write_byte(RFM69_REG_FIFO_THRESH, 0x8F);          // Start packet transmission when FIFO not empty
    rfm69_hal_write_byte(RFM69_REG_TEST_DAGC, 0x30);            // Disable low beta
    rfm69_hal_write_byte(RFM69_REG_TEST_PA1, RFM69_PA1_NORMAL); // Disable boost
    rfm69_hal_write_byte(RFM69_REG_TEST_PA2, RFM69_PA2_NORMAL);
    rfm69_hal_write(RFM69_REG_SYNC_VALUE1, rfm69_sync_word, sizeof(rfm69_sync_word));
    rfm69_hal_write_byte(RFM69_REG_SYNC_CONFIG, RFM69_SYNC_CONFIG_SYNC_ON | ((sizeof(rfm69_sync_word) - 1) << RFM69_SYNC_CONFIG_SIZE_POS));

    rfm69_hal_write_byte(RFM69_REG_DATA_MODUL, RFM69_DATA_MODUL_PACKET_MODE | RFM69_DATA_MODUL_FSK | RFM69_DATA_MODUL_GAUSSIAN_10);

    rfm69_hal_write_byte(RFM69_REG_BITRATE_MSB, (RFM69_BIT_RATE_DIV >> 8) & 0xFF);
    rfm69_hal_write_byte(RFM69_REG_BITRATE_LSB, RFM69_BIT_RATE_DIV & 0xFF);

    rfm69_hal_write_byte(RFM69_REG_FDEV_MSB, (RFM69_FDEV_DIV >> 8) & 0xFF);
    rfm69_hal_write_byte(RFM69_REG_FDEV_LSB, RFM69_FDEV_DIV & 0xFF);

    rfm69_hal_write_byte(RFM69_REG_RX_BW, 0xE0); // ??
    rfm69_hal_write_byte(RFM69_REG_AFC_BW, 0xE0); // ??

    rfm69_hal_write_byte(RFM69_REG_PACKET_CONFIG1, RFM69_PACKET_CONFIG1_FORMAT_VARIABLE | RFM69_PACKET_CONFIG1_DC_WHITENING | RFM69_PACKET_CONFIG1_CRC_ON | RFM69_PACKET_CONFIG1_CRC_CLEAR | RFM69_PACKET_CONFIG1_ADDRESS_FILTER);

    rfm69_hal_write_byte(RFM69_REG_PREAMBLE_MSB, (RFM69_PREAMBLE_LEN >> 8) & 0xFF);
    rfm69_hal_write_byte(RFM69_REG_PREAMBLE_LSB, RFM69_PREAMBLE_LEN & 0xFF);

    rfm69_hal_write_byte(RFM69_REG_FRF_MSB, (RFM69_FREQ_DIV >> 16) & 0xFF);
    rfm69_hal_write_byte(RFM69_REG_FRF_MID, (RFM69_FREQ_DIV >> 8) & 0xFF);
    rfm69_hal_write_byte(RFM69_REG_FRF_LSB, RFM69_FREQ_DIV & 0xFF);

    rfm69_hal_write_byte(RFM69_REG_PACKET_CONFIG2, RFM69_PACKET_CONFIG2_AUTO_RX_RESTART_ON); // Keep default

    rfm69_set_tx_power(1);
}

void rfm69_deinit(void)
{
    rfm69_hal_deinit();
}

uint8_t rfm69_get_version(void)
{
    return rfm69_hal_read_byte(RFM69_REG_VERSION);
}

// The RSSI in dBm is given by -rfm69_get_rssi() / 2
int rfm69_get_rssi(void)
{
    return rfm69_hal_read_byte(RFM69_REG_RSSI_VALUE);
}

void rfm69_set_node_address(uint8_t address)
{
    rfm69_hal_write_byte(RFM69_REG_NODE_ADRS, address);
}

int rfm69_write(uint8_t address, uint8_t *buf, uint8_t len)
{
    if(len > 63) {
        len = 63;
    }

    uint8_t header[] = {
        len + 1,
        address,
    };

    rfm69_hal_write(RFM69_REG_FIFO, header, sizeof(header));
    rfm69_hal_write(RFM69_REG_FIFO, buf, len);

    if(rfm69_pa_boost) {
        rfm69_hal_write_byte(RFM69_REG_TEST_PA1, RFM69_PA1_BOOST);
        rfm69_hal_write_byte(RFM69_REG_TEST_PA2, RFM69_PA2_BOOST);
    }

    rfm69_hal_write_byte(RFM69_REG_DIO_MAPPING1, RFM69_DIO0_MAP_TX);
    rfm69_set_mode(RFM69_MODE_TX);

    int ret = rfm69_wait_for_packet_sent();

    rfm69_set_mode(RFM69_MODE_STANDBY);

    if(rfm69_pa_boost) {
        rfm69_hal_write_byte(RFM69_REG_TEST_PA1, RFM69_PA1_NORMAL);
        rfm69_hal_write_byte(RFM69_REG_TEST_PA2, RFM69_PA2_NORMAL);
    }

    if(ret <= 0) {
        return ret;
    } else {
        return len;
    }
}

int rfm69_read(uint8_t *buf, uint8_t n)
{
    rfm69_hal_write_byte(RFM69_REG_DIO_MAPPING1, RFM69_DIO0_MAP_RX);
    rfm69_set_mode(RFM69_MODE_RX);

    int ret = rfm69_wait_for_payload_ready();

    rfm69_set_mode(RFM69_MODE_STANDBY);

    if(ret <= 0) {
        return ret;
    }

    uint8_t len = rfm69_hal_read_byte(RFM69_REG_FIFO);

    if(len > n) {
        rfm69_hal_read(RFM69_REG_FIFO, buf, n);
        rfm69_hal_read(RFM69_REG_FIFO, rfm69_temp_buf, len - n);
        return n;
    } else {
        rfm69_hal_read(RFM69_REG_FIFO, buf, len);
        return len;
    }
}
