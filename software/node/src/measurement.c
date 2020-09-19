#include <stdint.h>
#include <stdio.h>

#include "package-protocol.h"
#include "shtc3.h"
#include "adc.h"
#include "measurement.h"
#include "cbuf.h"
#include "pretty-print.h"

#define measurement_cbuf_LEN 128

struct
{
    uint8_t head;
    uint8_t tail;
    struct measurement buf[measurement_cbuf_LEN];
} measurement_cbuf;

int measurement_add(const struct measurement *m)
{
    if(cbuf_full(measurement_cbuf)) {
        // Overwrite oldest data
        cbuf_tail_next(measurement_cbuf);
    }
    cbuf_push(measurement_cbuf, *m);
    return 1;
}

struct measurement *measurement_get(void)
{
    if(cbuf_empty(measurement_cbuf)) {
        return 0;
    }

    return cbuf_tail(measurement_cbuf);
}

void measurement_handled(void)
{
    cbuf_tail_next(measurement_cbuf);
}

int measurement_empty(void)
{
    return cbuf_empty(measurement_cbuf);
}
