/*
 * framepanel.c
 *
 *  Created on: 10 de ene. de 2017
 *      Author: Yarib
 */

#include "framepanel.h"

#include "..\graphics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
	FRAMEPANEL_VIRTUALTABLE_MEMBERS
	uint16_t       x_pos;
	uint16_t       y_pos;
	uint16_t       width;
	uint16_t       height;
	uint32_t       backgroundColor;
	uint32_t       lineColor;
	TFTGraphics *  canvas;
} FramePanel_private;


static void FramePanel_delete    (FramePanel ** obj);
static void FramePanel_draw      (FramePanel * obj);
static void FramePanel_refresh   (FramePanel * obj);
static void FramePanel_clear     (FramePanel * obj);
static void FramePanel_set_x     (FramePanel * obj, int32_t x_pos);
static void FramePanel_set_y     (FramePanel * obj, int32_t y_pos);
static void FramePanel_set_width (FramePanel * obj, int32_t width);
static void FramePanel_set_height(FramePanel * obj, int32_t height);
static void FramePanel_set_lineColor      (FramePanel * obj, int32_t line_color);
static void FramePanel_set_backgroundColor(FramePanel * obj, int32_t background_color);
static void FramePanel_give_widget        (FramePanel * obj, Widget * child);

static void FramePanel_init_virtual_table(FramePanel_private * thiz)
{
	if (thiz != NULL)
	{
		thiz->delete = (WidgetDeleteFunc) FramePanel_delete;
		thiz->draw = (WidgetDrawFunc) FramePanel_draw;
		thiz->refresh = (WidgetRefreshFunc) FramePanel_refresh;
		thiz->clear = (WidgetClearFunc) FramePanel_clear;
		thiz->set_x = FramePanel_set_x;
		thiz->set_y = FramePanel_set_y;
		thiz->set_width = FramePanel_set_width;
		thiz->set_height = FramePanel_set_height;
		thiz->set_lineColor = FramePanel_set_lineColor;
		thiz->set_backgroundColor = FramePanel_set_backgroundColor;
		thiz->give_widget = FramePanel_give_widget;
	}
}


FramePanel * FramePanel_new (uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t line_color, uint32_t background_color)
{
	FramePanel_private * thiz = (FramePanel_private *) malloc(sizeof(FramePanel_private));

	if (thiz != NULL)
	{
		memset(thiz, 0, sizeof(FramePanel_private));
		FramePanel_init_virtual_table(thiz);
		thiz->x_pos = x;
		thiz->y_pos = y;
		thiz->width = width;
		thiz->height = height;
		thiz->lineColor = line_color;
		thiz->backgroundColor = background_color;

		thiz->canvas = TFTGraphics_instance();
	}

	return (FramePanel *)thiz;
}

static void FramePanel_give_widget (FramePanel * obj, Widget * child)
{
	if ((obj != NULL) && (child != NULL))
	{
		Widget * w;
		Widget * last;

		for (last = NULL, w = obj->first_child; w != NULL; w = w->next)
		{
			last = w;
		}

		if (last != NULL)
		{
			last->next = child;
			child->prev = last;
		}
		else
		{
			obj->first_child = child;
		}

		child->parent = (Widget *) obj;
	}
}

static void FramePanel_deleteChildren (FramePanel * obj)
{
	if (obj != NULL)
	{
		FramePanel_private * thiz = (FramePanel_private *) obj;
		Widget * w;
		Widget * next;

		for (w = thiz->first_child; w != NULL; w = next)
		{
			next = w->next;
			w->delete(&w);
		}
	}
}

static void FramePanel_delete (FramePanel ** obj)
{
	if (obj != NULL && *obj != NULL)
	{
		FramePanel_private * thiz = (FramePanel_private *) *obj;

		FramePanel_deleteChildren(*obj);

		free(thiz);
		*obj = NULL;
	}
}

static void FramePanel_draw (FramePanel * obj)
{
	if (obj != NULL)
	{
		FramePanel_private * thiz = (FramePanel_private *) obj;
		TFTGraphics * canvas = thiz->canvas;
		Widget * w;

		if (canvas != NULL)
		{
			canvas->drawRectFilled(thiz->x_pos, thiz->y_pos, thiz->width, thiz->height, thiz->backgroundColor);
			canvas->drawRect(thiz->x_pos, thiz->y_pos, thiz->width, thiz->height, thiz->lineColor);
		}

		for (w = thiz->first_child; w != NULL; w = w->next)
		{
			w->draw(w);
		}
	}
}

static void FramePanel_refresh (FramePanel * obj)
{
	if (obj != NULL)
	{
		FramePanel_private * thiz = (FramePanel_private *) obj;
		TFTGraphics * canvas = thiz->canvas;
		Widget * w;

		if (canvas != NULL)
		{
			canvas->drawRect(thiz->x_pos, thiz->y_pos, thiz->width, thiz->height, thiz->lineColor);
		}

		for (w = thiz->first_child; w != NULL; w = w->next)
		{
			w->refresh(w);
		}
	}
}

static void FramePanel_clear (FramePanel * obj)
{
	if (obj != NULL)
	{
		FramePanel_deleteChildren(obj);
		FramePanel_draw(obj);
	}
}

static void FramePanel_set_x (FramePanel * obj, int32_t x_pos)
{
	if (obj != NULL)
	{
		FramePanel_private * thiz = (FramePanel_private *) obj;
		thiz->x_pos = x_pos;

		FramePanel_draw(obj);
	}
}

static void FramePanel_set_y (FramePanel * obj, int32_t y_pos)
{
	if (obj != NULL)
	{
		FramePanel_private * thiz = (FramePanel_private *) obj;
		thiz->y_pos = y_pos;
		FramePanel_draw(obj);
	}
}

static void FramePanel_set_width (FramePanel * obj, int32_t width)
{
	if (obj != NULL)
	{
		FramePanel_private * thiz = (FramePanel_private *) obj;
		thiz->width = width;
		FramePanel_draw(obj);
	}
}

static void FramePanel_set_height (FramePanel * obj, int32_t height)
{
	if (obj != NULL)
	{
		FramePanel_private * thiz = (FramePanel_private *) obj;
		thiz->height = height;
		FramePanel_draw(obj);
	}
}

static void FramePanel_set_lineColor (FramePanel * obj, int32_t line_color)
{
	if (obj != NULL)
	{
		FramePanel_private * thiz = (FramePanel_private *) obj;
		thiz->lineColor = line_color;
		FramePanel_refresh(obj);
	}
}

static void FramePanel_set_backgroundColor (FramePanel * obj, int32_t background_color)
{
	if (obj != NULL)
	{
		FramePanel_private * thiz = (FramePanel_private *) obj;
		thiz->backgroundColor = background_color;
		FramePanel_draw(obj);
	}
}

