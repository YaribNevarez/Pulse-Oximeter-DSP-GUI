/*
 * widget.h
 *
 *  Created on: 9 de ene. de 2017
 *      Author: Yarib
 */

#ifndef SRC_UI_COMPONENTS_WIDGET_H_
#define SRC_UI_COMPONENTS_WIDGET_H_

#include "xil_types.h"

typedef struct Widget_public Widget;

typedef void (* WidgetDrawFunc)    (Widget * obj);
typedef void (* WidgetRefreshFunc) (Widget * obj);
typedef void (* WidgetClearFunc)   (Widget * obj);
typedef void (* WidgetDeleteFunc)  (Widget ** obj);

#define WIDGET_VIRTUALTABLE_MEMBERS \
		WidgetDrawFunc    draw; \
        WidgetRefreshFunc refresh; \
        WidgetClearFunc   clear; \
        WidgetDeleteFunc  delete; \
        Widget *          parent; \
        Widget *          prev; \
        Widget *          next; \
        Widget *          first_child;


struct Widget_public
{
	WIDGET_VIRTUALTABLE_MEMBERS
};

#endif /* SRC_UI_COMPONENTS_WIDGET_H_ */
