#ifndef TERRAIN_H
#define TERRAIN_H

#include "cinder/Vector.h"

#include <vector>

class Terrain
{
public:
	Terrain(std::vector<ci::Vec3f>& vertices, std::vector<unsigned int>& indices, std::vector<ci::Vec3f>& normals);
	~Terrain();

	std::vector<ci::Vec3f> getVertices() const;
	std::vector<unsigned int> getIndices() const;
	std::vector<ci::Vec3f> getNormals() const;
	std::vector<ci::Vec2f> getTextureCoordinates() const;

	ci::Vec3f getVertex(const unsigned int idx) const;
	unsigned int getIndex(const unsigned int idx) const;
	ci::Vec3f getNormal(const unsigned int idx) const;
	ci::Vec2f getTextureCoordinate(const unsigned int idx) const;

	int getCubesPerDimension() const;
	void setCubesPerDimension(const int cubesPerDimension);

private:
	std::vector<ci::Vec3f> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<ci::Vec3f> m_normals;
	std::vector<ci::Vec2f> m_textureCoordinates;

	int m_cubesPerDimension;
};

#endif