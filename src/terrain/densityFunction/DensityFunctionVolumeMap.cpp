#include "DensityFunctionVolumeMap.h"

DensityFunctionVolumeMap::DensityFunctionVolumeMap():
	m_terrainSize(0.0f, 0.0f)
{
}

DensityFunctionVolumeMap::~DensityFunctionVolumeMap()
{
}

float DensityFunctionVolumeMap::getValue(const ci::vec3& position) const
{
	ci::vec2 uv((position.x/m_terrainSize.x) + 0.5f, (position.z/m_terrainSize.y) + 0.5f);
	float w = (position.y/m_terrainSize.x) + 0.5f;

	float foo = 1.0f / float(m_maps.size()-1);
	float index = w / foo;

	float value = 0.0f;
	if(index > 0.0f && index < float(m_maps.size()-1))
	{
		int index0 = (int)index;
		int index1 = (int)index + 1;

		float value0 = getMapValue(uv, m_maps[index0]);
		float value1 = getMapValue(uv, m_maps[index1]);

		float factor = w - ((float)index0 * foo);
		factor /= foo;

		value = ((1.0f - factor) * value0) + (factor * value1);
	}
	else //given that map 0 and n-1 (m_maps with size n) are the same, this suffices to cover index < 0 and index >= n
	{
		value = getMapValue(uv, m_maps[0]);
	}

	return value - 0.5f;
}

void DensityFunctionVolumeMap::setTerrainSize(const float terrainSize)
{
	m_terrainSize.x = terrainSize;
	m_terrainSize.y = terrainSize;
}

void DensityFunctionVolumeMap::loadMaps(std::vector<std::string>& maps)
{
	if(maps.size() <= 0)
	{
		LOG_WARNING("No maps specified");
	}

	for(unsigned int i = 0; i < maps.size(); i++)
	{
		ci::Surface32f map(ci::loadImage(maps[i]));
		m_maps.push_back(map);
	}

	ci::Surface32f map(ci::loadImage(maps[0]));
	m_maps.push_back(map);
}

float DensityFunctionVolumeMap::getMapValue(const ci::vec2& position, const ci::Surface32f& map) const
{
	float x = (float)map.getWidth();
	float y = (float)map.getHeight();

	float a = position.x;
	float b = position.y;

	x *= a;
	y *= b;

	int iX0 = (int)x;
	int iY0 = (int)y;
	int iX1 = (int)x + 1;
	int iY1 = (int)y + 1;

	float v0 = (map.getPixel(ci::vec2(iX0, iY0)).r + map.getPixel(ci::vec2(iX1, iY0)).r) * 0.5f;
	float v1 = (map.getPixel(ci::vec2(iX0, iY1)).r + map.getPixel(ci::vec2(iX1, iY1)).r) * 0.5f;

	float v2 = (v0 + v1) * 0.5f;

	return v2;
}