#ifndef DENSITY_FUNCTION_SIN_COS
#define DENSITY_FUNCTION_SIN_COS

#include "IDensityFunction.h"

/**
 *@brief Simple density function for demonstration
 * Terrain from this function will be something like an egg carton
 */
class DensityFunctionSinCos : public IDensityFunction
{
public:
	DensityFunctionSinCos();
	~DensityFunctionSinCos();

	float getValue(const ci::vec3& position) const;
};

#endif