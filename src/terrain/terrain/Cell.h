#ifndef CELL_H
#define CELL_H

#include "TerrainUtility.h"
#include "terrain/common/Cube.h"
#include "terrain/densityFunction/IDensityFunction.h"

#include <map>

struct CellFace
{
public:
	ci::vec2 m_vertices[4];
	ci::vec2 m_saddlePoint;

	CellFace():
		m_saddlePoint()
	{
		m_vertices[0] = ci::vec2(0.0f, 0.0f);
		m_vertices[1] = ci::vec2(0.0f, 0.0f);
		m_vertices[2] = ci::vec2(0.0f, 0.0f);
		m_vertices[3] = ci::vec2(0.0f, 0.0f);
	}
};

class Cell
{
public:
	Cell(const ci::vec3& center, const float size);
	~Cell();

	void sampleTerrain(IDensityFunction& densityFunction, std::map<int, Edge>& edges, float terrainSize);
	unsigned int calculateVertexCase(IDensityFunction& densityFunction);

	std::vector<ci::vec3> getVertices();
	std::vector<unsigned int> getIndices();
	std::vector<ci::vec3> getNormals();

	std::vector<ci::vec3> getActiveNeighbourCenters();

private:
	ci::vec3 interpolateVertexPosition(ci::vec3 vector0, float weight0, ci::vec3 vector1, float weight1);
	ci::vec3 calculateNormal(ci::vec3& position, IDensityFunction& densityFunction);

	void calculateFaceSaddlePoints(float densities[]);
	void calculateBodySaddlePoints(float densities[]);

	void calculateActiveNeighbours(float densities[]);

	int calculateEdgeHashValue(const ci::vec3& v0, const ci::vec3& v1, float terrainSize, int vertexCount1d);

	std::vector<VertexOrder> getVertexOrderCase(const unsigned int vertexCase, const float densities[8]);
	std::vector<VertexOrder> getVertexOrders(const char indices[], const unsigned int size);
	bool testFace(const int faceIndex, const float densities[8]);
	bool testInterior(const unsigned int vertexCase, const unsigned int configuration, const unsigned int subConfiguration, const int testCase, const float densities[8]);

	ci::vec3 calculateInnerVertex(const float densities[8]);

	Cube m_cube;

	std::vector<ci::vec3> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<ci::vec3> m_normals;

	CellFace m_cellFaces[6];

	std::vector<ci::vec3> m_bodySaddlePoints;
	std::vector<ci::vec3> m_activeNeighbourCenters;
};

#endif