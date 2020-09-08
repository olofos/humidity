#include <inttypes.h>
#include <stdio.h>
#include <time.h>

#include "rfm69.h"
#include "db.h"
#include "package.h"
#include "package-handler.h"
#include "node.h"
#include "firmware.h"

#define SHTC3_TEMPERATURE_SHIFT 8
#define SHTC3_HUMIDITY_SHIFT 16
#define ADC_VOLTAGE_SHIFT 12

// Maximum allowed time difference in seconds
#define MAX_TIME_DIFF 5

static uint8_t from_bcd(uint8_t n)
{
    return 10 * (n >> 4) + (n & 0x0F);
}

static uint8_t to_bcd(uint8_t n)
{
    const uint8_t tens = n / 10;
    const uint8_t units = n % 10;

    return (tens << 4) | units;
}

static struct pkg_timestamp convert_time_to_pkg_timestamp(time_t t)
{
    struct tm tm;
    gmtime_r(&t, &tm);

    struct pkg_timestamp timestamp = {
        .year = to_bcd(tm.tm_year - 100),
        .month = to_bcd(tm.tm_mon + 1),
        .day = to_bcd(tm.tm_mday),
        .hour = to_bcd(tm.tm_hour),
        .minute = to_bcd(tm.tm_min),
        .second = to_bcd(tm.tm_sec),
    };

    return timestamp;
}

static time_t convert_pkg_timestamp_to_time(struct pkg_timestamp timestamp)
{
    struct tm tm = {
        .tm_year = 100 + from_bcd(timestamp.year),
        .tm_mon = from_bcd(timestamp.month) - 1,
        .tm_mday = from_bcd(timestamp.day),
        .tm_hour = from_bcd(timestamp.hour),
        .tm_min = from_bcd(timestamp.minute),
        .tm_sec = from_bcd(timestamp.second),
    };

    return mktime(&tm);
}

static const char *format_time(time_t *tp)
{
    struct tm *tmp = localtime(tp);
    static char s[20];
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S%z", tmp);
    return s;
}

static void send_ack(struct pkg_buffer *p, struct node *node, time_t timestamp)
{
    uint8_t flags = 0;
    uint64_t latest_fw_hash;

    if(node) {
        if(!db_check_firmware_is_uptodate(node->firmware_hash)) {
            if(!firmware_file_exists(node->firmware_hash)) {
                printf("Missing firmware for %016" PRIX64 "\n", node->firmware_hash);
            } else {
                latest_fw_hash = db_get_latest_firmware_hash();
                if(!firmware_file_exists(latest_fw_hash)) {
                    printf("Missing firmware for %016" PRIX64 "\n", latest_fw_hash);
                } else {
                    flags |= PKG_FLAG_UPDATE_AVAILABLE;
                    printf("Update available\n");
                }
            }
        } else {
            printf("Up to date\n");
        }
    } else {
        printf("Node not found!\n");
    }

    time_t now = time(0);
    if(timestamp != -1) {
        time_t diff = now - timestamp;
        if((diff > MAX_TIME_DIFF) || (diff < -MAX_TIME_DIFF)) {
            flags |= PKG_FLAG_SET_TIME;
        }
    }

    pkg_write_byte(p, PKG_ACK);
    pkg_write_byte(p, flags);

    if(flags & PKG_FLAG_UPDATE_AVAILABLE) {

        pkg_write_dword(p, (latest_fw_hash >> 32) & 0xFFFFFFFF);
        pkg_write_dword(p, latest_fw_hash & 0xFFFFFFFF);
    }

    if(flags & PKG_FLAG_SET_TIME) {
        struct pkg_timestamp pkg_timestamp = convert_time_to_pkg_timestamp(now);
        pkg_write_timestamp(p, &pkg_timestamp);
    }
}

static void handle_package_register(struct pkg_buffer *p, uint8_t request, int len, uint8_t node_id)
{
    uint8_t node_type = pkg_read_byte(p);

    uint64_t hash1 = pkg_read_dword(p);
    uint32_t hash2 = pkg_read_dword(p);
    uint64_t hash = (hash1 << 32) | hash2;

    if(hash & (1ULL << 63)) {
        printf("Expected a 63 bit hash. Truncating.\n");
        hash &= ~(1ULL << 63);
    }

    uint8_t protocol_version = 0;
    if(len > 10) {
        protocol_version = pkg_read_byte(p);

        if(protocol_version > PROTOCOL_VERSION_MAX) {
            printf("Unkown protocol version. Defaulting to 0\n");
            protocol_version = 0;
        }
    }

    if(db_register_node(node_id, node_type, hash) == DB_OK) {
        struct node *node = node_register(node_id, hash, protocol_version);
        if(node) {
            if(protocol_version > 0) {
                send_ack(p, node, 0);
            } else {
                struct pkg_timestamp pkg_timestamp = convert_time_to_pkg_timestamp(time(0));

                pkg_write_byte(p, PKG_SET_TIME);
                pkg_write_timestamp(p, &pkg_timestamp);
            }

            printf("New node\n");
            printf("Node id:    %d\n", node_id);
            printf("Type:       %d\n", node_type);
            printf("Hash:       %016" PRIX64 "\n", hash);
            printf("Protocol:   %d\n", protocol_version);

            return;
        }
    }

    pkg_write_byte(p, PKG_NACK);
    pkg_write_byte(p, 0x00);

    printf("Error when registering node\n");
}

