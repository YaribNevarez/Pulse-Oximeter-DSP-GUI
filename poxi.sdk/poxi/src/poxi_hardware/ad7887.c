/*
 * ad7887.c
 *
 *  Created on: 6 de dic. de 2016
 *      Author: Yarib Nevárez
 */
#include "ad7887.h"

#include "poxi.h"

#define AD7887_REFERENCE_MASK		0x2000
#define AD7887_CHANNEL_MODE_MASK	0x1000
#define AD7887_CHANNEL_MASK			0x0800
#define AD7887_POWER_MODE_MASK		0x0300

#define AD7887_SPI_BAUD_RATE    	0x80

	// SPI FRAME
	// DONTC | ZERO | REF | SIN/DUAL | CH | ZERO | PM1 | PM0 |
	//   0   |  0   |  1  |     0    |  0 |  0   |  0  |  1  |

static uint16_t ad7887_context = REF_DISABLED | SINGLE_CHANNEL | AIN0 | MODE2;

static void AD7887_set_reference(AD7887_REFERENCE reference);
static void AD7887_set_channel_mode(AD7887_CHANNEL_MODE channel_mode);
static void AD7887_set_channel(AD7887_CHANNEL channel);
static void AD7887_set_power_mode(AD7887_POWER_MODE power_mode);
static uint16_t AD7887_read_analog(void);

static AD7887 AD7887_obj = { AD7887_set_reference,
                             AD7887_set_channel_mode,
                             AD7887_set_channel,
                             AD7887_set_power_mode,
                             AD7887_read_analog };

AD7887 * AD7887_instance(void)
{
	return & AD7887_obj;
}

inline static void AD7887_init_spi(void)
{
	while (!GET_POXI_SPI_TRANSMISSION_DONE);
	SET_POXI_SPI_SLAVE_SELECT(POXI_SPI_ADC_CS);
	SET_POXI_SPI_DATA_LENGTH(POXI_SPI_DATA_LENGTH_16_BITS);
	SET_POXI_SPI_BAUD_RATE_DIVIDER(AD7887_SPI_BAUD_RATE);
	SET_POXI_SPI_CLOCK_POLARITY(1);
	SET_POXI_SPI_CLOCK_PHASE(0);
}

static void AD7887_set_reference(AD7887_REFERENCE reference)
{
	ad7887_context = (ad7887_context & ~AD7887_REFERENCE_MASK) | reference;
}

static void AD7887_set_channel_mode(AD7887_CHANNEL_MODE channel_mode)
{
	ad7887_context = (ad7887_context & ~AD7887_CHANNEL_MODE_MASK) | channel_mode;

	if (channel_mode == DUAL_CHANNEL)
	{
		AD7887_set_reference(REF_DISABLED);
	}
}

static void AD7887_set_channel(AD7887_CHANNEL channel)
{
	ad7887_context = (ad7887_context & ~AD7887_CHANNEL_MASK) | channel;

	if (channel == AIN1)
	{
		AD7887_set_channel_mode(DUAL_CHANNEL);
	}
}

static void AD7887_set_power_mode(AD7887_POWER_MODE power_mode)
{
	ad7887_context = (ad7887_context & ~AD7887_POWER_MODE_MASK) | power_mode;
}

static uint16_t AD7887_read_analog(void)
{
	AD7887_init_spi();
	POXI_SPI_DATA = ad7887_context;
	while (!GET_POXI_SPI_TRANSMISSION_DONE);
	return 0x0FFF & POXI_SPI_DATA;
}
