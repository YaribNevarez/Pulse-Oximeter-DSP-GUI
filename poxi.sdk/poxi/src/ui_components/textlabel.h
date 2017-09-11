/*
 * textlabel.h
 *
 *  Created on: 4 de ene. de 2017
 *      Author: Yarib Nevárez
 */

#ifndef TEXTLABEL_H_
#define TEXTLABEL_H_

#include "xil_types.h"
#include "widget.h"

typedef struct TextLabel_public TextLabel;

typedef enum
{
	TEXT,
	NUMBER
} TextLabel_Type;

#define TEXTLABEL_VIRTUALTABLE_MEMBERS \
		WIDGET_VIRTUALTABLE_MEMBERS \
        void 		(* set_x)     (TextLabel * obj, int32_t x_pos); \
        void 		(* set_y)     (TextLabel * obj, int32_t y_pos); \
		void 		(* set_width) (TextLabel * obj, int32_t width); \
		void 		(* set_height)(TextLabel * obj, int32_t height); \
        void        (* set_text)  (TextLabel * obj, char * str); \
        void 		(* set_number)(TextLabel * obj, int32_t number); \
        void 		(* set_label_type)      (TextLabel * obj, TextLabel_Type type); \
        void 		(* set_font_size)       (TextLabel * obj, uint8_t font_size); \
        void 		(* set_text_color)      (TextLabel * obj, int32_t text_color); \
        void 		(* set_background_color)(TextLabel * obj, int32_t background_color);

struct TextLabel_public
{
    TEXTLABEL_VIRTUALTABLE_MEMBERS
};

TextLabel * TextLabel_new (uint16_t x, uint16_t y, uint16_t width, uint16_t height, char * str, uint32_t text_color, uint32_t background_color);


#endif /* TEXTLABEL_H_ */
