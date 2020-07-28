#include <stdio.h>
#include <string.h>

#include "stm32l0xx.h"
#include "vector.h"
#include "cbuf.h"
#include "uart.h"

#define LSE_FREQ 32768
#define BAUD 9600

// LEN should be power of 2 and less than 256

#define tx_cbuf_LEN 64

struct tx_cbuf {
    volatile uint8_t head;
    volatile uint8_t tail;
    volatile uint8_t next_tail;
    uint8_t buf[tx_cbuf_LEN];
} tx_cbuf;

void uart_init(void)
{
    if(!(LPUART1->CR1 & USART_CR1_UE)) {
        RCC->APB1ENR |= RCC_APB1ENR_LPUART1EN;

        LPUART1->BRR = 256 * (uint32_t) LSE_FREQ / BAUD;
        LPUART1->CR1 = USART_CR1_TE | USART_CR1_UE;

        // DMA channel 7 remapped to LPUART1_TX
        DMA1_CSELR->CSELR = (0x05 << DMA_CSELR_C7S_Pos);
        DMA1_Channel7->CPAR = (uint32_t) &LPUART1->TDR;

        cbuf_init(tx_cbuf);
    }
}

void uart_init_dma(void)
{
    if(!(LPUART1->CR1 & USART_CR1_UE)) {
        LPUART1->CR3 |= USART_CR3_DMAT;
        NVIC_EnableIRQ(DMA1_Channel4_5_6_7_IRQn);

        uart_init();
    }
}


void uart_deinit(void)
{
    while(!(LPUART1->ISR & USART_ISR_TC)) {
    }

    LPUART1->CR1 = 0;
    NVIC_DisableIRQ(DMA1_Channel4_5_6_7_IRQn);
    RCC->APB1ENR &= ~RCC_APB1ENR_LPUART1EN;
}


static void uart_dma_tx_start(void)
{
    uint32_t len = cbuf_linear_len(tx_cbuf);

    if(len > 0) {
        // Use tx_cbuf.tail and not cbuf_tail(tx_cbuf) so we count mod sizeof(tail) and not mod LEN
        tx_cbuf.next_tail = tx_cbuf.tail + len;

        DMA1_Channel7->CMAR = (uint32_t) cbuf_tail(tx_cbuf);
        DMA1_Channel7->CNDTR = len;
        DMA1_Channel7->CCR = DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE | DMA_CCR_EN;
    }
}

ssize_t _write_r(struct _reent *reent, int fd, const void *buf, size_t count)
{
    (void) reent;

    if(fd == 1) {
        const char *s = buf;

        if(LPUART1->CR3 & USART_CR3_DMAT) {
            size_t num_left = count;

            while(num_left > 0) {
                size_t cap = cbuf_capacity(tx_cbuf);
                size_t num_to_write = num_left < cap ? num_left : cap;

                while(num_to_write) {
                    cbuf_push(tx_cbuf, *s++);
                    num_to_write--;
                    num_left--;
                }

                if(!(DMA1_Channel7->CCR & DMA_CCR_EN)) {
                    uart_dma_tx_start();
                }
            }
        } else {
            for(size_t i = 0; i < count; i++) {
                while(!(LPUART1->ISR & USART_ISR_TXE)) {
                }

                LPUART1->TDR = s[i];
            }
        }

        return count;
    } else {
        return -1;
    }
}

void DMA1_Channel4_5_6_7_IRQHandler(void)
{
    if(DMA1->ISR & DMA_ISR_TCIF7) {
        DMA1_Channel7->CCR = 0;

        tx_cbuf.tail = tx_cbuf.next_tail;

        if(!cbuf_empty(tx_cbuf)) {
            uart_dma_tx_start();
        }

        DMA1->IFCR = DMA_IFCR_CTCIF7 | DMA_IFCR_CHTIF7 | DMA_IFCR_CGIF7;
    }
}
