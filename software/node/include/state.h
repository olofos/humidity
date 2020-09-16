#ifndef STATE_H_
#define STATE_H_

enum state_flags {
    STATE_FLAG_NONE = 0x00,
    STATE_FLAG_UPDATE_AVAILABLE = 0x01,
    STATE_FLAG_REGISTERED = 0x02,
};


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
