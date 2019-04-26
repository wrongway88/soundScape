#include "Triangle.h"

Triangle::Triangle():
	m_vertex0(0.0f, 0.0f, 0.0f),
	m_vertex1(0.0f, 0.0f, 0.0f),
	m_vertex2(0.0f, 0.0f, 0.0f)
{
}

Triangle::Triangle(const ci::vec3& v0, const ci::vec3& v1, const ci::vec3& v2):
	m_vertex0(v0),
	m_vertex1(v1),
	m_vertex2(v2)
{
}

Triangle::~Triangle()
{
}

ci::vec3 Triangle::getVertex0()const
{
	return m_vertex0;
}

ci::vec3 Triangle::getVertex1()const
{
	return m_vertex1;
}

ci::vec3 Triangle::getVertex2()const
{
	return m_vertex2;
}