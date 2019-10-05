#ifndef GPIO_H_
#define GPIO_H_

#define GPIO_MODER_INPUT  0x0UL
#define GPIO_MODER_OUTPUT 0x1UL
#define GPIO_MODER_AF     0x2UL
#define GPIO_MODER_ANALOG 0x3UL
#define GPIO_MODER_MASK   0x3UL

#define GPIO_OTYPER_PP 0x0UL
#define GPIO_OTYPER_OD 0x1UL

// VDD = 1.65 - 2.7 V
// Low:       100 kHz
// Mid:       600 kHz
// High:        2 MHz
// Very High:  10 MHz

#define GPIO_OSPEEDR_LOW 0x0UL
#define GPIO_OSPEEDR_MID 0x1UL
#define GPIO_OSPEEDR_HI  0x2UL
#define GPIO_OSPEEDR_VHI 0x3UL

#define GPIO_PUPDR_NONE 0x00
#define GPIO_PUPDR_PU   0x01
#define GPIO_PUPDR_PD   0x02

#define EXPAND_MASK(MASK) (                     \
        (((MASK) & 0x0001) ? 0x00000003 : 0) |  \
        (((MASK) & 0x0002) ? 0x0000000C : 0) |  \
        (((MASK) & 0x0004) ? 0x00000030 : 0) |  \
        (((MASK) & 0x0008) ? 0x000000C0 : 0) |  \
        (((MASK) & 0x0010) ? 0x00000300 : 0) |  \
        (((MASK) & 0x0020) ? 0x00000C00 : 0) |  \
        (((MASK) & 0x0040) ? 0x00003000 : 0) |  \
        (((MASK) & 0x0080) ? 0x0000C000 : 0) |  \
        (((MASK) & 0x0100) ? 0x00030000 : 0) |  \
        (((MASK) & 0x0200) ? 0x000C0000 : 0) |  \
        (((MASK) & 0x0400) ? 0x00300000 : 0) |  \
        (((MASK) & 0x0800) ? 0x00C00000 : 0) |  \
        (((MASK) & 0x1000) ? 0x03000000 : 0) |  \
        (((MASK) & 0x2000) ? 0x0C000000 : 0) |  \
        (((MASK) & 0x4000) ? 0x30000000 : 0) |  \
        (((MASK) & 0x8000) ? 0xC0000000 : 0) )

#endif
