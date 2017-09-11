/*
 * tft_spi_driver.c
 *
 *  Created on: 2 de dic. de 2016
 *      Author: Yarib Nevárez
 */
#include "xparameters.h"
#include "TFT_SPI_DISPLAY_240x320.h"
#include "tft_spi_driver.h"

void tft_spi_initialize(void)
{
	SET_TFT_SPI_BAUD_RATE_DIVIDER(0xFF);
	SET_TFT_SPI_SETTLE_TIME(3);

	SET_TFT_DATA_COMMAND(1);

	SET_TFT_SPI_CLOCK_POLARITY(1);
	SET_TFT_SPI_CLOCK_PHASE(1);

	SET_TFT_CS_FORCE(0);
	SET_TFT_SPI_DATA_LENGTH(0);
}

void tft_spi_baud_rate(uint8_t baud_rate)
{
	SET_TFT_SPI_BAUD_RATE_DIVIDER(baud_rate);
	SET_TFT_SPI_SETTLE_TIME(2);
}

void tft_hardware_initialize(void)
{
	int nop = 10000;
	SET_TFT_DATA_COMMAND(1);
	SET_TFT_RESET(0);
	while(nop--);
	SET_TFT_RESET(1);
}

void tft_spi_write_data(uint8_t data)
{
	while(!GET_TFT_TRANSMISSION_DONE);
	SET_TFT_SPI_DATA_LENGTH(0);

	TFT_SPI_DATA = data;
}

void tft_spi_write_data16(uint16_t word)
{
	while(!GET_TFT_TRANSMISSION_DONE);
	SET_TFT_SPI_DATA_LENGTH(1);

	TFT_SPI_DATA = word;
}

void tft_spi_write_command(uint8_t cmd)
{
	SET_TFT_DATA_COMMAND(0);
	tft_spi_write_data(cmd);
	SET_TFT_DATA_COMMAND(1);
}
