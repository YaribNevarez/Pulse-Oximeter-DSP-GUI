/*
 * probe.h
 *
 *  Created on: 6 de ene. de 2017
 *      Author: Yarib
 */

#ifndef SRC_POXI_HARDWARE_PROBE_H_
#define SRC_POXI_HARDWARE_PROBE_H_

#include "xil_types.h"

typedef enum
{
	LIGHTPROBE_OFF = 0,
	LIGHTPROBE_RED,
	LIGHTPROBE_INFRARED
} LightProbe_Light;

typedef struct
{
    void (*red)     (uint8_t val);
    void (*infrared)(uint8_t val);
    void (*light)   (LightProbe_Light light);
} LightProbe;

LightProbe * LightProbe_instance();

#endif /* SRC_POXI_HARDWARE_PROBE_H_ */
