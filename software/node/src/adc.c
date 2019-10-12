#include <stdint.h>

#include "stm32l0xx.h"
#include "adc.h"
#include "systick.h"

#define ADC_TIMEOUT 100

#define VREF_CAL (*((uint16_t*) ((uint32_t ) 0x1FF80078)))
#define ADC_FULL_SCALE ((1<<12) - 1)

static void adc_cal(void)
{
    if(ADC1->CR & ADC_CR_ADEN) {
        return;
    }

    ADC1->CR = ADC_CR_ADCAL;

    while(ADC1->CR & ADC_CR_ADCAL)
        ;
}

void adc_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
    ADC1_COMMON->CCR |= ADC_CCR_LFMEN | ADC_CCR_VREFEN;
    ADC1->CFGR1 = ADC_CFGR1_SCANDIR;
    ADC1->CFGR2 = (1UL << ADC_CFGR2_CKMODE_Pos);

    if(!(ADC1->ISR & ADC_ISR_EOCAL)) {
        adc_cal();
    }

    ADC1->CR = ADC_CR_ADEN;

    while(!(ADC1->ISR & ADC_ISR_ADRDY)) {
    }

}

void adc_deinit(void)
{
    if(ADC1->CR & ADC_CR_ADSTART) {
        ADC1->CR = ADC_CR_ADSTP;

        while(ADC1->CR & ADC_CR_ADSTP)
            ;
    }

    ADC1->CR = ADC_CR_ADDIS;

    while(ADC1->CR & ADC_CR_ADEN)
        ;

    ADC1->ISR = ADC_ISR_ADRDY;
    ADC1_COMMON->CCR &= ~(ADC_CCR_LFMEN | ADC_CCR_VREFEN);
    RCC->APB2ENR &= ~RCC_APB2ENR_ADCEN;
}

int adc_measure_voltages(struct adc_supply_voltages *voltages)
{
    ADC1->CHSELR = ADC_CHSELR_CHSEL17 | ADC_CHSELR_CHSEL9;

    ADC1->CR = ADC_CR_ADSTART;

    while(!(ADC1->ISR & ADC_ISR_EOC))
        ;

    uint16_t m_vcc = ADC1->DR;

    uint16_t vcc = (3 * (1 << ADC_VOLTAGE_SHIFT) * VREF_CAL) / m_vcc;

    uint32_t start = systick;

    while(!(ADC1->ISR & ADC_ISR_EOC)) {
        if(systick - start >= ADC_TIMEOUT) return 0;
    }

    const uint32_t m_mid = ADC1->DR;

    const uint16_t vmid = (vcc * m_mid) / ADC_FULL_SCALE;

    voltages->vcc = vcc;
    voltages->vmid = vmid;

    return 1;
}
