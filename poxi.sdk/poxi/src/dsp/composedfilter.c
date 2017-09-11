/*
 * composedfilter.c
 *
 *  Created on: 7 de feb. de 2017
 *      Author: Yarib Nevárez
 */

#include <stdlib.h>
#include <string.h>
#include "filter.h"
#include <stdarg.h>
#include "composedfilter.h"

typedef struct // class
{
	// public:
	void   (* reset)  (ComposedFilter * obj);
	double (* process)(ComposedFilter * obj, double u);
	void   (* delete)         (ComposedFilter ** obj);
	double (* processSignal)  (ComposedFilter * obj, double * input, double * output, unsigned int length);
	void   (* setSampleTime)  (ComposedFilter * obj, double time);
	void   (* setupStatistics)(ComposedFilter * obj, int flags);
	void   (* resetStatistics)(ComposedFilter * obj);
	FilterStatistics (* getStatistics)(ComposedFilter * obj);
	// private:
	Filter **        filterArray;
	int              filters;
	double           sampleTime;
	DiscretePoint    lastPoint;
	int              statisticsFlags;
	FilterStatistics statisticsData;
} ComposedFilter_private;

static void   ComposedFilter_reset  (ComposedFilter * obj);
static double ComposedFilter_process(ComposedFilter * obj, double u);
static void   ComposedFilter_delete         (ComposedFilter ** obj);
static double ComposedFilter_processSignal  (ComposedFilter * obj, double * input, double * output, unsigned int length);
static void   ComposedFilter_setSampleTime  (ComposedFilter * obj, double time);
static void   ComposedFilter_setupStatistics(ComposedFilter * obj, int flags);
static void   ComposedFilter_resetStatistics(ComposedFilter * obj);
static FilterStatistics ComposedFilter_getStatistics(ComposedFilter * obj);

#define DEFAULT_SAMPLE_TIME 0.001

static void ComposedFilter_init_virtual_table(ComposedFilter_private * thiz)
{
	if (thiz != NULL)
	{
		thiz->reset           = ComposedFilter_reset;
		thiz->process         = ComposedFilter_process;
		thiz->delete          = ComposedFilter_delete;
		thiz->processSignal   = ComposedFilter_processSignal;
		thiz->setSampleTime   = ComposedFilter_setSampleTime;
		thiz->setupStatistics = ComposedFilter_setupStatistics;
		thiz->resetStatistics = ComposedFilter_resetStatistics;
		thiz->getStatistics   = ComposedFilter_getStatistics;
	}
}

ComposedFilter * ComposedFilter_new (int number_of_filters, ...)
{
	ComposedFilter_private * thiz = NULL;

	if (0 < number_of_filters)
	{
		int i;
		int valid = 0;

		va_list par;

		va_start(par, number_of_filters);

		for (i = 0; i < number_of_filters; i ++)
		{
			valid += va_arg(par, Filter *) != NULL;
		}

		if (valid == number_of_filters)
		{
			thiz = malloc(sizeof(ComposedFilter_private));
			if (thiz != NULL)
			{
				memset(thiz, 0x00, sizeof(ComposedFilter_private));
				ComposedFilter_init_virtual_table(thiz);

				thiz->filterArray = (Filter**)malloc(sizeof(Filter*) * number_of_filters);

				if (thiz->filterArray != NULL)
				{
					va_start(par, number_of_filters);
					for (i = 0; i < number_of_filters; i ++)
					{
						thiz->filterArray[i] = va_arg(par, Filter *);
					}
					thiz->filters = number_of_filters;

					thiz->sampleTime = DEFAULT_SAMPLE_TIME;
				}
				else
				{
					free(thiz);
					thiz = NULL;
				}
			}
		}
		va_end(par);
	}
	return (ComposedFilter *) thiz;
}

static void   ComposedFilter_reset  (ComposedFilter * obj)
{
	if (obj != NULL)
	{
		ComposedFilter_private * thiz = (ComposedFilter_private*) obj;
		int i;

		for (i = 0; i < thiz->filters; i ++)
		{
			if (thiz->filterArray[i] != NULL)
			{
				thiz->filterArray[i]->reset(thiz->filterArray[i]);
			}
		}

		ComposedFilter_resetStatistics(obj);
	}
}

