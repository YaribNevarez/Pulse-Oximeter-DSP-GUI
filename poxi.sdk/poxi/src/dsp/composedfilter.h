/*
 * composedfilter.h
 *
 *  Created on: 7 de feb. de 2017
 *      Author: Yarib Nevárez
 */

#ifndef SRC_DSP_COMPOSEDFILTER_H_
#define SRC_DSP_COMPOSEDFILTER_H_

#include "filter.h"

typedef struct
{
	double magnitude;
	double time;
} DiscretePoint;

typedef struct
{
	DiscretePoint maxOutput;
	DiscretePoint minOutput;
	DiscretePoint maxInput;
	DiscretePoint minInput;
	DiscretePoint currentOutput;
	DiscretePoint lastInput;
	DiscretePoint lastZeroCross;
	DiscretePoint secLastZeroCross;
	double        fundamentalFrec;
} FilterStatistics;

typedef enum
{
	STATISTICS_OFF   = 0x00,
	MAX_OUTPUT       = 0x01,
	MIN_OUTPUT       = 0x02,
	MAX_INPUT        = 0x04,
	MIN_INPUT        = 0x08,
	FUNDAMENTAL_FREC = 0x10
} FilterStatisticsFlags;

typedef struct ComposedFilter_public ComposedFilter;

struct ComposedFilter_public // class
{
	void   (* reset)  (ComposedFilter * obj);
	double (* process)(ComposedFilter * obj, double u);
	void   (* delete)         (ComposedFilter ** obj);
	double (* processSignal)  (ComposedFilter * obj, double * input, double * output, unsigned int length);
	void   (* setSampleTime)  (ComposedFilter * obj, double time);
	void   (* setupStatistics)(ComposedFilter * obj, int flags);
	void   (* resetStatistics)(ComposedFilter * obj);
	FilterStatistics (* getStatistics)(ComposedFilter * obj);
};

ComposedFilter * ComposedFilter_new (int number_of_filters, ...);

#endif /* SRC_DSP_COMPOSEDFILTER_H_ */
