/*
 * poxi.h
 *
 *  Created on: 11 de feb. de 2017
 *      Author: Yarib Nev�rez
 */

#ifndef SRC_POXI_H_
#define SRC_POXI_H_
#include "xil_types.h"

typedef struct
{
	uint8_t (* initialize)(void);
	uint8_t (* run)(void);
	void    (* dispose)(void);
} Poxi;

Poxi * Poxi_instance(void);
#endif /* SRC_POXI_H_ */