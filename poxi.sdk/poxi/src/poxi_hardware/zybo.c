/*
 * zybo.c
 *
 *  Created on: 6 de ene. de 2017
 *      Author: Yarib Nevárez
 */
#include "zybo.h"
#include "POXI.h"

static void    ZYBO_leds    (uint8_t val);
static void    ZYBO_led     (uint8_t ld, uint8_t val);
static uint8_t ZYBO_switches(void);
static uint8_t ZYBO_switch_ (uint8_t sw);
static uint8_t ZYBO_buttons (void);
static uint8_t ZYBO_button  (uint8_t btn);

static ZYBO ZYBO_obj = { ZYBO_leds,
                         ZYBO_led,
                         ZYBO_switches,
                         ZYBO_switch_,
                         ZYBO_buttons,
                         ZYBO_button };

static uint8_t ZYBO_leds_i = 0;

ZYBO * ZYBO_instance()
{
	return & ZYBO_obj;
}


static void ZYBO_leds (uint8_t val)
{
	ZYBO_leds_i = val;
	SET_POXI_ZYBO_LEDS(ZYBO_leds_i);
}

static void ZYBO_led (uint8_t ld, uint8_t val)
{
	if (val) { ZYBO_leds_i |=    1 << ld; }
	else     { ZYBO_leds_i &=  ~(1 << ld);}

	SET_POXI_ZYBO_LEDS(ZYBO_leds_i);
}

static uint8_t ZYBO_switches (void)
{
	return GET_POXI_ZYBO_SWITCHS;
}

static uint8_t ZYBO_switch_ (uint8_t sw)
{
	return (GET_POXI_ZYBO_SWITCHS & (1 << sw)) > 0;
}

static uint8_t ZYBO_buttons (void)
{
	return GET_POXI_ZYBO_PUSHBUTTONS;
}

static uint8_t ZYBO_button (uint8_t btn)
{
	return (GET_POXI_ZYBO_PUSHBUTTONS & (1 << btn)) > 0;
}
