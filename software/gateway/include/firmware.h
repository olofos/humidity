#ifndef FIRMWARE_H_
#define FIRMWARE_H_

#define FW_SIZE 32768
#define FW_PAGE_SIZE 64
#define FW_HALFPAGE_SIZE ((FW_PAGE_SIZE) / 2)

enum {
    FW_ERROR = -1,
    FW_DATA = 1,
    FW_EMPTY = 2,
    FW_UNCHANGED = 3,
};

struct firmware_halfpage {
    union {
        uint8_t buf[FW_HALFPAGE_SIZE];
        uint16_t count;
    };
    uint32_t crc;
    uint16_t address;
    int8_t result;
};

int firmware_set_dir(char *dirname);
int firmware_set_dir_from_file(char *filename);
void firmware_deinit(void);
int firmware_file_exists(uint64_t hash);
int firmware_get_halfpage(uint64_t old_hash, uint64_t new_hash, struct firmware_halfpage *halfpage);

#endif
