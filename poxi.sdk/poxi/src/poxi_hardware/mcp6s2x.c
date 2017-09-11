/*
 * mcp6s2x.c
 *
 *  Created on: 6 de dic. de 2016
 *      Author: Yarib Nevárez
 */

#include "mcp6s2x.h"

#include "POXI.h"

#define MCP6S2X_CMD_SHUTDOWN        0x2000
#define MCP6S2X_CMD_WRITE_REGISTER	0x4000

#define MCP6S2X_ADDRESS_CHANNEL     0x0100
#define MCP6S2X_ADDRESS_GAIN        0x0000

#define MCP6S2X_SPI_BAUD_RATE       0x10

static void MCP6S2X_shutdown(void);
static void MCP6S2X_select_channel(MCP6S2X_CHANNEL channel);
static void MCP6S2X_set_gain(MCP6S2X_GAIN gain);

static MCP6S2X MCP6S2X_obj = { MCP6S2X_shutdown,
                               MCP6S2X_select_channel,
                               MCP6S2X_set_gain};

MCP6S2X * MCP6S2X_instance(void)
{
	return & MCP6S2X_obj;
}


#define MCP6S2X_SPI_FRAME(command, address, data) ((command) | (address) | (0x7 & (unsigned int)(data)))

inline static void MCP6S2X_init_spi(void)
{
	while (!GET_POXI_SPI_TRANSMISSION_DONE);
	SET_POXI_SPI_SLAVE_SELECT(POXI_SPI_PGA_CS);
	SET_POXI_SPI_DATA_LENGTH(POXI_SPI_DATA_LENGTH_16_BITS);
	SET_POXI_SPI_BAUD_RATE_DIVIDER(MCP6S2X_SPI_BAUD_RATE);
	SET_POXI_SPI_CLOCK_POLARITY(1);
	SET_POXI_SPI_CLOCK_PHASE(1);
}

static void MCP6S2X_shutdown(void)
{
	MCP6S2X_init_spi();
	POXI_SPI_DATA = MCP6S2X_SPI_FRAME(MCP6S2X_CMD_SHUTDOWN, 0, 0);
}

static void MCP6S2X_select_channel(MCP6S2X_CHANNEL channel)
{
	MCP6S2X_init_spi();
	POXI_SPI_DATA = MCP6S2X_SPI_FRAME(MCP6S2X_CMD_WRITE_REGISTER, MCP6S2X_ADDRESS_CHANNEL, channel);
}

static void MCP6S2X_set_gain(MCP6S2X_GAIN gain)
{
	MCP6S2X_init_spi();
	POXI_SPI_DATA = MCP6S2X_SPI_FRAME(MCP6S2X_CMD_WRITE_REGISTER, MCP6S2X_ADDRESS_GAIN, gain);
}
