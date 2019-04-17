#include "Triangle.h"

Triangle::Triangle():
	m_vertex0(0.0f, 0.0f, 0.0f),
	m_vertex1(0.0f, 0.0f, 0.0f),
	m_vertex2(0.0f, 0.0f, 0.0f)
{
}

Triangle::Triangle(const ci::Vec3f& v0, const ci::Vec3f& v1, const ci::Vec3f& v2):
	m_vertex0(v0),
	m_vertex1(v1),
	m_vertex2(v2)
{
}

Triangle::~Triangle()
{
}

ci::Vec3f Triangle::getVertex0()const
{
	return m_vertex0;
}

ci::Vec3f Triangle::getVertex1()const
{
	return m_vertex1;
}

ci::Vec3f Triangle::getVertex2()const
{
	return m_vertex2;
}