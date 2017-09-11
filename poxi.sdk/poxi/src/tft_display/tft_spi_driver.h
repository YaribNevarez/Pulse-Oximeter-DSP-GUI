/*
 * tft_spi_driver.h
 *
 *  Created on: 2 de dic. de 2016
 *      Author: Yarib Nevárez
 */

#ifndef SRC_TFT_DISPLAY_TFT_SPI_DRIVER_H_
#define SRC_TFT_DISPLAY_TFT_SPI_DRIVER_H_
#include "xil_types.h"

void tft_spi_initialize(void);

void tft_spi_baud_rate(uint8_t speed);

void tft_hardware_initialize(void);

void tft_spi_write_data(uint8_t data);

void tft_spi_write_data16(uint16_t word);

void tft_spi_write_command(uint8_t cmd);


#endif /* SRC_TFT_DISPLAY_TFT_SPI_DRIVER_H_ */
