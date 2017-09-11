/*
 * tft_graphics_library.c
 *
 *  Created on: 2 de dic. de 2016
 *      Author: Yarib
 */

#include "tft_spi_driver.h"
#include "font5x8.h"
#include "tft_graphics.h"

// The scrolling area must be a integral multiple of TEXT_HEIGHT
#define TEXT_HEIGHT 16 // Height of text to be printed and scrolled
#define BOT_FIXED_AREA 0 // Number of lines in bottom fixed area (lines counted from bottom of screen)
#define TOP_FIXED_AREA 16 // Number of lines in top fixed area (lines counted from top of screen)

//set up display using predefined command sequence
static uint16_t width, height;
//static uint16_t iScrollStart;

// The initial y coordinate of the top of the scrolling area
static uint16_t yStart = TOP_FIXED_AREA;
// yArea must be a integral multiple of TEXT_HEIGHT
//static uint16_t yArea = 320 - TOP_FIXED_AREA-BOT_FIXED_AREA;
// The initial y coordinate of the top of the bottom text line
//static uint16_t yDraw = 320 - BOT_FIXED_AREA - TEXT_HEIGHT;


static void TFTGraphics_initialize     (void);
static void TFTGraphics_speed          (uint8_t speed);
static void TFTGraphics_setAddress     (uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
static void TFTGraphics_drawRectFilled (uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t colour);
static void TFTGraphics_drawPixel      (uint16_t x, uint16_t y, uint16_t colour);
static void TFTGraphics_drawPixel_2    (uint16_t x, uint16_t y, uint8_t size, uint16_t colour);
static void TFTGraphics_drawLine       (uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t colour);
static void TFTGraphics_drawRect       (uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t colour);
static void TFTGraphics_drawClear      (uint16_t colour);
static void TFTGraphics_setRotation    (TFTGraphics_Rotation rotation);
static void TFTGraphics_drawCircle     (uint16_t poX, uint16_t poY, uint16_t radius, uint16_t colour);
static void TFTGraphics_drawChar       (uint16_t x, uint16_t y, char c, uint8_t size, uint16_t colour, uint16_t bg);
static void TFTGraphics_drawString     (uint16_t x, uint16_t y, const char *string, uint8_t size, uint16_t colour, uint16_t bg);
static void TFTGraphics_setupScrollArea(uint16_t TFA, uint16_t BFA);
static void TFTGraphics_scrollAddress  (uint16_t VSP);
static int  TFTGraphics_scrollLine     (void);

static TFTGraphics TFTGraphics_obj = {
		TFTGraphics_initialize,
		TFTGraphics_speed,
		TFTGraphics_setAddress,
		TFTGraphics_drawRectFilled,
		TFTGraphics_drawPixel,
		TFTGraphics_drawPixel_2,
		TFTGraphics_drawLine,
		TFTGraphics_drawRect,
		TFTGraphics_drawClear,
		TFTGraphics_setRotation,
		TFTGraphics_drawCircle,
		TFTGraphics_drawChar,
		TFTGraphics_drawString,
		TFTGraphics_setupScrollArea,
		TFTGraphics_scrollAddress,
		TFTGraphics_scrollLine
};

TFTGraphics * TFTGraphics_instance(void)
{
	return & TFTGraphics_obj;
}

static void TFTGraphics_initialize()
{
	tft_spi_initialize();

	tft_hardware_initialize();

	width = ILI9341_WIDTH;
	height = ILI9341_HEIGHT;

	//Soft reset
	tft_spi_write_command(ILI9341_CMD_SOFTWARE_RESET);

	//Power control A
	tft_spi_write_command(ILI9341_CMD_POWER_ON_SEQ_CONTROL);
	tft_spi_write_data(0x39);
	tft_spi_write_data(0x2C);
	tft_spi_write_data(0x00);
	tft_spi_write_data(0x34);
	tft_spi_write_data(0x02);

	//Power control B
	tft_spi_write_command(ILI9341_CMD_POWER_CONTROL_B);
	tft_spi_write_data(0x00);
	tft_spi_write_data(0xC1);
	tft_spi_write_data(0x30);

	//Driver timing control A
	tft_spi_write_command(ILI9341_CMD_DRIVER_TIMING_CONTROL_A);
	tft_spi_write_data(0x85);
	tft_spi_write_data(0x00);
	tft_spi_write_data(0x78);

	//Driver timing control B
	tft_spi_write_command(ILI9341_CMD_DRIVER_TIMING_CONTROL_B);
	tft_spi_write_data(0x00);
	tft_spi_write_data(0x00);

	//Power on sequence control
	tft_spi_write_command(ILI9341_CMD_POWER_ON_SEQUENCE);
	tft_spi_write_data(0x64);
	tft_spi_write_data(0x03);
	tft_spi_write_data(0x12);
	tft_spi_write_data(0x81);

	//Pump ratio control
	tft_spi_write_command(ILI9341_CMD_PUMP_RATIO_CONTROL);
	tft_spi_write_data(0x20);

	//power control,VRH[5:0]
	tft_spi_write_command(ILI9341_CMD_POWER_CONTROL_1);
	tft_spi_write_data(0x23);

	//Power control,SAP[2:0];BT[3:0]
	tft_spi_write_command(ILI9341_CMD_POWER_CONTROL_2);
	tft_spi_write_data(0x10);

	//vcm control
	tft_spi_write_command(ILI9341_CMD_VCOM_CONTROL_1);
	tft_spi_write_data(0x3E);
	tft_spi_write_data(0x28);

	//vcm control 2
	tft_spi_write_command(ILI9341_CMD_VCOM_CONTROL_2);
	tft_spi_write_data(0x86);

	//Memory access control
	tft_spi_write_command(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	tft_spi_write_data(0x48);

	//Pixel format
	tft_spi_write_command(ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET);
	tft_spi_write_data(0x55);

	//Framerate control, normal mode full colors
	tft_spi_write_command(ILI9341_CMD_FRAME_RATE_CONTROL_NORMAL);
	tft_spi_write_data(0x00);
	tft_spi_write_data(0x18);

	//Display function control
	tft_spi_write_command(ILI9341_CMD_DISPLAY_FUNCTION_CONTROL);
	tft_spi_write_data(0x08);
	tft_spi_write_data(0x82);
	tft_spi_write_data(0x27);

	//3gamma function disable
	tft_spi_write_command(ILI9341_CMD_ENABLE_3_GAMMA_CONTROL);
	tft_spi_write_data(0x00);

	//Gamma curve selected
	tft_spi_write_command(ILI9341_CMD_GAMMA_SET);
	tft_spi_write_data(0x01);

	//Set positive gamma correction
	tft_spi_write_command(ILI9341_CMD_POSITIVE_GAMMA_CORRECTION);
	tft_spi_write_data(0x0F);
	tft_spi_write_data(0x31);
	tft_spi_write_data(0x2B);
	tft_spi_write_data(0x0C);
	tft_spi_write_data(0x0E);
	tft_spi_write_data(0x08);
	tft_spi_write_data(0x4E);
	tft_spi_write_data(0xF1);
	tft_spi_write_data(0x37);
	tft_spi_write_data(0x07);
	tft_spi_write_data(0x10);
	tft_spi_write_data(0x03);
	tft_spi_write_data(0x0E);
	tft_spi_write_data(0x09);
	tft_spi_write_data(0x00);

	//Set negative gamma correction
	tft_spi_write_command(ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION);
	tft_spi_write_data(0x00);
	tft_spi_write_data(0x0E);
	tft_spi_write_data(0x14);
	tft_spi_write_data(0x03);
	tft_spi_write_data(0x11);
	tft_spi_write_data(0x07);
	tft_spi_write_data(0x31);
	tft_spi_write_data(0xC1);
	tft_spi_write_data(0x48);
	tft_spi_write_data(0x08);
	tft_spi_write_data(0x0F);
	tft_spi_write_data(0x0C);
	tft_spi_write_data(0x31);
	tft_spi_write_data(0x36);
	tft_spi_write_data(0x0F);

	//Exit sleep
	tft_spi_write_command(ILI9341_CMD_SLEEP_OUT);

	//Display on
	tft_spi_write_command(ILI9341_CMD_DISPLAY_ON);
}

static void TFTGraphics_speed(uint8_t speed)
{
	tft_spi_baud_rate(0xFF - speed);
}

//set coordinate for print or other function
static void TFTGraphics_setAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2) {
	tft_spi_write_command(ILI9341_CMD_COLUMN_ADDRESS_SET);
	tft_spi_write_data16(x1);
	tft_spi_write_data16(x2);

	tft_spi_write_command(ILI9341_CMD_PAGE_ADDRESS_SET);
	tft_spi_write_data16(y1);
	tft_spi_write_data16(y2);
	// memory write
	tft_spi_write_command(ILI9341_CMD_MEMORY_WRITE);
}

//draw colour filled rectangle
static void TFTGraphics_drawRectFilled(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t colour)
{
	if ((x >= width) || (y >= height)) return;
	if ((x + w - 1) >= width) w = width - x;
	if ((y + h - 1) >= height) h = height - y;
	TFTGraphics_setAddress(x, y, x + w - 1, y + h - 1);
	for (y = h; y > 0; y--)
		for (x = w; x > 0; x--)
			tft_spi_write_data16(colour);
}

// draw pixel
// pixels will always be counted from right side.x is representing LCD width which will always be less than 240.Y is representing LCD height which will always be less than 320
static void TFTGraphics_drawPixel(uint16_t x, uint16_t y, uint16_t colour) {
	if ((x < 0) || (x >= width) || (y < 0) || (y >= height)) return;
	TFTGraphics_setAddress(x, y, x + 1, y + 1);
	tft_spi_write_data16(colour);
}

static void TFTGraphics_drawPixel_2(uint16_t x, uint16_t y, uint8_t size, uint16_t colour) {
	if (size == 1) // default size or big size
		TFTGraphics_drawPixel(x, y, colour);
	else
		TFTGraphics_drawRectFilled(x, y, size, size, colour);
}

// Draw a line from x0, y0 to x1, y1
// Note:    This is a version of Bresenham's line drawing algorithm
//          It only draws lines from left to right!
static void TFTGraphics_drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t colour) {
    int16_t dy = y1 - y0;
    int16_t dx = x1 - x0;
    int16_t stepx, stepy;

    if (dy < 0) {
        dy = -dy; stepy = -1;
    }
    else stepy = 1;

    if (dx < 0) {
        dx = -dx; stepx = -1;
    }
    else stepx = 1;

    dy <<= 1;                           // dy is now 2*dy
    dx <<= 1;                           // dx is now 2*dx

    TFTGraphics_drawPixel(x0, y0, colour);

    if (dx > dy) {
        int fraction = dy - (dx >> 1);  // same as 2*dy - dx
        while (x0 != x1) {
            if (fraction >= 0) {
                y0 += stepy;
                fraction -= dx;         // same as fraction -= 2*dx
            }
            x0 += stepx;
            fraction += dy;                 // same as fraction -= 2*dy
            TFTGraphics_drawPixel(x0, y0, colour);
        }
    } else {
        int fraction = dx - (dy >> 1);
        while (y0 != y1) {
            if (fraction >= 0) {
                x0 += stepx;
                fraction -= dy;
            }
            y0 += stepy;
            fraction += dx;
            TFTGraphics_drawPixel(x0, y0, colour);
        }
    }
}

