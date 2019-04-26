#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "cinder/Vector.h"

class Triangle
{
public:
	Triangle();
	Triangle(const ci::vec3& v0, const ci::vec3& v1, const ci::vec3& v2);
	~Triangle();

	ci::vec3 getVertex0()const;
	ci::vec3 getVertex1()const;
	ci::vec3 getVertex2()const;

private:
	ci::vec3 m_vertex0;
	ci::vec3 m_vertex1;
	ci::vec3 m_vertex2;
};

#endif