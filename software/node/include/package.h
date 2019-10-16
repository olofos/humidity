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
    PKG_REGISTER       = 0x80,
    PKG_MEASUREMENT    = 0x81,
    PKG_DEBUG          = 0x82,
    PKG_UPDATE_REQUEST = 0x83,

    // Responses
    PKG_NACK           = 0x00,
    PKG_ACK            = 0x01,
    PKG_SET_TIME       = 0x02,
    PKG_UPDATE_DATA    = 0x03,
};

enum pkg_node_type {
    PKG_NODE_TYPE_HUMIDITY = 0x01,
};

enum pkg_flags {
    PKG_FLAG_UPDATE_AVAILABLE = 0x01,
};

struct pkg_buffer {
    uint8_t len;
    uint8_t write_counter;
    uint8_t read_counter;
    uint8_t from;
    uint8_t buf[49];
};

static inline void pkg_init(struct pkg_buffer *buf)
{
    buf->write_counter = 0;
    buf->read_counter = 2;
}

static inline void pkg_write_byte(struct pkg_buffer *buf, uint8_t val)
{
    buf->buf[buf->write_counter++] = val;
}

static inline void pkg_write_word(struct pkg_buffer *buf, uint16_t val)
{
    buf->buf[buf->write_counter++] = val & 0x00FF;
    buf->buf[buf->write_counter++] = (val >> 8) & 0x00FF;
}

static inline void pkg_write_dword(struct pkg_buffer *buf, uint32_t val)
{
    buf->buf[buf->write_counter++] = val & 0x000000FF;
    buf->buf[buf->write_counter++] = (val >> 8) & 0x000000FF;
    buf->buf[buf->write_counter++] = (val >> 16) & 0x000000FF;
    buf->buf[buf->write_counter++] = (val >> 24) & 0x000000FF;
}

static inline void pkg_write_timestamp(struct pkg_buffer *buf, const struct pkg_timestamp *t)
{
    buf->buf[buf->write_counter++] = t->day;
    buf->buf[buf->write_counter++] = t->month;
    buf->buf[buf->write_counter++] = t->year;
    buf->buf[buf->write_counter++] = t->second;
    buf->buf[buf->write_counter++] = t->minute;
    buf->buf[buf->write_counter++] = t->hour;
}

static inline int pkg_write(uint8_t node, const struct pkg_buffer *buf)
{
    return rfm69_write(node, buf->buf, buf->write_counter);
}

static inline int pkg_read(struct pkg_buffer *buf)
{
    buf->len = rfm69_read(buf->buf, sizeof(buf->buf));

    if(buf->len >= 2) {
        buf->from = buf->buf[1];
        return buf->len - 2;
    }

    return buf->len;
}

static inline uint8_t pkg_read_byte(struct pkg_buffer *buf)
{
    return buf->buf[buf->read_counter++];
}

static inline uint16_t pkg_read_word(struct pkg_buffer *buf)
{
    const uint8_t b0 = buf->buf[buf->read_counter++];
    const uint8_t b1 = buf->buf[buf->read_counter++];

    return (b1 << 8) | b0;
}

static inline uint32_t pkg_read_dword(struct pkg_buffer *buf)
{
    const uint32_t b0 = buf->buf[buf->read_counter++];
    const uint32_t b1 = buf->buf[buf->read_counter++];
    const uint32_t b2 = buf->buf[buf->read_counter++];
    const uint32_t b3 = buf->buf[buf->read_counter++];

    return ((uint32_t) b3 << 24) | ((uint32_t) b2 << 16) | ((uint32_t) b1 << 8) | (uint32_t) b0;
}

static inline void pkg_read_timestamp(struct pkg_buffer *buf, struct pkg_timestamp *t)
{
    t->day = buf->buf[buf->read_counter++];
    t->month = buf->buf[buf->read_counter++];
    t->year = buf->buf[buf->read_counter++];
    t->second = buf->buf[buf->read_counter++];
    t->minute = buf->buf[buf->read_counter++];
    t->hour = buf->buf[buf->read_counter++];
}

#endif
