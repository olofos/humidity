#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

#include <linux/types.h>
#include <linux/spi/spidev.h>

#include <gpiod.h>

#include "rfm69.h"
#include "db.h"
#include "package.h"
#include "aes-key.h"

#define SHTC3_TEMPERATURE_SHIFT 8
#define ADC_VOLTAGE_SHIFT 12

#define LOCKNAME "/tmp/humidity-gateway.lock"

void sighandler(int);

static int done = 0;

#define GATEWAY_ADDRESS 1
#define NODE_ADDRESS 2

uint8_t from_bcd(uint8_t n)
{
    return 10 * (n >> 4) + (n & 0x0F);
}

uint8_t to_bcd(uint8_t n)
{
    const uint8_t tens = n / 10;
    const uint8_t units = n % 10;

    return (tens << 4) | units;
}

struct pkg_timestamp convert_time_to_pkg_timestamp(time_t t)
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

time_t convert_pkg_timestamp_to_time(struct pkg_timestamp timestamp)
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

static int take_lock(void)
{
    const char *lockname = LOCKNAME;
    int fd = open(lockname, O_RDONLY | O_CREAT);
    if(fd < 0) {
        perror("Could not open lock file");
        return -1;
    }
    if(flock(fd, LOCK_EX | LOCK_NB) < 0) {
        perror("Could not acquire lock");
        return -1;
    }
    return fd;
}

