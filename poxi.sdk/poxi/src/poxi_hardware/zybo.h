/*
 * zybo.h
 *
 *  Created on: 6 de ene. de 2017
 *      Author: Yarib Nevárez
 */

#ifndef SRC_POXI_HARDWARE_ZYBO_H_
#define SRC_POXI_HARDWARE_ZYBO_H_
#include "xil_types.h"

typedef struct
{
    void    (*leds)    (uint8_t val);
    void    (*led)     (uint8_t ld, uint8_t val);
    uint8_t (*switches)(void);
    uint8_t (*switch_) (uint8_t sw);
    uint8_t (*buttons) (void);
    uint8_t (*button)  (uint8_t btn);
} ZYBO;

ZYBO * ZYBO_instance();

#endif /* SRC_POXI_HARDWARE_ZYBO_H_ */