static void TFTGraphics_drawRect(uint16_t x,uint16_t y,uint16_t w,uint16_t h,uint16_t colour) {
	// two horizontal lines
	TFTGraphics_drawLine(x, y, x + w, y, colour);
	TFTGraphics_drawLine(x, y + h, x + w, y + h, colour);
	// two vertical lines
	TFTGraphics_drawLine(x, y, x, y + h, colour);
	TFTGraphics_drawLine(x + w, y, x + w, y + h, colour);
}

//clear lcd and fill with colour
static void TFTGraphics_drawClear(uint16_t colour) {
	TFTGraphics_drawRectFilled(0,0,width, height, colour);
}

//rotate screen at desired orientation
static void TFTGraphics_setRotation(TFTGraphics_Rotation rotation) {
	tft_spi_write_command(ILI9341_CMD_MEMORY_ACCESS_CONTROL);
	switch (rotation)  {
		case ROT0:
			tft_spi_write_data(0x40 | 0x08);
			width = ILI9341_HEIGHT;
			height = ILI9341_WIDTH;
		break;
		case ROT90:
			tft_spi_write_data(0x20 | 0x08);
			width  = ILI9341_WIDTH;
			height = ILI9341_HEIGHT;
		break;
		case ROT180:
			tft_spi_write_data(0x80 | 0x08);
			width  = ILI9341_HEIGHT;
			height = ILI9341_WIDTH;
		break;
		case ROT270:
			tft_spi_write_data(0x40 | 0x80 | 0x20 | 0x08);
			width  = ILI9341_WIDTH;
			height = ILI9341_HEIGHT;
		break;
	}
}

