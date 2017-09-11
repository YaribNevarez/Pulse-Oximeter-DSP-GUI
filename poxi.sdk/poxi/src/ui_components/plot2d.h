/*
 * plot2d.h
 *
 *  Created on: 3 de ene. de 2017
 *      Author: Yarib Nevárez
 */

#ifndef PLOT2D_H_
#define PLOT2D_H_

#include "xil_types.h"
#include "widget.h"

typedef struct Plot2D_public Plot2D;

#define PLOT2D_VIRTUALTABLE_MEMBERS \
		WIDGET_VIRTUALTABLE_MEMBERS \
        void     (* add_point) (Plot2D * obj, uint16_t value, uint32_t color);

struct Plot2D_public
{
    PLOT2D_VIRTUALTABLE_MEMBERS
};

Plot2D * Plot2D_new(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t line_color, uint32_t background_color);

#endif /* PLOT2D_H_ */
