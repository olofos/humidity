#ifndef SHTC3_REGISTERS_H_
#define SHTC3_REGISTERS_H_

#define SHTC3_I2C_ADDRESS 0x70

#define SHTC3_COMMAND_SLEEP  0xB098
#define SHTC3_COMMAND_WAKEUP 0x3517
#define SHTC3_COMMAND_READ   0x6458
#define SHTC3_COMMAND_RESET  0x805D
#define SHTC3_COMMAND_ID     0xEFC8

#define SHTC3_ID_MASK 0x083F
#define SHTC3_ID      0x0807

#define SHTC3_TIMEOUT 100

#endif
