/*
 * filter.h
 *
 *  Created on: 23 de ene. de 2017
 *      Author: Yarib Nevárez
 */

#ifndef SRC_DSP_FILTER_H_
#define SRC_DSP_FILTER_H_

typedef struct
{
	const unsigned char order;  // Filter order
	const double *      a_coef; // Feedback filter coefficients
	const double *      b_coef; // Feedforward filter coefficients
} FilterParameters;

typedef struct Filter_public Filter;

struct Filter_public
{
	void   (* reset)  (Filter * obj);
	double (* process)(Filter * obj, double u);
	void   (* delete) (Filter ** obj);
	double (* output) (Filter * obj);
	const FilterParameters * (* access_parameters) (Filter * obj);
};

Filter * Filter_new(const FilterParameters * parameters);

#endif /* SRC_DSP_FILTER_H_ */