static void handle_package_measurement(struct pkg_buffer *p, uint8_t request, int len, uint8_t node_id)
{
    struct node *node = node_get(node_id);

    if(!node) {
        printf("Unknown node %d\n", node_id);
        pkg_write_byte(p, PKG_NACK);
        pkg_write_byte(p, PKG_FLAG_NOT_REGISTERED);
        return;
    }

    struct pkg_timestamp pkg_timestamp;
    pkg_read_timestamp(p, &pkg_timestamp);
    time_t timestamp = convert_pkg_timestamp_to_time(pkg_timestamp);

    if(pkg_timestamp.year > 0) {
        uint16_t humidity_raw = pkg_read_word(p);
        int16_t temperature_raw = pkg_read_word(p);
        uint16_t vcc_raw = pkg_read_word(p);
        uint16_t vmid_raw = pkg_read_word(p);

        double humidity = (100.0 * humidity_raw) / (1 << SHTC3_HUMIDITY_SHIFT);
        double temperature = ((double) temperature_raw) / (1 << SHTC3_TEMPERATURE_SHIFT);
        double vcc = ((double) vcc_raw) / (1 << ADC_VOLTAGE_SHIFT);
        double vmid = ((double) vmid_raw) / (1 << ADC_VOLTAGE_SHIFT);

        int row_id = db_add_measurement(node_id, timestamp, humidity, temperature, vcc, vmid);
        if(row_id >= 0) {
            float rssi = -rfm69_get_rssi() / 2.0;

            if(node && (node->protocol_version > 0)) {
                if(request == PKG_MEASUREMENT_REPEAT) {
                    send_ack(p, node, (time_t)(-1));
                } else {
                    send_ack(p, node, timestamp);
                }
            } else {
                pkg_write_byte(p, PKG_ACK);
                pkg_write_byte(p, 0);
            }

            if(row_id == 0) {
                printf("Measurement already added\n");
            } else {
                printf("New measurement #%d\n", row_id);
                printf("Node id:     %d\n", node_id);
                printf("Timestamp:   %s\n", format_time(&timestamp));
                printf("Temperature: %.2fC\n", temperature);
                printf("Humidity:    %.2f%%\n", humidity);
                printf("VCC:         %.2fV\n", vcc);
                printf("Vmid:        %.2fV\n", vmid);
                printf("RSSI:        %.2fdB\n", rssi);
            }
        } else {
            printf("Error %d when adding measurement", row_id);

            uint8_t flags = 0x00;

            if(row_id == DB_NOT_REGISTERED) {
                flags = PKG_FLAG_NOT_REGISTERED;
                printf(": Not registered");
            }

            printf("\n");

            pkg_write_byte(p, PKG_NACK);
            pkg_write_byte(p, flags);
        }
    } else {
        printf("Timestamp too old: %s\n", format_time(&timestamp));

        pkg_write_byte(p, PKG_NACK);
        pkg_write_byte(p, PKG_FLAG_NOT_REGISTERED);
    }
}


static void handle_package_debug(struct pkg_buffer *p, uint8_t request, int len, uint8_t node_id)
{
    struct pkg_timestamp pkg_timestamp;
    pkg_read_timestamp(p, &pkg_timestamp);
    time_t timestamp = convert_pkg_timestamp_to_time(pkg_timestamp);

    char msg[64];

    int msg_len = pkg_read_string(p, msg, sizeof(msg));

    if(pkg_timestamp.year > 0) {
        printf("Message from %d at %s: %s\n", node_id, format_time(&timestamp), msg);

        int row_id = db_add_debug_message(node_id, timestamp, msg, msg_len);
        if(row_id >= 0) {
            pkg_write_byte(p, PKG_ACK);
            pkg_write_byte(p, 0x00);
        } else {
            pkg_write_byte(p, PKG_NACK);
            pkg_write_byte(p, 0x00);
        }
    } else {
        printf("Timestamp too old: %s\n", format_time(&timestamp));
        printf("Message from %d: \"%s\"\r\n", node_id, msg);

        pkg_write_byte(p, PKG_NACK);
        pkg_write_byte(p, PKG_FLAG_NOT_REGISTERED);
    }
}

void handle_package(struct pkg_buffer *p, int len)
{
    uint8_t node_id = p->from;
    uint8_t request = pkg_read_byte(p);

    time_t receive_time = time(0);
    printf("\r\nReceived package from %d at %s\n", node_id, format_time(&receive_time));

    switch(request) {
    case PKG_REGISTER: // Register
        handle_package_register(p, request, len, node_id);
        break;

    case PKG_MEASUREMENT_REPEAT:
    case PKG_MEASUREMENT: // Measurement
        handle_package_measurement(p, request, len, node_id);
        break;

    case PKG_DEBUG:
        handle_package_debug(p, request, len, node_id);
        break;

    default:
        printf("Unknown package type %02X\n", request);
        break;
    }
}