static void TFTGraphics_drawCircle(uint16_t poX, uint16_t poY, uint16_t radius, uint16_t colour) {
    int x = -radius, y = 0, err = 2-2*radius, e2;
    do {
    	TFTGraphics_drawPixel(poX-x, poY+y,colour);
    	TFTGraphics_drawPixel(poX+x, poY+y,colour);
    	TFTGraphics_drawPixel(poX+x, poY-y,colour);
    	TFTGraphics_drawPixel(poX-x, poY-y,colour);
        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    } while (x <= 0);
}

static void TFTGraphics_drawChar(uint16_t x, uint16_t y, char c, uint8_t size, uint16_t colour, uint16_t bg) {
	int8_t i;
	int8_t j;
	// draw. optimisation:6th font line is set as 0, to lower font array size
	for (i=0; i < FONT_WIDTH; i++ ) {
		uint8_t line = (i == FONT_WIDTH-1)? 0 : *(font5x8 + (c * (FONT_WIDTH - 1)) + i);
		for (j = 0; j < FONT_HEIGHT; j++) {
			if (line & 0x1) {
				if (colour != TRANSPARENT) TFTGraphics_drawPixel_2(x + i*size, y + j*size, size, colour);
			}
			else {
				if (bg != TRANSPARENT) TFTGraphics_drawPixel_2(x + i*size, y + j*size, size, bg);
			}
			line >>= 1;
		}
	}
}

