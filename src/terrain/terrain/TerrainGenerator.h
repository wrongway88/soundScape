#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include "Terrain.h"
#include "Cell.h"
#include "terrain/densityFunction/IDensityFunction.h"

#include "cinder/Vector.h"

#include <list>

class TerrainGenerator
{
public:
	TerrainGenerator();
	~TerrainGenerator();

	Terrain* generateTerrain(IDensityFunction& densityFunction, float terrainSize, float cellSize);

	Terrain* generateTerrain(IDensityFunction& densityFunction, float terrainSize, float cellSize, const ci::vec3& seedCell);

	ci::vec3 findSeedCell(IDensityFunction& densityFunction, float terrainSize, float cellSize);

private:
	void initializeVisitedCells(int size);
	void addTriangles(std::vector<ci::vec3>& vertices, std::vector<unsigned int>& indices, std::vector<ci::vec3>& normals,
						std::vector<ci::vec3>& cellVertices, std::vector<unsigned int>& cellIndices, std::vector<ci::vec3>& cellNormals);

	std::vector<std::vector<std::vector<bool> > > m_visitedCells;
	int m_visitedCellsSize;
};

#endif