int main(void)
{
    signal(SIGINT, sighandler);

    if(take_lock() < 0) {
        return 1;
    }

    // Make sure we work in UTC
    setenv("TZ", "", 1);
    tzset();

    char *db_filename = "../db/humidity.db";

    if(getenv("DB")) {
        db_filename = getenv("DB");
    }

    printf("Opening database %s\n", db_filename);
    if(db_init(db_filename) != DB_OK) {
        fprintf(stderr, "Failed initializing database\n");
        return 1;
    }

    rfm69_init();
    rfm69_set_node_address(GATEWAY_ADDRESS);
    rfm69_set_aes_key(aes_key);

    uint8_t rfm69_version = rfm69_get_version();

    printf("RFM69 Version: %02X\r\n", rfm69_version);

    struct pkg_buffer pkg_buffer;

    while(!done) {
        struct pkg_buffer *p = &pkg_buffer;
        pkg_init(p);

        int len = pkg_read(p);

        if(done) break;

        if(len > 0) {
            printf("\r\n");
            uint8_t node = p->from;
            uint8_t request = pkg_read_byte(p);

            time_t receive_time = time(0);
            printf("Received package from %d at %s\n", node, format_time(&receive_time));

            switch(request) {
            case PKG_REGISTER: // Register
            {
                uint8_t node_type = pkg_read_byte(p);

                uint64_t hash1 = pkg_read_dword(p);
                uint32_t hash2 = pkg_read_dword(p);
                uint64_t hash = (hash1 << 32) | hash2;

                if(db_register_node(node, node_type, hash) == DB_OK) {
                    struct pkg_timestamp pkg_timestamp = convert_time_to_pkg_timestamp(time(0));

                    pkg_write_byte(p, PKG_SET_TIME);
                    pkg_write_timestamp(p, &pkg_timestamp);
                    pkg_write(node, p);

                    printf("New node\n");
                    printf("Node id:    %d\n", node);
                    printf("Type:       %d\n", node_type);
                    printf("Hash:       %016llX\n", hash);
                } else {
                    pkg_write_byte(p, PKG_NACK);
                    pkg_write_byte(p, 0x00);
                    pkg_write(node, p);

                    printf("Error when registering node\n");
                }
            }
            break;

            case PKG_MEASUREMENT: // Measurement
            {
                struct pkg_timestamp pkg_timestamp;
                pkg_read_timestamp(p, &pkg_timestamp);
                time_t timestamp = convert_pkg_timestamp_to_time(pkg_timestamp);

                if(pkg_timestamp.year > 0) {
                    uint16_t humidity_raw = pkg_read_word(p);
                    int16_t temperature_raw = pkg_read_word(p);
                    uint16_t vcc_raw = pkg_read_word(p);
                    uint16_t vmid_raw = pkg_read_word(p);

                    double humidity = (100.0 * humidity_raw) / (1 << 16);
                    double temperature = ((double) temperature_raw) / (1 << SHTC3_TEMPERATURE_SHIFT);
                    double vcc = ((double) vcc_raw) / (1 << ADC_VOLTAGE_SHIFT);
                    double vmid = ((double) vmid_raw) / (1 << ADC_VOLTAGE_SHIFT);

                    int ret = db_add_measurement(node, timestamp, humidity, temperature, vcc, vmid);
                    if((ret > 0) || (ret == DB_ALREADY_ADDED)) {
                        uint8_t flags = 0x00;

                        int uptodate = db_check_firmware_is_uptodate(node);

                        if(!uptodate) {
                            uint64_t latest_hash = db_get_latest_firmware_hash();

                            if(latest_hash) {
                                flags |= PKG_FLAG_UPDATE_AVAILABLE;
                            }
                        }

                        float rssi = -rfm69_get_rssi() / 2.0;

                        pkg_write_byte(p, PKG_ACK);
                        pkg_write_byte(p, flags);
                        pkg_write(node, p);

                        if(ret == DB_ALREADY_ADDED) {
                            printf("Measurement already added\n");
                        } else {
                            printf("New measurement #%d\n", ret);
                            printf("Node id:     %d\n", node);
                            printf("Timestamp:   %s\n", format_time(&timestamp));
                            printf("Temperature: %.2fC\n", temperature);
                            printf("Humidity:    %.2f%%\n", humidity);
                            printf("VCC:         %.2fV\n", vcc);
                            printf("Vmid:        %.2fV\n", vmid);
                            printf("RSSI:        %.2fdB\n", rssi);
                        }
                    } else {
                        printf("Error when adding measurement");

                        uint8_t flags = 0x00;

                        if(ret == DB_NOT_REGISTERED) {
                            flags = PKG_FLAG_NOT_REGISTERED;
                            printf(": Not registered");
                        }

                        printf("\n");

                        pkg_write_byte(p, PKG_NACK);
                        pkg_write_byte(p, flags);
                        pkg_write(node, p);
                    }
                } else {
                    printf("Timestamp too old: %s\n", format_time(&timestamp));

                    pkg_write_byte(p, PKG_NACK);
                    pkg_write_byte(p, PKG_FLAG_NOT_REGISTERED);
                    pkg_write(node, p);
                }
            }
            break;

            case PKG_DEBUG:
            {
                struct pkg_timestamp pkg_timestamp;
                pkg_read_timestamp(p, &pkg_timestamp);
                time_t timestamp = convert_pkg_timestamp_to_time(pkg_timestamp);

                char msg[64];

                int len = pkg_read_string(p, msg, sizeof(msg));

                if(pkg_timestamp.year > 0) {
                    printf("Message from %d at %s: %s\n", node, format_time(&timestamp), msg);

                    int ret = db_add_debug_message(node, timestamp, msg, len);
                    if(ret > 0) {
                        pkg_write_byte(p, PKG_ACK);
                        pkg_write_byte(p, 0x00);
                        pkg_write(node, p);
                    } else {
                        pkg_write_byte(p, PKG_NACK);
                        pkg_write_byte(p, 0x00);
                        pkg_write(node, p);
                    }
                } else {
                    printf("Timestamp too old: %s\n", format_time(&timestamp));
                    printf("Message from %d: \"%s\"\r\n", node, msg);

                    pkg_write_byte(p, PKG_NACK);
                    pkg_write_byte(p, PKG_FLAG_NOT_REGISTERED);
                    pkg_write(node, p);
                }
            }
            break;
            }
        } else {
            printf(".");
            fflush(stdout);
        }
    }

    printf("Quitting\n");

    rfm69_deinit();
    db_deinit();


    return 0;
}

void sighandler(int s)
{
    printf("Caught signal: %d\n", s);
    done = 1;
}
