/*
 * filter.c
 *
 *  Created on: 23 de ene. de 2017
 *      Author: Yarib Nevárez
 */

#include <stdlib.h>
#include <string.h>
#include "filter.h"


typedef struct // class
{	// public:
	void   (* reset)  (Filter * obj);
	double (* process)(Filter * obj, double u);
	void   (* delete) (Filter ** obj);
	double (* output) (Filter * obj);
	const FilterParameters * (* access_parameters) (Filter * obj);
	// private:
	const FilterParameters * parameters;
	double  * states;
	double    y;
} Filter_private;

static void   Filter_reset  (Filter * obj);
static double Filter_process(Filter * obj, double u);
static double Filter_output (Filter * obj);
static const FilterParameters * Filter_access_parameters (Filter * obj);
static void   Filter_delete (Filter ** obj);


static void Filter_init_virtual_table(Filter_private * filter)
{
	if (filter != NULL)
	{
		filter->reset = Filter_reset;
		filter->process = Filter_process;
		filter->output = Filter_output;
		filter->access_parameters = Filter_access_parameters;
		filter->delete = Filter_delete;
	}
}

Filter * Filter_new(const FilterParameters * parameters)
{
	Filter_private * filter = NULL;

	if (   parameters != NULL
		&& parameters->a_coef != NULL
		&& parameters->b_coef != NULL
		&& parameters->order > 0)
	{
		filter = (Filter_private *) malloc(sizeof(Filter_private));

		if (filter != NULL)
		{
			memset(filter, 0x00, sizeof(Filter_private));

			Filter_init_virtual_table(filter);

			filter->parameters = parameters;

			Filter_reset((Filter *) filter);
		}
	}

	return (Filter *) filter;
}


static void   Filter_reset  (Filter * obj)
{
	if (obj != NULL)
	{
		Filter_private * filter = (Filter_private *) obj;

		if (filter->parameters != NULL)
		{
			if (filter->states == NULL)
			{
				filter->states = malloc(sizeof(double)*filter->parameters->order);
			}

			if (filter->states != NULL)
			{
				memset(filter->states, 0x00, sizeof(double)*filter->parameters->order);
			}
		}

		filter->y = (double)0.0;
	}
}

static double Filter_process(Filter * obj, double u)
{
	double y = (double)0.0;
	if (obj != NULL)
	{
		Filter_private * filter = (Filter_private *) obj;

		if (filter->parameters != NULL)
		{
			const double * A = filter->parameters->a_coef;
			const double * B = filter->parameters->b_coef;
			const unsigned char n = filter->parameters->order;

			double * x = filter->states;

			if ((n > 0) && (A != NULL) && (B != NULL) && (x != NULL))
			{
				unsigned char i;

				y = B[0] * u + x[0];
				for (i = 1; i < n; i ++) { x[i-1] = B[i] * u - A[i] * y + x[i];	}
				x[n-1] = B[n] * u - A[n] * y;

				filter->y = y;
			}
		}
	}
	return y;
}

static double Filter_output (Filter * obj)
{
	double y = (double)0.0;
	if (obj != NULL)
	{
		y = ((Filter_private *) obj)->y;
	}
	return y;
}

static const FilterParameters * Filter_access_parameters (Filter * obj)
{
	FilterParameters const * parameters = NULL;
	if (obj != NULL)
	{
		parameters = ((Filter_private *) obj)->parameters;
	}
	return parameters;
}

static void   Filter_delete (Filter ** obj)
{
	if (obj != NULL && *obj != NULL)
	{
		Filter_private * filter = (Filter_private *) *obj;

		if (filter->states != NULL)
		{
			free(filter->states);
		}

		free(filter);

		*obj = NULL;
	}
}
