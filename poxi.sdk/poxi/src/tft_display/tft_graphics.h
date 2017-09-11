/*
 * tft_gl.h
 *
 *  Created on: 2 de dic. de 2016
 *      Author: Yarib
 */

#ifndef SRC_TFT_DISPLAY_TFT_GRAPHICS_H_
#define SRC_TFT_DISPLAY_TFT_GRAPHICS_H_

#include "xil_types.h"
#include "ili9341.h"

typedef enum {
	ROT0 = 0,	// Portrait
	ROT90 = 1,	// Landscape
	ROT180 = 2,	// Flipped portrait
	ROT270 = 3	// Flipped landscape
} TFTGraphics_Rotation;

typedef struct
{
    void (*initialize)     (void);
    void (*speed)          (uint8_t rate);
    void (*setAddress)     (uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
    void (*drawRectFilled) (uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t colour);
    void (*drawPixel)      (uint16_t x, uint16_t y, uint16_t colour);
    void (*drawPixel_2)    (uint16_t x, uint16_t y, uint8_t size, uint16_t colour);
    void (*drawLine)       (uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t colour);
    void (*drawRect)       (uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t colour);
    void (*drawClear)      (uint16_t colour);
    void (*setRotation)    (TFTGraphics_Rotation rotation);
    void (*drawCircle)     (uint16_t poX, uint16_t poY, uint16_t radius, uint16_t colour);
    void (*drawChar)       (uint16_t x, uint16_t y, char c, uint8_t size, uint16_t colour, uint16_t bg);
    void (*drawString)     (uint16_t x, uint16_t y, const char *string, uint8_t size, uint16_t colour, uint16_t bg);
    void (*setupScrollArea)(uint16_t TFA, uint16_t BFA);
    void (*scrollAddress)  (uint16_t VSP);
    int  (*scrollLine)     (void);
} TFTGraphics;

TFTGraphics * TFTGraphics_instance(void);

#endif /* SRC_TFT_DISPLAY_TFT_GRAPHICS_H_ */
