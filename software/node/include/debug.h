#ifndef DEBUG_H_
#define DEBUG_H_

#define DEBUG_LEN 40

struct debug_message {
    struct pkg_timestamp timestamp;
    uint8_t retries;
    uint8_t len;
    char buf[DEBUG_LEN];
};

void debug_print(const char *str);
void debug_printf(const char *fmt, ...);
struct debug_message *debug_get(void);

void debug_handled(void);
int debug_empty(void);

#define debug_cbuf_LEN 16

struct debug_cbuf {
    uint8_t head;
    uint8_t tail;
    struct debug_message buf[debug_cbuf_LEN];
};

extern struct debug_cbuf debug_cbuf;

#endif
