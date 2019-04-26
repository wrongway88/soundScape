#ifndef DENSITY_FUNCTION_VOLUME_MAP_H
#define DENSITY_FUNCTION_VOLUME_MAP_H

#include "IDensityFunction.h"
#include "core/utility/logging/logging.h"

#include "cinder/app/App.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

class DensityFunctionVolumeMap : public IDensityFunction
{
public:
	DensityFunctionVolumeMap();
	~DensityFunctionVolumeMap();

	float getValue(const ci::vec3& position) const;

	void setTerrainSize(const float terrainSize);
	/**
	 *@note The first map will automatically be loaded a second time as last map
	 */
	void loadMaps(std::vector<std::string>& maps);

private:
	float getMapValue(const ci::vec2& position, const ci::Surface32f& map) const;

	ci::vec2 m_terrainSize;
	std::vector<ci::Surface32f> m_maps;
};

#endif