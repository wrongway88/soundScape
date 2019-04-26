#ifndef I_DENSITY_FUNCTION
#define I_DENSITY_FUNCTION

#include "cinder/Vector.h"

class IDensityFunction
{
public:
	IDensityFunction();
	virtual ~IDensityFunction() = 0;

	virtual float getValue(const ci::vec3& position) const = 0;
};

#endif