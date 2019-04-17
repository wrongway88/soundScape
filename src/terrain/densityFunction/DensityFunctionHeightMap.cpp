#include "DensityFunctionHeightMap.h"

DensityFunctionHeightMap::DensityFunctionHeightMap()
	: m_terrainSize(0.0f, 0.0f)
	, m_heightMap()
	, m_altitudeScale(1.0f)
{
}

DensityFunctionHeightMap::~DensityFunctionHeightMap()
{
}

float DensityFunctionHeightMap::getValue(ci::Vec3f& position) const
{
	ci::Vec2f uv(position.x/m_terrainSize.x, position.z/m_terrainSize.y);

	float x = m_heightMap.getWidth();
	float y = m_heightMap.getHeight();

	float a = uv.x + 0.5f;
	float b = uv.y + 0.5f;

	x *= a;
	y *= b;

	int iX0 = (int)x;
	int iY0 = (int)y;
	int iX1 = (int)x + 1;
	int iY1 = (int)y + 1;

	float v0 = (m_heightMap.getPixel(ci::Vec2i(iX0, iY0)).r + m_heightMap.getPixel(ci::Vec2i(iX1, iY0)).r) * 0.5f;
	float v1 = (m_heightMap.getPixel(ci::Vec2i(iX0, iY1)).r + m_heightMap.getPixel(ci::Vec2i(iX1, iY1)).r) * 0.5f;

	float v2 = (v0 + v1) * 0.5f;

	//float value = m_heightMap.getPixel(Vec2i((int)x, (int)y)).r * 16.0f;
	float value = v2 * m_altitudeScale;

	return -position.y + value;
}

void DensityFunctionHeightMap::setTerrainSize(const float terrainSize)
{
	m_terrainSize.x = terrainSize;
	m_terrainSize.y = terrainSize;
}

void DensityFunctionHeightMap::loadHeightMap(const std::string& file)
{
	m_heightMap = ci::Surface32f(ci::loadImage(file));
}

float DensityFunctionHeightMap::getAltitudeScale() const
{
	return m_altitudeScale;
}

void DensityFunctionHeightMap::setAltitudeScale(const float altitudeScale)
{
	m_altitudeScale = altitudeScale;
}