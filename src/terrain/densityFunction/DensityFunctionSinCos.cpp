#include "DensityFunctionSinCos.h"

DensityFunctionSinCos::DensityFunctionSinCos()
{
}

DensityFunctionSinCos::~DensityFunctionSinCos()
{
}

float DensityFunctionSinCos::getValue(const ci::vec3& position) const
{
	float density = -position.y;
	density += std::sin(position.x);
	density += std::cos(position.z);

	return density;
}