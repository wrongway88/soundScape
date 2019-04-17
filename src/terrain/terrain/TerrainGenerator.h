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

	Terrain* generateTerrain(IDensityFunction& densityFunction, float terrainSize, float cellSize, const ci::Vec3i& seedCell);

	ci::Vec3i findSeedCell(IDensityFunction& densityFunction, float terrainSize, float cellSize);

private:
	void initializeVisitedCells(int size);
	void addTriangles(std::vector<ci::Vec3f>& vertices, std::vector<unsigned int>& indices, std::vector<ci::Vec3f>& normals,
						std::vector<ci::Vec3f>& cellVertices, std::vector<unsigned int>& cellIndices, std::vector<ci::Vec3f>& cellNormals);

	std::vector<std::vector<std::vector<bool> > > m_visitedCells;
	int m_visitedCellsSize;
};

#endif