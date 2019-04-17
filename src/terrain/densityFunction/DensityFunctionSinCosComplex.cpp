#include "DensityFunctionSinCosComplex.h"

DensityFunctionSinCosComplex::DensityFunctionSinCosComplex()
{
}

DensityFunctionSinCosComplex::~DensityFunctionSinCosComplex()
{
}

float DensityFunctionSinCosComplex::getValue(ci::Vec3f& position) const
{
	float density = -position.y;
	density += std::sin(position.x);
	density += std::cos(position.z);

	density += std::sin(position.z * 0.5f);
	density += std::cos(position.x * 0.5f);

	density -= std::sin(position.x * 0.02f) * 2.0f;
	density -= std::cos(position.z * 0.02f) * 2.0f;

	density -= std::sin(position.z * 0.1f) * 10.0f;
	density -= std::cos(position.x * 0.1f) * 10.0f;

	return density;
}