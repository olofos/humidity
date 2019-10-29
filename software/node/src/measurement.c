#include <stdint.h>
#include <stdio.h>

#include "package-protocol.h"
#include "shtc3.h"
#include "adc.h"
#include "measurement.h"

void measurement_save(void)
{
}

void measurement_restore(void)
{
}

static struct measurement saved_measurement;

int measurement_add(const struct measurement *m)
{
    saved_measurement = *m;

    return 1;
}

int measurement_get(struct measurement *m)
{
    *m = saved_measurement;

    return 1;
}
