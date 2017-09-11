/*
 * MATLAB.C
 *
 *  Created on: 26 de ene. de 2017
 *      Author: Yarib Nevárez
 */
#include "filter.h"
#include "DSP.H"

double high_pass_filter_wrapper(double u1)
{
	static Filter * filter = (Filter *)0;

	if (filter == 0)
	{
		filter = Filter_new(&high_pass_filter_parameters);
	}

	return filter->process(filter, u1);
}

double low_pass_filter_wrapper(double u1)
{
	static Filter * filter = (Filter *)0;

	if (filter == 0)
	{
		filter = Filter_new(&low_pass_filter_parameters);
	}

	return filter->process(filter, u1);
}
