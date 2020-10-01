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

struct timer_state {
    uint16_t take_measurement;
    uint16_t send_measurement;
    uint16_t send_debug;
    uint16_t send_update;
};

struct sleep_state {
    uint16_t period;
    uint8_t mode;
};

struct state {
    struct update_state update;
    struct timer_state timer;
    struct sleep_state sleep;
    uint8_t flags;
};

extern struct state state;

void state_init(void);
void state_load(void);
void state_save(void);

#endif
