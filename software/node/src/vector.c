#include <stdint.h>
#include "vector.h"

extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss, _estack;

#ifdef HAVE_INITFINI_ARRAY

/* These magic symbols are provided by the linker.  */
extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end []) (void) __attribute__((weak));
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));

#endif

void __attribute__((naked)) Reset_Handler(void)
{
    uint32_t *src, *dst;

    for(src = &_sidata, dst = &_sdata; dst < &_edata; src++, dst++) {
        *dst = *src;
    }

    for(dst = &_sbss; dst < &_ebss; dst++) {
        *dst = 0;
    }

#ifdef HAVE_INITFINI_ARRAY
    size_t count;
    size_t i;

    count = __preinit_array_end - __preinit_array_start;
    for (i = 0; i < count; i++) {
        __preinit_array_start[i] ();
    }

    count = __init_array_end - __init_array_start;
    for (i = 0; i < count; i++) {
        __init_array_start[i] ();
    }
#endif

    main();

    for(;;) {
    }
}

void __attribute__((naked)) Default_Handler(void)
{
    for(;;) {
    }
}

typedef void (*vector_table_entry_t)(void);

typedef struct {
    uint32_t *initial_sp_value;
    vector_table_entry_t reset; // 004
    vector_table_entry_t nmi;   // 008
    vector_table_entry_t hard_fault; // 00c

    vector_table_entry_t reserved_x0010; // 010
    vector_table_entry_t reserved_x0014; // 014
    vector_table_entry_t reserved_x0018; // 018
    vector_table_entry_t reserved_x001C; // 01c
    vector_table_entry_t reserved_x0020; // 020
    vector_table_entry_t reserved_x0024; // 024
    vector_table_entry_t reserved_x0028; // 028

    vector_table_entry_t sv_call; // 02c
    vector_table_entry_t reserved_x0030; // 030
    vector_table_entry_t reserved_x0034; // 034
    vector_table_entry_t pend_sv; // 038
    vector_table_entry_t systick; // 03c

    vector_table_entry_t wwdg; // 040
    vector_table_entry_t pvd; // 044
    vector_table_entry_t rtc; // 048
    vector_table_entry_t flash; // 04c
    vector_table_entry_t rcc; // 050
    vector_table_entry_t exti0_1; // 054
    vector_table_entry_t exti2_3; // 058
    vector_table_entry_t exti4_15; // 05c
    vector_table_entry_t reserved_x0060; // 060
    vector_table_entry_t dma1_channel1; // 064
    vector_table_entry_t dma1_channel2_3; // 068
    vector_table_entry_t dma1_channel4_5_6_7; // 06c
    vector_table_entry_t adc1_comp; // 070
    vector_table_entry_t lptim1; // 074
    vector_table_entry_t reserved_x0078; // 078
    vector_table_entry_t tim2; // 07c

    vector_table_entry_t reserved_x0080; // 080
    vector_table_entry_t reserved_x0084; // 084
    vector_table_entry_t reserved_x0088; // 088
    vector_table_entry_t reserved_x008C; // 08c

    vector_table_entry_t tim21; // 090
    vector_table_entry_t reserved_x0094; // 094
    vector_table_entry_t tim22; // 098
    vector_table_entry_t i2c1; // 09c
    vector_table_entry_t reserved_x00A0; // 0a0
    vector_table_entry_t spi1; // 0a4
    vector_table_entry_t reserved_x00A8; // 0a8
    vector_table_entry_t reserved_x00AC; // 0ac
    vector_table_entry_t usart2; // 0b0
    vector_table_entry_t lpuart1; // 0b4
    vector_table_entry_t reserved_x00B8; // 0b8
    vector_table_entry_t reserved_x00BC; // 0bc
} vector_table_t;

#define weak_alias(name, aliasname) _weak_alias (name, aliasname)
#define _weak_alias(name, aliasname) extern __typeof (name) aliasname __attribute__ ((weak, alias (#name)));

weak_alias(Default_Handler, NMI_Handler);
weak_alias(Default_Handler, HardFault_Handler);
weak_alias(Default_Handler, SVC_Handler);
weak_alias(Default_Handler, PendSV_Handler);
weak_alias(Default_Handler, SysTick_Handler);

weak_alias(Default_Handler, WWDG_IRQHandler);
weak_alias(Default_Handler, PVD_IRQHandler);
weak_alias(Default_Handler, RTC_IRQHandler);
weak_alias(Default_Handler, FLASH_IRQHandler);
weak_alias(Default_Handler, RCC_IRQHandler);
weak_alias(Default_Handler, EXTI0_1_IRQHandler);
weak_alias(Default_Handler, EXTI2_3_IRQHandler);
weak_alias(Default_Handler, EXTI4_15_IRQHandler);
weak_alias(Default_Handler, DMA1_Channel1_IRQHandler);
weak_alias(Default_Handler, DMA1_Channel2_3_IRQHandler);
weak_alias(Default_Handler, DMA1_Channel4_5_6_7_IRQHandler);
weak_alias(Default_Handler, ADC1_COMP_IRQHandler);
weak_alias(Default_Handler, LPTIM1_IRQHandler);
weak_alias(Default_Handler, TIM2_IRQHandler);
weak_alias(Default_Handler, TIM21_IRQHandler);
weak_alias(Default_Handler, TIM22_IRQHandler);
weak_alias(Default_Handler, I2C1_IRQHandler);
weak_alias(Default_Handler, SPI1_IRQHandler);
weak_alias(Default_Handler, USART2_IRQHandler);
weak_alias(Default_Handler, LPUART1_IRQHandler);

vector_table_t vector_table __attribute__ ((section(".isr_vector"))) = {
    .initial_sp_value = &_estack,
    .reset = Reset_Handler,
    .nmi = NMI_Handler,
    .hard_fault = HardFault_Handler,
    .sv_call = SVC_Handler,
    .pend_sv = PendSV_Handler,
    .systick = SysTick_Handler,

    .wwdg = WWDG_IRQHandler,
    .pvd = PVD_IRQHandler,
    .rtc = RTC_IRQHandler,
    .flash = FLASH_IRQHandler,
    .rcc = RCC_IRQHandler,

    .exti0_1 = EXTI0_1_IRQHandler,
    .exti2_3 = EXTI2_3_IRQHandler,
    .exti4_15 = EXTI4_15_IRQHandler,
    .dma1_channel1 = DMA1_Channel1_IRQHandler,
    .dma1_channel2_3 = DMA1_Channel2_3_IRQHandler,
    .dma1_channel4_5_6_7 = DMA1_Channel4_5_6_7_IRQHandler,
    .adc1_comp = ADC1_COMP_IRQHandler,
    .lptim1 = LPTIM1_IRQHandler,
    .tim2 = TIM2_IRQHandler,
    .tim21 = TIM21_IRQHandler,
    .tim22 = TIM22_IRQHandler,
    .i2c1 = I2C1_IRQHandler,
    .spi1 = SPI1_IRQHandler,
    .usart2 = USART2_IRQHandler,
    .lpuart1 = LPUART1_IRQHandler,

    .reserved_x0010 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0014 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0018 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x001C = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0020 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0024 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0028 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0030 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0034 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0060 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0078 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0080 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0084 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0088 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x008C = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x0094 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x00A0 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x00A8 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x00AC = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x00B8 = (vector_table_entry_t) 0xFFFFFFFF,
    .reserved_x00BC = (vector_table_entry_t) 0xFFFFFFFF,

};
