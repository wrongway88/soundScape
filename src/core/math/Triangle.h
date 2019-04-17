#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "cinder/Vector.h"

class Triangle
{
public:
	Triangle();
	Triangle(const ci::Vec3f& a, const ci::Vec3f& b, const ci::Vec3f& c);

	ci::Vec3f GetNormal() const; // upper case to match original coding convention

	float getShortestDistance(const ci::Vec3f& point) const;
	ci::Vec3f getClosestPointOnTriangle(const ci::Vec3f& point) const;
	float getAltitudeAtPoint(const ci::Vec3f& point) const;

	bool checkAbove(const ci::Vec3f& point) const;

	// should be much faster to do this test before testing actual distance/collision
	bool testCircumsphere(const ci::Vec3f& point) const;
	bool testCircumsphere(const ci::Vec3f& point, float radius) const; // to test spheres
	bool testCircumsphere2D(const ci::Vec3f& point) const;

	ci::Vec3f getVertex(const unsigned int index) const;

	ci::Vec3f getCenter() const;

	static float getAreaYProjected(const ci::Vec3f& pointA, const ci::Vec3f& pointB, const ci::Vec3f& pointC);
	static float getArea3d(const ci::Vec3f& pointA, const ci::Vec3f& pointB, const ci::Vec3f& pointC);

	float getMaxY() const;

private:
	ci::Vec3f getPlaneProjectedPoint(const ci::Vec3f& point) const;
	ci::Vec3f getLineProjectedPoint(const ci::Vec3f&  point, const ci::Vec3f& edgeStart, const ci::Vec3f& edgeEnd) const;
	float getDistancePointToEdge(const ci::Vec3f&  point, const ci::Vec3f& edgeStart, const ci::Vec3f& edgeEnd) const;

	bool checkAreasEqual(const std::vector<float>& areas0, const std::vector<float>& areas1) const;

	void calculateCircumsphere();

	ci::Vec3f m_vertices[3];
	ci::Vec3f m_normal;

	ci::Vec3f m_circumsphereCenter;
	float m_radius;
	float m_maxY;
};

#endif // TRIANGLE_H