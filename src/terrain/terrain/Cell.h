#ifndef CELL_H
#define CELL_H

#include "TerrainUtility.h"
#include "terrain/common/Cube.h"
#include "terrain/densityFunction/IDensityFunction.h"

#include <map>

struct CellFace
{
public:
	ci::Vec2f m_vertices[4];
	ci::Vec2f m_saddlePoint;

	CellFace():
		m_saddlePoint()
	{
		m_vertices[0] = ci::Vec2f(0.0f, 0.0f);
		m_vertices[1] = ci::Vec2f(0.0f, 0.0f);
		m_vertices[2] = ci::Vec2f(0.0f, 0.0f);
		m_vertices[3] = ci::Vec2f(0.0f, 0.0f);
	}
};

class Cell
{
public:
	Cell(ci::Vec3f& center, float size);
	~Cell();

	void sampleTerrain(IDensityFunction& densityFunction, std::map<int, Edge>& edges, float terrainSize);
	unsigned int calculateVertexCase(IDensityFunction& densityFunction);

	std::vector<ci::Vec3f> getVertices();
	std::vector<unsigned int> getIndices();
	std::vector<ci::Vec3f> getNormals();

	std::vector<ci::Vec3f> getActiveNeighbourCenters();

private:
	ci::Vec3f interpolateVertexPosition(ci::Vec3f vector0, float weight0, ci::Vec3f vector1, float weight1);
	ci::Vec3f calculateNormal(ci::Vec3f& position, IDensityFunction& densityFunction);

	void calculateFaceSaddlePoints(float densities[]);
	void calculateBodySaddlePoints(float densities[]);

	void calculateActiveNeighbours(float densities[]);

	int calculateEdgeHashValue(const ci::Vec3f& v0, const ci::Vec3f& v1, float terrainSize, int vertexCount1d);

	std::vector<VertexOrder> getVertexOrderCase(const unsigned int vertexCase, const float densities[8]);
	std::vector<VertexOrder> getVertexOrders(const char indices[], const unsigned int size);
	bool testFace(const int faceIndex, const float densities[8]);
	bool testInterior(const unsigned int vertexCase, const unsigned int configuration, const unsigned int subConfiguration, const int testCase, const float densities[8]);

	ci::Vec3f calculateInnerVertex(const float densities[8]);

	Cube m_cube;

	std::vector<ci::Vec3f> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<ci::Vec3f> m_normals;

	CellFace m_cellFaces[6];

	std::vector<ci::Vec3f> m_bodySaddlePoints;
	std::vector<ci::Vec3f> m_activeNeighbourCenters;
};

#endif