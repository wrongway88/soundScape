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
		m_v0 = ci::Vec3f(0.0f, 0.0f, 0.0f);
		m_v1 = ci::Vec3f(0.0f, 0.0f, 0.0f);
		m_intersection = ci::Vec3f(0.0f, 0.0f, 0.0f);
		m_normal = ci::Vec3f(0.0f, 0.0f, 0.0f);
		m_timesVisited = 0;
	}

	ci::Vec3f m_v0;
	ci::Vec3f m_v1;

	ci::Vec3f m_intersection;
	ci::Vec3f m_normal;

	int m_timesVisited;
};

class Cube
{
public:
	Cube(ci::Vec3f& center, float size);
	~Cube();

	ci::Vec3f getVertex(const unsigned int index);
	ci::Vec3f getCenter();
	float getSize();

	std::vector<unsigned int> getFaceIndices(unsigned int faceIndex);
	std::vector<ci::Vec2f> getFaceVertices(unsigned int faceIndex);

	static EdgeIndex getEdgeIndices(const unsigned int edgeIndex);

private:
	void setupVertices();

	ci::Vec3f m_center;
	ci::Vec3f m_vertices[8];

	float m_size;
	float m_halfSize;
};

#endif