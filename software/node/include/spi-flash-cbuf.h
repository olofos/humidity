#ifndef SPI_FLASH_CBUF_H_
#define SPI_FLASH_CBUF_H_

#define SPI_FLASH_CBUF_BUF_SIZE 32768
#define SPI_FLASH_CBUF_RECORD_SIZE 64
#define SPI_FLASH_CBUF_CAPACITY (SPI_FLASH_CBUF_BUF_SIZE / SPI_FLASH_CBUF_RECORD_SIZE)

int sf_cbuf_init(void);
int sf_cbuf_deinit(void);

uint16_t sf_cbuf_len(void);
int sf_cbuf_empty(void);
int sf_cbuf_full(void);

int sf_cbuf_push(uint8_t *data, uint8_t len);
int sf_cbuf_pop(uint8_t *data, uint8_t len);

#endif
