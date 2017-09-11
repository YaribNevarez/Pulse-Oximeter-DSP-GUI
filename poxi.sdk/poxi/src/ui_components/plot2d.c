
/*
 * plot2d.c
 *
 *  Created on: 4 de ene. de 2017
 *      Author: Yarib Nevárez
 */
#include "plot2d.h"

#include "..\graphics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	uint16_t y;
	uint32_t c;
} Point2D;

typedef struct
{
	PLOT2D_VIRTUALTABLE_MEMBERS
	Point2D *     plot2D_space;
	Point2D *     plot2D_old_space;
	uint16_t      x_pos;
	uint16_t      y_pos;
	uint16_t      size;
	uint16_t      height;
	uint16_t      index;
	uint16_t      old_index;
	uint32_t      background_color;
	uint32_t      line_color;
	TFTGraphics * canvas;
} Plot2D_private;

static void Plot2D_delete(Plot2D ** obj);

static void Plot2D_add(Plot2D * obj, uint16_t y, uint32_t c);

static void Plot2D_refresh(Plot2D * obj);

static void Plot2D_draw(Plot2D * obj);

static void Plot2D_clear(Plot2D * obj);

static void Plot2D_init_virtual_table(Plot2D * obj)
{
	if (obj != NULL)
	{
		Plot2D_private * thiz = (Plot2D_private *) obj;
		thiz->delete    = (WidgetDeleteFunc) Plot2D_delete;
		thiz->add_point = Plot2D_add;
		thiz->refresh   = (WidgetRefreshFunc) Plot2D_refresh;
		thiz->draw      = (WidgetDrawFunc) Plot2D_draw;
		thiz->clear     = (WidgetClearFunc) Plot2D_clear;
	}
}

Plot2D * Plot2D_new(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t line_color, uint32_t background_color)
{
	Plot2D_private * thiz = (Plot2D_private *) malloc(sizeof(Plot2D_private));

	if (thiz != NULL)
	{
		memset(thiz, 0, sizeof(Plot2D_private));

		Plot2D_init_virtual_table((Plot2D *)thiz);

		thiz->x_pos = x;
		thiz->y_pos = y;
		thiz->background_color = background_color;
		thiz->line_color = line_color;
		thiz->size = width;
		thiz->height = height;

		thiz->plot2D_space     = (Point2D *) malloc(sizeof(Point2D) * width);
		memset(thiz->plot2D_space, (int)0, sizeof(Point2D) * width);
		thiz->index = 0;

		thiz->plot2D_old_space = (Point2D *) malloc(sizeof(Point2D) * width);
		memset(thiz->plot2D_old_space, 0, sizeof(Point2D) * width);
		thiz->old_index = 0;

		thiz->canvas = TFTGraphics_instance();
	}
	return (Plot2D *) thiz;
}

static void Plot2D_delete(Plot2D ** obj)
{
	if (obj != NULL && *obj != NULL)
	{
		Plot2D_private * thiz = (Plot2D_private *) *obj;

		if (thiz->plot2D_space != NULL)
		{
			free(thiz->plot2D_space);
		}

		if (thiz->plot2D_old_space != NULL)
		{
			free(thiz->plot2D_old_space);
		}

		free(thiz);
		*obj = NULL;
	}
}

static void Plot2D_add(Plot2D * obj, uint16_t y, uint32_t c)
{
	if (obj != NULL)
	{
		Plot2D_private * thiz = (Plot2D_private *) obj;
		if(thiz->plot2D_space != NULL)
		{
			if (thiz->height <= y)
			{
				y = 0;
				c = thiz->background_color;
			}

			if (thiz->index < thiz->size)
			{
				thiz->plot2D_space[thiz->index].y = y;
				thiz->plot2D_space[thiz->index].c = c;

				thiz->index ++;
			}
			else
			{
				memcpy(thiz->plot2D_space, thiz->plot2D_space + 1, sizeof(Point2D)*(thiz->size - 1));

				thiz->plot2D_space[thiz->size - 1].y = y;
				thiz->plot2D_space[thiz->size - 1].c = c;
			}
			Plot2D_refresh(obj);
		}
	}
}

static void Plot2D_refresh(Plot2D * obj)
{
	if (obj != NULL)
	{
		Plot2D_private * thiz   = (Plot2D_private *) obj;
		TFTGraphics *    canvas = thiz->canvas;
		if ((thiz->plot2D_space != NULL) && (canvas != NULL))
		{
			int16_t i;

			for (i = 0; i < thiz->index - 1; i ++)
			{
				if (thiz->index == thiz->old_index)
				canvas->drawLine(thiz->x_pos + i + 1,
						 thiz->y_pos + thiz->height - thiz->plot2D_old_space[i].y,
						 thiz->x_pos + i + 1 + 1,
						 thiz->y_pos + thiz->height - thiz->plot2D_old_space[i+1].y,
						 thiz->background_color);

				canvas->drawLine(thiz->x_pos + i + 1,
						 thiz->y_pos + thiz->height - thiz->plot2D_space[i].y,
						 thiz->x_pos + i + 1 + 1,
						 thiz->y_pos + thiz->height - thiz->plot2D_space[i+1].y,
						 thiz->plot2D_space[i].c);
			}

			memcpy(thiz->plot2D_old_space, thiz->plot2D_space, sizeof(Point2D) * thiz->index);
			thiz->old_index = thiz->index;
		}
	}
}

static void Plot2D_draw(Plot2D * obj)
{
	if (obj != NULL)
	{
		Plot2D_private * thiz = (Plot2D_private *) obj;
		TFTGraphics *    canvas = thiz->canvas;
		if ((thiz->plot2D_space != NULL) && (canvas != NULL))
		{
			int16_t i;

			canvas->drawRectFilled(thiz->x_pos + 1, thiz->y_pos + 1, thiz->size, thiz->height, thiz->background_color);

			canvas->drawRect(thiz->x_pos, thiz->y_pos, thiz->size + 1, thiz->height + 1, thiz->line_color);

			for (i = 0; i < thiz->index - 1; i ++)
			{
				canvas->drawLine(thiz->x_pos + i + 1,
						 thiz->y_pos + thiz->height - thiz->plot2D_space[i].y,
						 thiz->x_pos + i + 1 + 1,
						 thiz->y_pos + thiz->height - thiz->plot2D_space[i+1].y,
						 thiz->plot2D_space[i].c);
			}

			memcpy(thiz->plot2D_old_space, thiz->plot2D_space, sizeof(Point2D) * thiz->index);
			thiz->old_index = thiz->index;
		}
	}
}

static void Plot2D_clear(Plot2D * obj)
{
	if (obj != NULL)
	{
		Plot2D_private * thiz = (Plot2D_private *) obj;
		if (thiz->plot2D_space != NULL)
		{
			memset(thiz->plot2D_space, 0, sizeof(Point2D) * thiz->size);
			thiz->index = 0;
			if (thiz->plot2D_old_space != NULL)
			{
				memset(thiz->plot2D_old_space, 0, sizeof(Point2D) * thiz->size);
				thiz->old_index = 0;
			}

			Plot2D_refresh(obj);
		}
	}
}
