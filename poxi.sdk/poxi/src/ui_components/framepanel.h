/*
 * framepanel.h
 *
 *  Created on: 10 de ene. de 2017
 *      Author: Yarib
 */

#ifndef SRC_UI_COMPONENTS_FRAMEPANEL_H_
#define SRC_UI_COMPONENTS_FRAMEPANEL_H_

#include "xil_types.h"
#include "widget.h"

#define MAX_HEIGHT  320
#define MAX_WIDTH   240

typedef struct FramePanel_public FramePanel;

#define FRAMEPANEL_VIRTUALTABLE_MEMBERS \
        WIDGET_VIRTUALTABLE_MEMBERS \
        void (* set_x)     (FramePanel * obj, int32_t x_pos); \
        void (* set_y)     (FramePanel * obj, int32_t y_pos); \
        void (* set_width) (FramePanel * obj, int32_t width); \
        void (* set_height)(FramePanel * obj, int32_t height); \
        void (* set_lineColor)      (FramePanel * obj, int32_t text_color); \
        void (* set_backgroundColor)(FramePanel * obj, int32_t background_color);\
        void (* give_widget)        (FramePanel * obj, Widget * child);

struct FramePanel_public
{
	FRAMEPANEL_VIRTUALTABLE_MEMBERS
};

FramePanel * FramePanel_new (uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t line_color, uint32_t background_color);


#endif /* SRC_UI_COMPONENTS_FRAMEPANEL_H_ */
