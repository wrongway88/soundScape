#ifndef CUBE_H
#define CUBE_H

#include "core/utility/logging/logging.h"

#include "cinder/Vector.h"

#include <sstream>

struct EdgeIndex
{
	EdgeIndex()
	{
		m_v0 = -1;
		m_v1 = -1;
	}

	int m_v0;
	int m_v1;
};

struct Edge
{
	Edge()
	{
		m_v0 = ci::vec3(0.0f, 0.0f, 0.0f);
		m_v1 = ci::vec3(0.0f, 0.0f, 0.0f);
		m_intersection = ci::vec3(0.0f, 0.0f, 0.0f);
		m_normal = ci::vec3(0.0f, 0.0f, 0.0f);
		m_timesVisited = 0;
	}

	ci::vec3 m_v0;
	ci::vec3 m_v1;

	ci::vec3 m_intersection;
	ci::vec3 m_normal;

	int m_timesVisited;
};

class Cube
{
public:
	Cube(const ci::vec3& center, const float size);
	~Cube();

	ci::vec3 getVertex(const unsigned int index);
	ci::vec3 getCenter();
	float getSize();

	std::vector<unsigned int> getFaceIndices(unsigned int faceIndex);
	std::vector<ci::vec2> getFaceVertices(unsigned int faceIndex);

	static EdgeIndex getEdgeIndices(const unsigned int edgeIndex);

private:
	void setupVertices();

	ci::vec3 m_center;
	ci::vec3 m_vertices[8];

	float m_size;
	float m_halfSize;
};

#endif