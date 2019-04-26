#ifndef DENSITY_FUNCTION_SPECTRUM_SIMPLE_H
#define DENSITY_FUNCTION_SPECTRUM_SIMPLE_H

#include <vector>

#include "IDensityFunction.h"

class DensityFunctionSpectrumSimple : public IDensityFunction
{
public:
	DensityFunctionSpectrumSimple();
	~DensityFunctionSpectrumSimple();

	void setSpectrum(const std::vector<std::vector<float>>& spectrum);

	void setTerrainSize(const float terrainSize);

	void setAltitudeScale(const float altitudeScale);

	float getValue(const ci::vec3& position) const;

private:
	std::vector<std::vector<float>> m_spectrum;

	ci::vec2 m_terrainSize;
	float m_altitudeScale;
};

#endif // DENSITY_FUNCTION_SPECTRUM_SIMPLE_H
