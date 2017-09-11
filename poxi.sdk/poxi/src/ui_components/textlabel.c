/*
 * textlabel.c
 *
 *  Created on: 4 de ene. de 2017
 *      Author: Yarib Nevárez
 */

#include "textlabel.h"

#include "..\graphics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _DYNAMIC_MALLOC_

#ifndef _DYNAMIC_MALLOC_
#define MAX_TEXT_LENGTH (80)
#endif

typedef struct
{
	TEXTLABEL_VIRTUALTABLE_MEMBERS
	uint16_t       x_pos;
	uint16_t       y_pos;
	uint16_t       width;
	uint16_t       height;
	uint32_t       background_color;
	uint32_t       text_color;
	TextLabel_Type type;
	uint8_t        font_size;
#ifdef _DYNAMIC_MALLOC_
	char *         text;
	char *         last_text;
#else
	char           text[MAX_TEXT_LENGTH];
	char           last_text[MAX_TEXT_LENGTH];
#endif
	int32_t        number;
	TFTGraphics *  canvas;
} TextLabel_private;


static void TextLabel_delete    (TextLabel ** obj);
static void TextLabel_draw      (TextLabel * obj);
static void TextLabel_refresh   (TextLabel * obj);
static void TextLabel_clear     (TextLabel * obj);
static void TextLabel_set_x     (TextLabel * obj, int32_t x_pos);
static void TextLabel_set_y     (TextLabel * obj, int32_t y_pos);
static void TextLabel_set_width (TextLabel * obj, int32_t width);
static void TextLabel_set_height(TextLabel * obj, int32_t height);
static void TextLabel_set_text  (TextLabel * obj, char * str);
static void TextLabel_set_number(TextLabel * obj, int32_t number);
static void TextLabel_set_label_type (TextLabel * obj, TextLabel_Type type);
static void TextLabel_set_font_size  (TextLabel * obj, uint8_t font_size);
static void TextLabel_set_text_color      (TextLabel * obj, int32_t text_color);
static void TextLabel_set_background_color(TextLabel * obj, int32_t background_color);

static void TextLabel_init_virtual_table(TextLabel_private * thiz)
{
	if (thiz != NULL)
	{
		thiz->delete = (WidgetDeleteFunc) TextLabel_delete;
		thiz->draw = (WidgetDrawFunc) TextLabel_draw;
		thiz->refresh = (WidgetRefreshFunc) TextLabel_refresh;
		thiz->clear = (WidgetClearFunc) TextLabel_clear;
		thiz->set_x = TextLabel_set_x;
		thiz->set_y = TextLabel_set_y;
		thiz->set_width = TextLabel_set_width;
		thiz->set_height = TextLabel_set_height;
		thiz->set_text = TextLabel_set_text;
		thiz->set_number = TextLabel_set_number;
		thiz->set_label_type = TextLabel_set_label_type;
		thiz->set_font_size = TextLabel_set_font_size;
		thiz->set_text_color = TextLabel_set_text_color;
		thiz->set_background_color = TextLabel_set_background_color;
	}
}


TextLabel * TextLabel_new (uint16_t x, uint16_t y, uint16_t width, uint16_t height, char * str, uint32_t text_color, uint32_t background_color)
{
	TextLabel_private * thiz = (TextLabel_private *) malloc(sizeof(TextLabel_private));

	if (thiz != NULL)
	{
		memset(thiz, 0, sizeof(TextLabel_private));
		TextLabel_init_virtual_table(thiz);
		thiz->x_pos = x;
		thiz->y_pos = y;
		thiz->width = width;
		thiz->height = height;
		TextLabel_set_text((TextLabel *)thiz, str);
		thiz->text_color = text_color;
		thiz->background_color = background_color;
		thiz->font_size = 1;

		thiz->canvas = TFTGraphics_instance();
	}

	return (TextLabel *)thiz;
}

static void TextLabel_delete (TextLabel ** obj)
{
	if (obj != NULL && *obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) *obj;

#ifdef _DYNAMIC_MALLOC_
		if (thiz->last_text != NULL)
		{
			free(thiz->last_text);
		}

		if (thiz->text != NULL)
		{
			free(thiz->text);
		}
#endif

		free(thiz);
		*obj = NULL;
	}
}

static void TextLabel_draw (TextLabel * obj)
{
	if (obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;

#ifdef _DYNAMIC_MALLOC_
		if (thiz->text != NULL)
#endif
		if (thiz->canvas != NULL)
		{
			thiz->canvas->drawString(thiz->x_pos,
					   thiz->y_pos,
					   thiz->text,
					   thiz->font_size,
					   thiz->text_color,
					   thiz->background_color);

#ifdef _DYNAMIC_MALLOC_
			if (thiz->last_text != NULL)
			{
				free(thiz->last_text);
			}
			thiz->last_text = malloc(sizeof(char) * (strlen(thiz->text) + 1));
			if (thiz->last_text != NULL)
#endif
			{
				memcpy(thiz->last_text, thiz->text, sizeof(char) * (strlen(thiz->text) + 1));
			}
		}
	}
}

