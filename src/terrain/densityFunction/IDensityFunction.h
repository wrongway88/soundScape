#ifndef I_DENSITY_FUNCTION
#define I_DENSITY_FUNCTION

#include "cinder/Vector.h"

class IDensityFunction
{
public:
	IDensityFunction();
	virtual ~IDensityFunction() = 0;

	virtual float getValue(ci::Vec3f& position) const = 0;
};

#endif