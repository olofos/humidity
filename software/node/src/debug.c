#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "package-protocol.h"
#include "debug.h"
#include "cbuf.h"
#include "rtc.h"

struct debug_cbuf debug_cbuf;

static void debug_nprint(const char *str, int len)
{
    struct pkg_timestamp timestamp;
    rtc_get_time(&timestamp);

    while(len > 0) {
        if(cbuf_full(debug_cbuf)) {
            // Overwrite oldest message
            cbuf_tail_next(debug_cbuf);
        }

        int n = (len < DEBUG_LEN) ? len : DEBUG_LEN;

        struct debug_message *msg = cbuf_head(debug_cbuf);

        msg->timestamp = timestamp;
        msg->len = n;
        msg->retries = 0;
        memcpy(msg->buf, str, n);

        cbuf_head_next(debug_cbuf);

        len -= n;
        str += n;
    }
}

void debug_print(const char *msg)
{
    debug_nprint(msg, strlen(msg));
}

void debug_printf(const char *fmt, ...)
{
    char buf[2*DEBUG_LEN];

    va_list va;
    va_start(va, fmt);
    int len = vsnprintf(buf, sizeof(buf), fmt, va);
    va_end(va);

    debug_nprint(buf, len);
}

struct debug_message *debug_get(void)
{
    if(cbuf_empty(debug_cbuf)) {
        return 0;
    }

    return cbuf_tail(debug_cbuf);
}

void debug_handled(void)
{
    cbuf_tail_next(debug_cbuf);
}

int debug_empty(void)
{
    return cbuf_empty(debug_cbuf);
}
