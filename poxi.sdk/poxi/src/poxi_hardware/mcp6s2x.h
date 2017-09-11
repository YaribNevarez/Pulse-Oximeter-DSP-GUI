/*
 * mcp6s2x.h
 *
 *  Created on: 6 de dic. de 2016
 *      Author: Yarib Nevárez
 */

#ifndef SRC_POXI_HARDWARE_MCP6S2X_H_
#define SRC_POXI_HARDWARE_MCP6S2X_H_

//| M2 | M1 | M0 | - | - | - | - | A0 |
// 0    0     0    NOP
// 0    0     1    Shutdown
// 0    1     0    Write to register
//
//                                 A0
//                                 1 Channel Register
//                                 0 Gain register
//
//| - | - | - | - | - | G2 | G1 | G0 |
//1, 2, 4, 5, 8, 10, 16, 32
//
//| - | - | - | - | - | C2 | C1 | C0 |

typedef enum
{
	CH0 = 0,
	CH1 = 1,
	CH2 = 2,
	CH3 = 3,
	CH4 = 4,
	CH5 = 5,
	CH6 = 6,
	CH7 = 7
} MCP6S2X_CHANNEL;

typedef enum
{
	GAIN_1 = 0,
	GAIN_2 = 1,
	GAIN_4 = 2,
	GAIN_5 = 3,
	GAIN_8 = 4,
	GAIN_10 = 5,
	GAIN_16 = 6,
	GAIN_32 = 7
} MCP6S2X_GAIN;


typedef struct
{
    void (*shutdown)(void);
    void (*select_channel)(MCP6S2X_CHANNEL channel);
    void (*set_gain)(MCP6S2X_GAIN gain);
} MCP6S2X;

MCP6S2X * MCP6S2X_instance(void);

#endif /* SRC_POXI_HARDWARE_MCP6S2X_H_ */
