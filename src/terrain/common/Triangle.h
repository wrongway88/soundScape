#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "cinder/Vector.h"

class Triangle
{
public:
	Triangle();
	Triangle(const ci::Vec3f& v0, const ci::Vec3f& v1, const ci::Vec3f& v2);
	~Triangle();

	ci::Vec3f getVertex0()const;
	ci::Vec3f getVertex1()const;
	ci::Vec3f getVertex2()const;

private:
	ci::Vec3f m_vertex0;
	ci::Vec3f m_vertex1;
	ci::Vec3f m_vertex2;
};

#endif