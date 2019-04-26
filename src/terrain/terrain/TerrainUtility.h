#ifndef TERRAIN_UTILITY_H
#define TERRAIN_UTILITY_H

#include "cinder/Vector.h"
#include "../common/Cube.h"

struct VertexOrder
{
	VertexOrder()
	{
		for(unsigned int i = 0; i < 3; i++)
		{
			m_order[i] = -1;
		}
	}

	VertexOrder(int first, int second, int third)
	{
		m_order[0] = first;
		m_order[1] = second;
		m_order[2] = third;
	}

	int m_order[3];
};

struct VertexOrderCase
{
	VertexOrder m_orders[5];

	VertexOrderCase(VertexOrder a, VertexOrder b, VertexOrder c, VertexOrder d, VertexOrder e)
	{
		m_orders[0] = a;
		m_orders[1] = b;
		m_orders[2] = c;
		m_orders[3] = d;
		m_orders[4] = e;
	}
};

/**
 *@brief Stores density values of the corners (vertices) of a cube
 *@note value order is supposed to be the same order as the vertices in the class Cube
 */
struct CubeCornerValues
{
public:
	float m_value0;
	float m_value1;
	float m_value2;
	float m_value3;
	float m_value4;
	float m_value5;
	float m_value6;
	float m_value7;

	CubeCornerValues():
		m_value0(0.0f),
		m_value1(0.0f),
		m_value2(0.0f),
		m_value3(0.0f),
		m_value4(0.0f),
		m_value5(0.0f),
		m_value6(0.0f),
		m_value7(0.0f)
	{}

	CubeCornerValues(float value0, float value1, float value2, float value3, float value4, float value5, float value6, float value7):
		m_value0(value0),
		m_value1(value1),
		m_value2(value2),
		m_value3(value3),
		m_value4(value4),
		m_value5(value5),
		m_value6(value6),
		m_value7(value7)
	{}
};

class TerrainUtility
{
public:
	static const int m_caseToNumPolys[256];
	static const VertexOrderCase m_edgeConnectList[256];



	static float interpolate(ci::vec2& position, ci::vec2& vertex00, ci::vec2& vertex11, float value00, float value10, float value01, float value11);
	/**
	 *@note vertex000 has to be the cubes vertex at -x, -y, -z and vertex111 the vertex at +x, +y, +z
	 */
	static float interpolate(ci::vec3& position, ci::vec3& vertex000, ci::vec3& vertex111, CubeCornerValues& cubeCornerValues);

	static ci::vec2 calculateFaceSaddlePoint(ci::vec2& vertex00, ci::vec2& vertex11, float value00, float value10, float value01, float value11);
	static std::vector<ci::vec3> calculateBodySaddlePoints(const ci::vec3& vertex000, const ci::vec3& vertex111, const CubeCornerValues& cubeCornerValues);
};

#endif