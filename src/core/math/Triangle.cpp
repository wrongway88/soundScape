#include "triangle.h"

#include <algorithm>
#include <cfloat>

#include "../utility/logging/logging.h"

Triangle::Triangle()
{

}

Triangle::Triangle(const ci::Vec3f& a, const ci::Vec3f& b, const ci::Vec3f& c)
{
	m_vertices[0] = a;
	m_vertices[1] = b;
	m_vertices[2] = c;

	ci::Vec3f ab = m_vertices[1] - m_vertices[0];
	ci::Vec3f ac = m_vertices[2] - m_vertices[0];
	m_normal = ab.cross(ac);
	m_normal.normalize();

	calculateCircumsphere();

	m_maxY = FLT_MIN;
	for (unsigned int i = 0; i < 3; i++)
	{
		if (m_vertices[i].y > m_maxY)
		{
			m_maxY = m_vertices[i].y;
		}
	}
}

ci::Vec3f Triangle::GetNormal() const
{
	return m_normal;
}

float Triangle::getShortestDistance(const ci::Vec3f& point) const
{
	ci::Vec3f projectedPoint = getPlaneProjectedPoint(point);

	ci::Vec3f projPointToV0 = m_vertices[0] - projectedPoint;
	ci::Vec3f projPointToV1 = m_vertices[1] - projectedPoint;
	ci::Vec3f projPointToV2 = m_vertices[2] - projectedPoint;

	float cos01 = (projPointToV0.dot(projPointToV1)) / (projPointToV0.length() * projPointToV1.length()); // 0 to 1
	float cos02 = (projPointToV0.dot(projPointToV2)) / (projPointToV0.length() * projPointToV2.length()); // 0 to 2
	float cos03 = (projPointToV1.dot(projPointToV2)) / (projPointToV1.length() * projPointToV2.length()); // 1 to 2

	// distance when projected point within triangle
	float angle1 = acos(cos01);
	float angle2 = acos(cos02);
	float angle3 = acos(cos03);

	float angle = (angle1 + angle2 + angle3) * (180.0f / 3.14159f);

	if (angle >= 360.0f)
	{
		return (point - projectedPoint).length();
	}

	// distance to edges (or vertices)

	float distance01 = getDistancePointToEdge(point, m_vertices[0], m_vertices[1]);
	float distance12 = getDistancePointToEdge(point, m_vertices[1], m_vertices[2]);
	float distance20 = getDistancePointToEdge(point, m_vertices[2], m_vertices[0]);

	return std::min(distance01, std::min(distance12, distance20));
}

ci::Vec3f Triangle::getClosestPointOnTriangle(const ci::Vec3f& point) const
{
	ci::Vec3f projectedPoint = getPlaneProjectedPoint(point);

	ci::Vec3f projPointToV0 = m_vertices[0] - projectedPoint;
	ci::Vec3f projPointToV1 = m_vertices[1] - projectedPoint;
	ci::Vec3f projPointToV2 = m_vertices[2] - projectedPoint;

	float cos01 = (projPointToV0.dot(projPointToV1)) / (projPointToV0.length() * projPointToV1.length());
	float cos02 = (projPointToV0.dot(projPointToV2)) / (projPointToV0.length() * projPointToV2.length());

	// distance when projected point within triangle
	float angle = acos(cos01) + acos(cos02);
	angle *= (180.0f / 3.14159f);
	if (angle >= 180.0f)
	{
		return projectedPoint;
	}

	// distance to edges (or vertices)

	ci::Vec3f point01 = getLineProjectedPoint(point, m_vertices[0], m_vertices[1]);
	ci::Vec3f point12 = getLineProjectedPoint(point, m_vertices[1], m_vertices[2]);
	ci::Vec3f point20 = getLineProjectedPoint(point, m_vertices[2], m_vertices[0]);

	float dist01 = (point - point01).lengthSquared();
	float dist12 = (point - point12).lengthSquared();
	float dist20 = (point - point20).lengthSquared();

	if (dist01 < dist12 && dist01 < dist20)
	{
		return point01;
	}
	else if (dist12 < dist01 && dist12 < dist20)
	{
		return point12;
	}
	else
	{
		return point20;
	}

	return projectedPoint;
}

float Triangle::getAltitudeAtPoint(const ci::Vec3f& point) const
{
	ci::Vec3f point2d0 = m_vertices[0];
	ci::Vec3f point2d1 = m_vertices[1];
	ci::Vec3f point2d2 = m_vertices[2];

	ci::Vec3f point2d = point;

	float area0p1 = getAreaYProjected(point2d0, point2d1, point2d);
	float area1p2 = getAreaYProjected(point2d1, point2d2, point2d);
	float area0p2 = getAreaYProjected(point2d2, point2d0, point2d);

	float area012 = getAreaYProjected(point2d0, point2d1, point2d2);

	std::vector<float> areas0;
	std::vector<float> areas1;

	areas0.push_back(area0p1);
	areas0.push_back(area1p2);
	areas0.push_back(area0p2);

	areas1.push_back(area012);

	if (checkAreasEqual(areas0, areas1) == false)
	{
		return 0.0f;
	}

	return (area0p1 * point2d2.y + area1p2 * point2d0.y + area0p2 * point2d1.y) / area012;
}

