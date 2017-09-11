/*
 * GUICom.h
 *
 *  Created on: 3 de feb. de 2017
 *      Author: Yarib Nevárez
 */

#ifndef SRC_GUICOM_H_
#define SRC_GUICOM_H_

#include "xil_types.h"

typedef enum
{
	TRACE_0 = 0,
	TRACE_1,
	TRACE_2,
	TRACE_3,
	TRACE_4,
	TRACE_5,
	TRACE_6,
	TRACE_7,
	TRACE_8,
	TRACE_9,
	TRACE_ALL = 0xFF
} GUITrace;

typedef uint8_t (* GUIProgressCallback)(void * data, uint32_t progress, uint32_t total);

typedef struct //class
{
    void    (* clearTrace) (GUITrace trace);
    uint8_t (* plotSamples)(GUITrace trace, double * array, uint32_t length);
    void    (* setVisible) (GUITrace trace, uint8_t visible);
    void    (* setTime)    (GUITrace trace, double time);
    void    (* setStepTime)(GUITrace trace, double time);
    void    (* textMsg)    (uint8_t id, char * msg);
    void    (* setProgressCallback)(GUIProgressCallback function, void * data);
} GUICom;

GUICom * GUICom_instance(void);

#endif /* SRC_GUICOM_H_ */
