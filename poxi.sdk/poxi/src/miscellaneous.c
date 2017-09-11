/*
 * miscellaneous.c
 *
 *  Created on: 4 de feb. de 2017
 *      Author: Yarib Nevárez
 */

#include "miscellaneous.h"

void delay_ms(unsigned int length_ms)
{
	length_ms *= 108200;
	while (length_ms--);
}
