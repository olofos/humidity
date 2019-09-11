#ifndef SPI_FLASH_H_
#define SPI_FLASH_H_

void spi_flash_erase_page(uint32_t address);
void spi_flash_write_page(uint32_t address, uint8_t *buf, uint16_t length);
void spi_flash_read(uint32_t address, uint8_t *buf, uint32_t length);
uint32_t spi_flash_read_id(void);

#endif
