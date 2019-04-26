#include "Terrain.h"

#include "core/utility/logging/logging.h"

Terrain::Terrain(std::vector<ci::vec3>& vertices, std::vector<unsigned int>& indices, std::vector<ci::vec3>& normals):
	m_vertices(vertices),
	m_indices(indices),
	m_normals(normals),
	m_cubesPerDimension(0)
{
	for(unsigned int i = 0; i < m_vertices.size(); i++)
	{
		m_textureCoordinates.push_back(ci::vec2(0.0f, 0.0f));
	}
}

Terrain::~Terrain()
{
}

std::vector<ci::vec3> Terrain::getVertices() const
{
	return m_vertices;
}

std::vector<unsigned int> Terrain::getIndices() const
{
	return m_indices;
}

std::vector<ci::vec3> Terrain::getNormals() const
{
	return m_normals;
}

std::vector<ci::vec2> Terrain::getTextureCoordinates() const
{
	return m_textureCoordinates;
}

ci::vec3 Terrain::getVertex(const unsigned int idx) const
{
	ci::vec3 result(0.0f, 0.0f, 0.0f);

	if(idx >= m_vertices.size())
	{
		LOG_ERROR("Index out of range");
		return result;
	}

	result = m_vertices[idx];

	return result;
}

unsigned int Terrain::getIndex(const unsigned int idx) const
{
	unsigned int result = 0;

	if(idx >= m_indices.size())
	{
		LOG_ERROR("Index out of range");
		return result;
	}

	result = m_indices[idx];

	return result;
}

ci::vec3 Terrain::getNormal(const unsigned int idx) const
{
	ci::vec3 result(0.0f, 0.0f, 0.0f);

	if(idx >= m_normals.size())
	{
		LOG_ERROR("Index out of range");
		return result;
	}

	result = m_normals[idx];

	return result;
}

ci::vec2 Terrain::getTextureCoordinate(const unsigned int idx) const
{
	ci::vec2 result(0.0f, 0.0f);

	if(idx >= m_textureCoordinates.size())
	{
		LOG_ERROR("Index out of range");
		return result;
	}

	result = m_textureCoordinates[idx];

	return result;
}

int Terrain::getCubesPerDimension() const
{
	return m_cubesPerDimension;
}

void Terrain::setCubesPerDimension(const int cubesPerDimension)
{
	m_cubesPerDimension = cubesPerDimension;
}
