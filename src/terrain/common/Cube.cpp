#include "Cube.h"

Cube::Cube(const ci::vec3& center, const float size):
	m_center(center),
	m_size(size),
	m_halfSize(size * 0.5f)
{
	setupVertices();
}

Cube::~Cube()
{
}

ci::vec3 Cube::getVertex(const unsigned int index)
{
	if(index >= 8)
	{
		std::stringstream message;
		message << "Index " << index << " out of range, maximum index is 7";
		LOG_ERROR(message.str());
		return ci::vec3(0.0f, 0.0f, 0.0f);
	}

	return m_vertices[index];
}

ci::vec3 Cube::getCenter()
{
	return m_center;
}

float Cube::getSize()
{
	return m_size;
}

std::vector<unsigned int> Cube::getFaceIndices(unsigned int faceIndex)
{
	std::vector<unsigned int> result;

	if(faceIndex >= 6)
	{
		std::stringstream message;
		message << "Index " << faceIndex << " out of range, maximum index is 5";
		LOG_ERROR(message.str());
		return result;
	}

	switch(faceIndex)
	{
	case 0:
		result.push_back(0);
		result.push_back(4);
		result.push_back(5);
		result.push_back(1);
		break;
	case 1:
		result.push_back(1);
		result.push_back(5);
		result.push_back(6);
		result.push_back(2);
		break;
	case 2:
		result.push_back(2);
		result.push_back(6);
		result.push_back(7);
		result.push_back(3);
		break;
	case 3:
		result.push_back(3);
		result.push_back(7);
		result.push_back(4);
		result.push_back(0);
		break;
	case 4:
		result.push_back(0);
		result.push_back(3);
		result.push_back(2);
		result.push_back(1);
		break;
	case 5:
		result.push_back(4);
		result.push_back(7);
		result.push_back(6);
		result.push_back(5);
		break;
	default:
		return result;
	}

	return result;
}

std::vector<ci::vec2> Cube::getFaceVertices(unsigned int faceIndex)
{
	std::vector<ci::vec2> result;

	if(faceIndex >= 6)
	{
		std::stringstream message;
		message << "Index " << faceIndex << " out of range, maximum index is 5";
		LOG_ERROR(message.str());
		return result;
	}

	std::vector<unsigned int> vertexIndices = getFaceIndices(faceIndex);
	std::vector<ci::vec3> vertices;
	if(vertexIndices.size() == 4)
	{
		vertices.push_back(getVertex(vertexIndices[0]));
		vertices.push_back(getVertex(vertexIndices[1]));
		vertices.push_back(getVertex(vertexIndices[2]));
		vertices.push_back(getVertex(vertexIndices[3]));
	}
	else
	{
		LOG_ERROR("Invalid face indices");
		return result;
	}

	switch(faceIndex)
	{
	case 0:
		result.push_back(ci::vec2(vertices[0].x, vertices[0].y));
		result.push_back(ci::vec2(vertices[1].x, vertices[1].y));
		result.push_back(ci::vec2(vertices[2].x, vertices[2].y));
		result.push_back(ci::vec2(vertices[3].x, vertices[3].y));
		break;
	case 1:
		result.push_back(ci::vec2(vertices[0].x, vertices[0].z));
		result.push_back(ci::vec2(vertices[1].x, vertices[1].z));
		result.push_back(ci::vec2(vertices[2].x, vertices[2].z));
		result.push_back(ci::vec2(vertices[3].x, vertices[3].z));
		break;
	case 2:
		result.push_back(ci::vec2(vertices[0].x, vertices[0].y));
		result.push_back(ci::vec2(vertices[1].x, vertices[1].y));
		result.push_back(ci::vec2(vertices[2].x, vertices[2].y));
		result.push_back(ci::vec2(vertices[3].x, vertices[3].y));
		break;
	case 3:
		result.push_back(ci::vec2(vertices[0].x, vertices[0].z));
		result.push_back(ci::vec2(vertices[1].x, vertices[1].z));
		result.push_back(ci::vec2(vertices[2].x, vertices[2].z));
		result.push_back(ci::vec2(vertices[3].x, vertices[3].z));
		break;
	case 4:
		result.push_back(ci::vec2(vertices[0].x, vertices[0].z));
		result.push_back(ci::vec2(vertices[1].x, vertices[1].z));
		result.push_back(ci::vec2(vertices[2].x, vertices[2].z));
		result.push_back(ci::vec2(vertices[3].x, vertices[3].z));
		break;
	case 5:
		result.push_back(ci::vec2(vertices[0].x, vertices[0].z));
		result.push_back(ci::vec2(vertices[1].x, vertices[1].z));
		result.push_back(ci::vec2(vertices[2].x, vertices[2].z));
		result.push_back(ci::vec2(vertices[3].x, vertices[3].z));
		break;
	default:
		return result;
	}

	return result;
}

