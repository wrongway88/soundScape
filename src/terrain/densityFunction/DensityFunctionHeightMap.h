#ifndef DENSITY_FUNCTION_HEIGHT_MAP
#define DENSITY_FUNCTION_HEIGHT_MAP

#include "IDensityFunction.h"

#include "cinder/app/App.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Vector.h"

/**
 *@brief Simple density function for demonstration
 * Terrain from this function will be something like an egg carton
 */
class DensityFunctionHeightMap : public IDensityFunction
{
public:
	DensityFunctionHeightMap();
	~DensityFunctionHeightMap();

	float getValue(const ci::vec3& position) const;

	void setTerrainSize(const float terrainSize);
	void loadHeightMap(const std::string& file);

	float getAltitudeScale() const;
	void setAltitudeScale(const float altitudeScale);

private:
	ci::vec2 m_terrainSize;
	ci::Surface32f m_heightMap;

	float m_altitudeScale;
};

#endif