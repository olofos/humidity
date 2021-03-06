#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "rfm69.h"
#include "rtc.h"
#include "adc.h"
#include "shtc3.h"
#include "package.h"
#include "measurement.h"
#include "pretty-print.h"
#include "state.h"
#include "package-handler.h"
#include "debug.h"

void construct_registration_package(struct pkg_buffer *p, uint8_t node_type, uint64_t hash)
{
    pkg_write_byte(p, PKG_REGISTER);
    pkg_write_byte(p, node_type);
    pkg_write_dword(p, (hash >> 32) & 0xFFFFFFFF);
    pkg_write_dword(p, hash & 0xFFFFFFFF);
    pkg_write_byte(p, PKG_VERSION);
}

void construct_measurement_package(struct pkg_buffer *p, const struct measurement *measurement)
{
    pkg_write_byte(p, (measurement->retries == 0) ? PKG_MEASUREMENT : PKG_MEASUREMENT_REPEAT);
    pkg_write_timestamp(p, &measurement->timestamp);
    pkg_write_word(p, measurement->humidity_temperature.humidity);
    pkg_write_word(p, measurement->humidity_temperature.temperature);
    pkg_write_word(p, measurement->voltages.vcc);
    pkg_write_word(p, measurement->voltages.vmid);
}

void construct_debug_package(struct pkg_buffer *p, const struct debug_message *msg)
{
    pkg_write_byte(p, PKG_DEBUG);
    pkg_write_timestamp(p, &msg->timestamp);

    for(int n = 0; n < msg->len; n++) {
        pkg_write_byte(p, msg->buf[n]);
    }
}

void construct_update_request_package(struct pkg_buffer *p, uint64_t old_hash, uint64_t new_hash, uint16_t address)
{
    pkg_write_byte(p, PKG_UPDATE_REQUEST);
    pkg_write_word(p, address);
    pkg_write_dword(p, (old_hash >> 32) & 0xFFFFFFFF);
    pkg_write_dword(p, old_hash & 0xFFFFFFFF);
    pkg_write_dword(p, (new_hash >> 32) & 0xFFFFFFFF);
    pkg_write_dword(p, new_hash & 0xFFFFFFFF);
}

int handle_ack_or_nack(struct pkg_buffer *p)
{
    uint8_t response = pkg_read_byte(p);

    if(response == PKG_ACK) {
        state.flags |= STATE_FLAG_REGISTERED;

        uint8_t flags = pkg_read_byte(p);

        if(flags & PKG_FLAG_UPDATE_AVAILABLE) {
            uint64_t hash_hi = pkg_read_dword(p);
            uint32_t hash_lo = pkg_read_dword(p);
            uint64_t hash = (hash_hi << 32) | hash_lo;
            if(!(state.flags & STATE_FLAG_UPDATE_AVAILABLE)
               || ((state.update.address == 0) && (state.update.hash != hash))) {
                printf("New version available: %016" PRIX64 "\r\n", hash);
                state.flags |= STATE_FLAG_UPDATE_AVAILABLE;
                state.update.hash = hash;
                state.update.address = 0;
            } else {
                printf("Update already in progress\r\n");
            }
        }

        if(flags & PKG_FLAG_SET_TIME) {
            struct pkg_timestamp pkg_timestamp;
            pkg_read_timestamp(p, &pkg_timestamp);
            rtc_set_time(&pkg_timestamp);
            printf("New time: ");
            print_timestamp(&pkg_timestamp);
        }

        return PKG_OK;
    } else if(response == PKG_NACK) {
        uint8_t flags = pkg_read_byte(p);
        if(flags & PKG_FLAG_NOT_REGISTERED) {
            state.flags &= ~STATE_FLAG_REGISTERED;
        }
        if(flags & PKG_FLAG_NO_RETRY) {
            return PKG_ERROR_NO_RETRY;
        }
    } else {
        printf("Received %02X. Expected ACK or NACK.\r\n", response);
    }
    return PKG_ERROR;
}
