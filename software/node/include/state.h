#ifndef STATE_H_
#define STATE_H_

struct update_state {
    uint64_t hash;
    uint16_t address;
};

struct state {
    struct update_state update;
    uint16_t time_until_next_measurement;
    uint8_t flags;
};

#endif
