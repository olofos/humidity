#include <stdint.h>

#include "state.h"
#include "update.h"

int update_available(void)
{
    return state.flags & STATE_FLAG_UPDATE_AVAILABLE;
}
