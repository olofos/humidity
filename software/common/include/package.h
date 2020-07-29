#ifndef PACKAGE_H_
#define PACKAGE_H_

#include "package-protocol.h"

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

static inline int pkg_read_string(struct pkg_buffer *buf, char *s, int len)
{
    int i;
    for(i = 0; ((i < len - 1) && (buf->read_counter < buf->len)); i++) {
        s[i] = buf->buf[buf->read_counter++];
    }
    s[i] = 0;

    return i;
}

#endif