static void ComposedFilter_processStatistics(ComposedFilter_private * thiz, double u, double y)
{
	if (thiz != NULL && thiz->statisticsFlags)
	{
		int flags = thiz->statisticsFlags;

		if (flags & MAX_OUTPUT)
		{
			if (thiz->statisticsData.maxOutput.magnitude < y)
			{
				thiz->statisticsData.maxOutput = thiz->statisticsData.currentOutput;
			}
		}

		if (flags & MIN_OUTPUT)
		{
			if (y < thiz->statisticsData.minOutput.magnitude)
			{
				thiz->statisticsData.minOutput = thiz->statisticsData.currentOutput;
			}
		}

		if (flags & MAX_INPUT)
		{
			if (thiz->statisticsData.maxInput.magnitude < u)
			{
				thiz->statisticsData.maxInput = thiz->statisticsData.lastInput;
			}
		}

		if (flags & MIN_INPUT)
		{
			if (u < thiz->statisticsData.minInput.magnitude)
			{
				thiz->statisticsData.minInput = thiz->statisticsData.lastInput;
			}
		}

		if (flags & FUNDAMENTAL_FREC)
		{
			if (   ((double)0 < thiz->lastPoint.magnitude && thiz->statisticsData.currentOutput.magnitude < (double)0)
			    || ((double)0 > thiz->lastPoint.magnitude && thiz->statisticsData.currentOutput.magnitude > (double)0))
			{
				if (   thiz->statisticsData.secLastZeroCross.time != 0
				    && thiz->statisticsData.lastZeroCross.time != 0)
				{
					thiz->statisticsData.fundamentalFrec =
					(double)1 / (thiz->statisticsData.currentOutput.time - thiz->statisticsData.secLastZeroCross.time);
				}
				thiz->statisticsData.secLastZeroCross = thiz->statisticsData.lastZeroCross;
				thiz->statisticsData.lastZeroCross = thiz->statisticsData.currentOutput;
			}

			thiz->lastPoint = thiz->statisticsData.currentOutput;
		}
	}
}

static double ComposedFilter_process(ComposedFilter * obj, double u)
{
	double y = 0.0;

	if (obj != NULL)
	{
		ComposedFilter_private * thiz = (ComposedFilter_private*) obj;
		int i;

		y = u;

		for (i = 0; i < thiz->filters; i ++)
		{
			if (thiz->filterArray[i] != NULL)
			{
				y = thiz->filterArray[i]->process(thiz->filterArray[i], y);
			}
		}

		thiz->statisticsData.currentOutput.magnitude = y;
		thiz->statisticsData.currentOutput.time += thiz->sampleTime;
		thiz->statisticsData.lastInput.magnitude = u;
		thiz->statisticsData.lastInput.time += thiz->sampleTime;;
		if (thiz->statisticsFlags)
		{
			ComposedFilter_processStatistics(thiz, u, y);
		}
	}
	return y;
}

static void   ComposedFilter_delete         (ComposedFilter ** obj)
{
	if ((obj != NULL) && (*obj != NULL))
	{
		ComposedFilter_private * thiz = (ComposedFilter_private*) *obj;
		int i;

		for (i = 0; i < thiz->filters; i ++)
		{
			if (thiz->filterArray[i] != NULL)
			{
				thiz->filterArray[i]->delete(&thiz->filterArray[i]);
			}
		}

		free(thiz->filterArray);
		free(thiz);
		*obj = NULL;
	}
}

static double ComposedFilter_processSignal  (ComposedFilter * obj, double * input, double * output, unsigned int length)
{
	double y = 0;

	if (obj != NULL && input != NULL && output != NULL)
	{
		unsigned int i;

		for (i = 0; i < length; i ++)
		{
			output[i] = ComposedFilter_process(obj, input[i]);
		}
		y = ((ComposedFilter_private*) obj)->statisticsData.currentOutput.magnitude;
	}
	return y;
}

static void   ComposedFilter_setSampleTime  (ComposedFilter * obj, double time)
{
	if (obj != NULL)
	{
		((ComposedFilter_private *) obj)->sampleTime = time;
	}
}

static void   ComposedFilter_setupStatistics(ComposedFilter * obj, int flags)
{
	if (obj != NULL)
	{
		((ComposedFilter_private *) obj)->statisticsFlags = flags;
	}
}

static void   ComposedFilter_resetStatistics(ComposedFilter * obj)
{
	if (obj != NULL)
	{
		ComposedFilter_private * thiz = (ComposedFilter_private*) obj;
		DiscretePoint currentOutput = thiz->statisticsData.currentOutput;
		DiscretePoint lastInput = thiz->statisticsData.lastInput;

		FilterStatistics * statisticsData = &thiz->statisticsData;

		statisticsData->maxOutput = currentOutput;
		statisticsData->minOutput = currentOutput;
		statisticsData->minInput = lastInput;
		statisticsData->maxInput = lastInput;
	}
}

static FilterStatistics ComposedFilter_getStatistics(ComposedFilter * obj)
{
	FilterStatistics statistics;
	if (obj != NULL)
	{
		statistics = ((ComposedFilter_private *) obj)->statisticsData;
	}
	return statistics;
}