static void TFTGraphics_drawString(uint16_t x, uint16_t y, const char *string, uint8_t size, uint16_t colour, uint16_t bg) {
    unsigned char c;
    while ( (c = *string++) ) {
    	TFTGraphics_drawChar(x, y, c, size, colour, bg);
        if(x <= width - 2 * FONT_WIDTH * size)
        	x += size * FONT_WIDTH;
        else {
        	x = 0;
        	y += size * FONT_HEIGHT;
        }
    }
}

// Setup a portion of the screen for vertical scrolling
// We are using a hardware feature of the display, so we can only scroll in portrait orientation
static void TFTGraphics_setupScrollArea(uint16_t TFA, uint16_t BFA) {
  tft_spi_write_command(ILI9341_CMD_VERT_SCROLL_DEFINITION); // Vertical scroll definition
  tft_spi_write_data16(TFA);
  tft_spi_write_data16(320-TFA-BFA);
  tft_spi_write_data16(BFA);
}

// Setup the vertical scrolling start address
static void TFTGraphics_scrollAddress(uint16_t VSP) {
	tft_spi_write_command(ILI9341_CMD_VERT_SCROLL_START_ADDRESS);
	tft_spi_write_data16(VSP);
}

// Call this function to scroll the display one text line
static int TFTGraphics_scrollLine() {
	int yTemp = yStart; // Store the old yStart, this is where we draw the next line
	// fill remaining space
	TFTGraphics_drawRectFilled(0,yStart,width,TEXT_HEIGHT, BLACK);
	// Change the top of the scroll area
	yStart+=TEXT_HEIGHT;
	// The value must wrap around as the screen memory is a circular buffer
	if (yStart >= 320 - BOT_FIXED_AREA) yStart = TOP_FIXED_AREA + (yStart - 320 + BOT_FIXED_AREA);
	// Now we can scroll the display
	TFTGraphics_scrollAddress(yStart);
	return  yTemp;
}