bool Triangle::checkAbove(const ci::Vec3f& point) const
{
	ci::Vec3f point2d0 = m_vertices[0];
	ci::Vec3f point2d1 = m_vertices[1];
	ci::Vec3f point2d2 = m_vertices[2];

	ci::Vec3f point2d = point;

	std::vector<float> areas0;
	std::vector<float> areas1;

	areas0.push_back(getAreaYProjected(point2d0, point2d1, point2d));
	areas0.push_back(getAreaYProjected(point2d0, point2d2, point2d));
	areas0.push_back(getAreaYProjected(point2d1, point2d2, point2d));

	areas1.push_back(getAreaYProjected(point2d0, point2d1, point2d2));

	// float diff = std::abs(area - area012);

	return checkAreasEqual(areas0, areas1);
}

float Triangle::getAreaYProjected(const ci::Vec3f& pointA, const ci::Vec3f& pointB, const ci::Vec3f& pointC)
{
	return std::abs((pointA.x * (pointB.z - pointC.z) + pointB.x * (pointC.z - pointA.z) + pointC.x * (pointA.z - pointB.z)) * 0.5f);
}

float Triangle::getArea3d(const ci::Vec3f& pointA, const ci::Vec3f& pointB, const ci::Vec3f& pointC)
{
	ci::Vec3f ab = pointB - pointA;
	ci::Vec3f ac = pointC - pointA;

	float dot = ab.dot(ac);
	while (dot > 1.0f)
	{
		dot -= 1.0f;
	}
	while (dot < -1.0f)
	{
		dot += 1.0f;
	}

	float angle = std::acos(dot);

	return 0.5f * (ab.length() * ac.length() * std::sin(angle));
}

float Triangle::getMaxY() const
{
	return m_maxY;
}

bool Triangle::testCircumsphere(const ci::Vec3f& point) const
{
	return (m_circumsphereCenter - point).length() <= m_radius;
}

bool Triangle::testCircumsphere(const ci::Vec3f& point, float radius) const
{
	return (m_circumsphereCenter - point).length() <= (m_radius + radius);
}

bool Triangle::testCircumsphere2D(const ci::Vec3f& point) const
{
	ci::Vec2f center(m_circumsphereCenter.x, m_circumsphereCenter.z);
	ci::Vec2f point2D(point.x, point.z);

	return (center - point2D).length() <= (m_radius);
}

ci::Vec3f Triangle::getVertex(const unsigned int index) const
{
	if (index < 3)
	{
		return m_vertices[index];
	}
	else
	{
		LOG_ERROR_STREAM(<< "Index " << index << " is out of range. Max index is 2");
		return ci::Vec3f(0.0f, 0.0f, 0.0f);
	}
}

ci::Vec3f Triangle::getCenter() const
{
	return ((m_vertices[0] + m_vertices[1] + m_vertices[2]) / 3.0f);
}

ci::Vec3f Triangle::getPlaneProjectedPoint(const ci::Vec3f& point) const
{
	ci::Vec3f v0ToPoint = point - m_vertices[0];
	v0ToPoint.normalize();

	float cosAlpha = (v0ToPoint.dot(m_normal)) / (v0ToPoint.length() * m_normal.length()); //division should be superfluous? both vectors should have length 1

	ci::Vec3f pointToV0 = m_vertices[0] - point;
	float projectionDistance = pointToV0.length() * cosAlpha;

	ci::Vec3f pointToProjPoint = -projectionDistance * m_normal;
	return point + pointToProjPoint;
}

ci::Vec3f Triangle::getLineProjectedPoint(const ci::Vec3f&  point, const ci::Vec3f& edgeStart, const ci::Vec3f& edgeEnd) const
{
	ci::Vec3f pointToStart = edgeStart - point;
	ci::Vec3f startToEnd = edgeEnd - edgeStart;

	return edgeStart + ((pointToStart * startToEnd) / startToEnd.lengthSquared()) * startToEnd;
}

float Triangle::getDistancePointToEdge(const ci::Vec3f&  point, const ci::Vec3f& edgeStart, const ci::Vec3f& edgeEnd) const
{
	ci::Vec3f projectedPoint = getLineProjectedPoint(point, edgeStart, edgeEnd);

	float distStartToProj = (projectedPoint - edgeStart).length();
	float distEndToProj = (projectedPoint - edgeEnd).length();

	float distStartToEnd = (edgeEnd - edgeStart).length();

	if (distStartToEnd <= distEndToProj + distStartToProj)
	{
		float distStartToPoint = (edgeStart - point).length();
		float distEndToPoint = (edgeEnd - point).length();

		return std::min(distStartToPoint, distEndToPoint);
	}
	else
	{
		return (point - projectedPoint).length();
	}
}

bool Triangle::checkAreasEqual(const std::vector<float>& areas0, const std::vector<float>& areas1) const
{
	float area0 = 0.0f;
	float area1 = 0.0f;

	for (unsigned int i = 0; i < areas0.size(); i++)
	{
		area0 += areas0[i];
	}

	for (unsigned int i = 0; i < areas1.size(); i++)
	{
		area1 += areas1[i];
	}

	float diff = std::abs(area0 - area1);

	if (diff > std::max(area1 * 0.00001f, 0.0001f))
	{
		return false;
	}
	return true;
}

void Triangle::calculateCircumsphere()
{
	m_circumsphereCenter = (m_vertices[0] + m_vertices[1] + m_vertices[2]) / 3.0f;

	float dist0 = (m_circumsphereCenter - m_vertices[0]).length();
	float dist1 = (m_circumsphereCenter - m_vertices[1]).length();
	float dist2 = (m_circumsphereCenter - m_vertices[2]).length();

	m_radius = std::max(dist0, std::max(dist1, dist2));
}