#ifndef PACKAGE_PROTOCOL_H_
#define PACKAGE_PROTOCOL_H_

struct pkg_timestamp {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

struct pkg_measurement
{
    struct pkg_timestamp timestamp;
    uint16_t humidity;
    uint16_t temperature;
    uint16_t vcc;
    uint16_t vmid;
};

enum pkg_package_type {
    // Requests
    PKG_REGISTER           = 0x80,
    PKG_MEASUREMENT        = 0x81,
    PKG_DEBUG              = 0x82,
    PKG_UPDATE_REQUEST     = 0x83,
    PKG_MEASUREMENT_REPEAT = 0x85, // Only v1

    // Responses
    PKG_NACK             = 0x00,
    PKG_ACK              = 0x01,
    PKG_UPDATE_DATA      = 0x03,
    PKG_UPDATE_NO_CHANGE = 0x04,
    PKG_UPDATE_EMPTY     = 0x05,

    PKG_SET_TIME       = 0x02, // Only v0
};

enum pkg_node_type {
    PKG_NODE_TYPE_HUMIDITY = 0x01,
};

enum pkg_flags {
    // ACK
    PKG_FLAG_UPDATE_AVAILABLE = 0x01,
    PKG_FLAG_SET_TIME = 0x04,

    // NACK
    PKG_FLAG_NOT_REGISTERED = 0x02,
    PKG_FLAG_NO_RETRY = 0x08,
};

struct pkg_buffer {
    uint8_t len;
    uint8_t write_counter;
    uint8_t read_counter;
    uint8_t from;
    uint8_t buf[49];
};

#define PROTOCOL_VERSION_MAX 1

#endif
