#ifndef DENSITY_FUNCTION_SIN_COS_COMPLEX_H
#define DENSITY_FUNCTION_SIN_COS_COMPLEX_H

#include "IDensityFunction.h"

class DensityFunctionSinCosComplex : public IDensityFunction
{
public:
	DensityFunctionSinCosComplex();
	~DensityFunctionSinCosComplex();

	float getValue(const ci::vec3& position) const;
};

#endif