EdgeIndex Cube::getEdgeIndices(const unsigned int edgeIndex)
{
	EdgeIndex edge;

	switch(edgeIndex)
	{
	case 0:
		edge.m_v0 = 0;
		edge.m_v1 = 1;
		break;
	case 1:
		edge.m_v0 = 1;
		edge.m_v1 = 2;
		break;
	case 2:
		edge.m_v0 = 2;
		edge.m_v1 = 3;
		break;
	case 3:
		edge.m_v0 = 3;
		edge.m_v1 = 0;
		break;
	case 4:
		edge.m_v0 = 4;
		edge.m_v1 = 5;
		break;
	case 5:
		edge.m_v0 = 5;
		edge.m_v1 = 6;
		break;
	case 6:
		edge.m_v0 = 6;
		edge.m_v1 = 7;
		break;
	case 7:
		edge.m_v0 = 7;
		edge.m_v1 = 4;
		break;
	case 8:
		edge.m_v0 = 0;
		edge.m_v1 = 4;
		break;
	case 9:
		edge.m_v0 = 1;
		edge.m_v1 = 5;
		break;
	case 10:
		edge.m_v0 = 2;
		edge.m_v1 = 6;
		break;
	case 11:
		edge.m_v0 = 3;
		edge.m_v1 = 7;
		break;
	default:
		break;
	}

	return edge;
}

void Cube::setupVertices()
{
	m_vertices[0].x = -m_halfSize + m_center.x;
	m_vertices[0].y = -m_halfSize + m_center.y;
	m_vertices[0].z = -m_halfSize + m_center.z;

	m_vertices[1].x = m_halfSize + m_center.x;
	m_vertices[1].y = -m_halfSize + m_center.y;
	m_vertices[1].z = -m_halfSize + m_center.z;

	m_vertices[2].x = m_halfSize + m_center.x;
	m_vertices[2].y = -m_halfSize + m_center.y;
	m_vertices[2].z = m_halfSize + m_center.z;

	m_vertices[3].x = -m_halfSize + m_center.x;
	m_vertices[3].y = -m_halfSize + m_center.y;
	m_vertices[3].z = m_halfSize + m_center.z;


	m_vertices[4].x = -m_halfSize + m_center.x;
	m_vertices[4].y = m_halfSize + m_center.y;
	m_vertices[4].z = -m_halfSize + m_center.z;

	m_vertices[5].x = m_halfSize + m_center.x;
	m_vertices[5].y = m_halfSize + m_center.y;
	m_vertices[5].z = -m_halfSize + m_center.z;

	m_vertices[6].x = m_halfSize + m_center.x;
	m_vertices[6].y = m_halfSize + m_center.y;
	m_vertices[6].z = m_halfSize + m_center.z;

	m_vertices[7].x = -m_halfSize + m_center.x;
	m_vertices[7].y = m_halfSize + m_center.y;
	m_vertices[7].z = m_halfSize + m_center.z;
}