/*
 * ad7887.h
 *
 *  Created on: 6 de dic. de 2016
 *      Author: Yarib
 */

#ifndef SRC_POXI_HARDWARE_AD7887_H_
#define SRC_POXI_HARDWARE_AD7887_H_
#include "xil_types.h"

typedef enum
{
	REF_ENABLED  = 0,
	REF_DISABLED = 0x2000
} AD7887_REFERENCE;

typedef enum
{
	SINGLE_CHANNEL = 0,
	DUAL_CHANNEL   = 0x1000
} AD7887_CHANNEL_MODE;

typedef enum
{
	AIN0 = 0,
	AIN1 = 0x0800
} AD7887_CHANNEL;

typedef enum
{
	MODE1 = 0,			// The AD7887 enters shutdown if the CS input is 1 and is in full power mode when CS is 0.
	MODE2 = 0x0100,		// The AD7887 is always fully powered up, regardless of the status of any of the logic inputs.
	MODE3 = 0x0200,		// The AD7887 automatically enters shutdown mode at the end of each conversion, regardless of the state of CS.
	MODE4 = 0x0300		// In this standby mode, portions of the AD7887 are powered down but the on-chip reference voltage remains powered up.
} AD7887_POWER_MODE;

typedef struct{
    void     (*set_reference)   (AD7887_REFERENCE reference);
    void     (*set_channel_mode)(AD7887_CHANNEL_MODE channel_mode);
    void     (*set_channel)     (AD7887_CHANNEL channel);
    void     (*set_power_mode)  (AD7887_POWER_MODE power_mode);
    uint16_t (*read_analog)     (void);
} AD7887;

// Singleton instance
AD7887 * AD7887_instance(void);


#endif /* SRC_POXI_HARDWARE_AD7887_H_ */
