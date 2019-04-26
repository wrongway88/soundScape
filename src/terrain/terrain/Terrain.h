#ifndef TERRAIN_H
#define TERRAIN_H

#include "cinder/Vector.h"

#include <vector>

class Terrain
{
public:
	Terrain(std::vector<ci::vec3>& vertices, std::vector<unsigned int>& indices, std::vector<ci::vec3>& normals);
	~Terrain();

	std::vector<ci::vec3> getVertices() const;
	std::vector<unsigned int> getIndices() const;
	std::vector<ci::vec3> getNormals() const;
	std::vector<ci::vec2> getTextureCoordinates() const;

	ci::vec3 getVertex(const unsigned int idx) const;
	unsigned int getIndex(const unsigned int idx) const;
	ci::vec3 getNormal(const unsigned int idx) const;
	ci::vec2 getTextureCoordinate(const unsigned int idx) const;

	int getCubesPerDimension() const;
	void setCubesPerDimension(const int cubesPerDimension);

private:
	std::vector<ci::vec3> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<ci::vec3> m_normals;
	std::vector<ci::vec2> m_textureCoordinates;

	int m_cubesPerDimension;
};

#endif