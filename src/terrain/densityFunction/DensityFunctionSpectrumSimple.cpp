#include "DensityFunctionSpectrumSimple.h"

DensityFunctionSpectrumSimple::DensityFunctionSpectrumSimple()
	: m_spectrum()
	, m_terrainSize()
	, m_altitudeScale()
{
}

DensityFunctionSpectrumSimple::~DensityFunctionSpectrumSimple()
{
}

void DensityFunctionSpectrumSimple::setSpectrum(const std::vector<std::vector<float>>& spectrum)
{
	m_spectrum = spectrum;
}

void DensityFunctionSpectrumSimple::setTerrainSize(const float terrainSize)
{
	m_terrainSize.x = terrainSize;
	m_terrainSize.y = terrainSize;
}

void DensityFunctionSpectrumSimple::setAltitudeScale(const float altitudeScale)
{
	m_altitudeScale = altitudeScale;
}

float DensityFunctionSpectrumSimple::getValue(const ci::vec3& position) const
{
	if (m_spectrum.size() <= 0
		|| m_spectrum[0].size() <= 0)
	{
		return -position.y;
	}

	ci::vec2 spectrumSize(m_spectrum.size(), m_spectrum[0].size());

	ci::vec2 horizontalPos;
	horizontalPos.x = position.x;
	horizontalPos.y = position.z;

	horizontalPos += m_terrainSize * 0.5f;

	horizontalPos /= m_terrainSize;

	horizontalPos *= spectrumSize;

	if (horizontalPos.x < 0.0f
		|| horizontalPos.y < 0.0f
		|| horizontalPos.x > m_spectrum.size()
		|| horizontalPos.y > m_spectrum[0].size())
	{
		return -position.y;
	}

	return -position.y + (m_spectrum[horizontalPos.x][horizontalPos.y] * m_altitudeScale);
}
