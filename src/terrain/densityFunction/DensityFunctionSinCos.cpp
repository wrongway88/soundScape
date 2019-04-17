#include "DensityFunctionSinCos.h"

DensityFunctionSinCos::DensityFunctionSinCos()
{
}

DensityFunctionSinCos::~DensityFunctionSinCos()
{
}

float DensityFunctionSinCos::getValue(ci::Vec3f& position) const
{
	float density = -position.y;
	density += std::sin(position.x);
	density += std::cos(position.z);

	return density;
}