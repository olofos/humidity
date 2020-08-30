#include <stdint.h>
#include <stdio.h>

#include "stm32l0xx.h"

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
        (void) cbuf_pop(measurement_cbuf);
    }

    cbuf_push(measurement_cbuf, *m);
    return 1;
}

int measurement_get(struct measurement *m)
{
    *m = cbuf_peek(measurement_cbuf);
    return 1;
}

void measurement_handled(void)
{
    (void) cbuf_pop(measurement_cbuf);
}

int measurement_empty(void)
{
    return cbuf_empty(measurement_cbuf);
}