static void TextLabel_refresh (TextLabel * obj)
{
	if (obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;

		TFTGraphics * canvas = thiz->canvas;

		if (canvas != NULL)
		{
#ifdef _DYNAMIC_MALLOC_
			if (thiz->last_text != NULL && thiz->text != NULL)
#endif
			if (strlen(thiz->text) < strlen(thiz->last_text))
			{
				canvas->drawString(thiz->x_pos,
						   thiz->y_pos,
						   thiz->last_text,
						   thiz->font_size,
						   thiz->background_color,
						   thiz->background_color);
#ifdef _DYNAMIC_MALLOC_
				free(thiz->last_text);
				thiz->last_text = NULL;
#endif
			}
#ifdef _DYNAMIC_MALLOC_
			if (thiz->text != NULL)
#endif
			{
				canvas->drawString(thiz->x_pos,
						   thiz->y_pos,
						   thiz->text,
						   thiz->font_size,
						   thiz->text_color,
						   thiz->background_color);
#ifdef _DYNAMIC_MALLOC_
				thiz->last_text = malloc(sizeof(char) * (strlen(thiz->text) + 1));
				if (thiz->last_text != NULL)
#endif
				{
					memcpy(thiz->last_text, thiz->text, sizeof(char) * (strlen(thiz->text) + 1));
				}
			}
		}
	}
}

static void TextLabel_clear (TextLabel * obj)
{
	if (obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;
#ifdef _DYNAMIC_MALLOC_
		if (thiz->text != NULL)
		{
			free(thiz->text);
			thiz->text = NULL;
		}
#else
		memset(thiz->text, 0x00, sizeof(thiz->text));
#endif
		thiz->number = 0;

		TextLabel_refresh(obj);
	}
}

static void TextLabel_set_x (TextLabel * obj, int32_t x_pos)
{
	if (obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;
		thiz->x_pos = x_pos;
	}
}

static void TextLabel_set_y (TextLabel * obj, int32_t y_pos)
{
	if (obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;
		thiz->y_pos = y_pos;
	}
}

static void TextLabel_set_width (TextLabel * obj, int32_t width)
{
	if (obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;
		thiz->width = width;
	}
}

static void TextLabel_set_height (TextLabel * obj, int32_t height)
{
	if (obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;
		thiz->height = height;
	}
}

static void TextLabel_set_text (TextLabel * obj, char * str)
{
	if (obj != NULL && str != NULL && strlen(str) > 0)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;

#ifdef _DYNAMIC_MALLOC_
		if ((thiz->text == NULL) || ((strcmp(str, thiz->text) != 0)))
		{
			char * text = malloc(sizeof(char) * (strlen(str) + 1));

			if (text != NULL)
			{
				memcpy(text, str, sizeof(char) * (strlen(str) + 1));

				if (thiz->text != NULL)
				{
					free(thiz->text);
				}

				thiz->text = text;

				TextLabel_refresh(obj);
			}
		}
#else
		if (strcmp(str, thiz->text) != 0)
		{
			memcpy(thiz->text, str, sizeof(char) * (strlen(str) + 1));
			TextLabel_refresh(obj);
		}
#endif
	}
}

static void TextLabel_set_number (TextLabel * obj, int32_t number)
{
	if (obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;

		if ((thiz->type == NUMBER) && (thiz->number != number))
		{
			char text[10];
			thiz->number = number;

			sprintf(text, "%ld", number);

			TextLabel_set_text(obj, text);
		}
	}
}

static void TextLabel_set_label_type (TextLabel * obj, TextLabel_Type type)
{
	if (obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;
		thiz->type = type;
	}
}

static void TextLabel_set_font_size (TextLabel * obj, uint8_t font_size)
{
	if (obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;
		thiz->font_size = font_size;
	}
}

static void TextLabel_set_text_color (TextLabel * obj, int32_t text_color)
{
	if (obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;
		if (thiz->text_color != text_color)
		{
			thiz->text_color = text_color;
			TextLabel_refresh(obj);
		}
	}
}

static void TextLabel_set_background_color (TextLabel * obj, int32_t background_color)
{
	if (obj != NULL)
	{
		TextLabel_private * thiz = (TextLabel_private *) obj;
		if (thiz->background_color != background_color)
		{
			thiz->background_color = background_color;
			TextLabel_refresh(obj);
		}
	}
}

