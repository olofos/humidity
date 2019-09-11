#ifndef SPI_H_
#define SPI_H_

void spi_init(void);
void spi_deinit(void);

uint8_t spi_read(void);
void spi_write(uint8_t out);

#endif
