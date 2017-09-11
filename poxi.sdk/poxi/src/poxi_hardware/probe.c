/*
 * probe.c
 *
 *  Created on: 6 de ene. de 2017
 *      Author: Yarib
 */

#include "probe.h"
#include "POXI.h"

static void LightProbe_red     (uint8_t val);
static void LightProbe_infrared(uint8_t val);
static void LightProbe_light   (LightProbe_Light light);

static LightProbe LightProbe_obj = { LightProbe_red,
                                     LightProbe_infrared,
                                     LightProbe_light};

LightProbe * LightProbe_instance()
{
	return & LightProbe_obj;
}

static void LightProbe_red (uint8_t val)
{
	SET_POXI_SPI_LED_RED(val);
}

static void LightProbe_infrared (uint8_t val)
{
	SET_POXI_SPI_LED_INFRARED(val);
}

static void LightProbe_light (LightProbe_Light light)
{
	switch(light)
	{
    case LIGHTPROBE_OFF:
        SET_POXI_SPI_LED_RED(0);
        SET_POXI_SPI_LED_INFRARED(0);
        break;
    case LIGHTPROBE_RED:
        SET_POXI_SPI_LED_RED(1);
        SET_POXI_SPI_LED_INFRARED(0);
        break;
    case LIGHTPROBE_INFRARED:
        SET_POXI_SPI_LED_RED(0);
        SET_POXI_SPI_LED_INFRARED(1);
        break;
	}
}
