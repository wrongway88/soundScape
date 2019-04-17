#include "TerrainGenerator.h"

#include "terrain/utility/StlVectorUtility.h"

#include <map>

TerrainGenerator::TerrainGenerator():
	m_visitedCellsSize(0)
{
}

TerrainGenerator::~TerrainGenerator()
{
}

Terrain* TerrainGenerator::generateTerrain(IDensityFunction& densityFunction, float terrainSize, float cellSize)
{
	std::vector<ci::Vec3f> vertices;
	std::vector<unsigned int> indices;
	std::vector<ci::Vec3f> normals;

	std::map<int, Edge> edges;

	float halfTerrainSize = terrainSize * 0.5f;
	for(float yPos = -halfTerrainSize; yPos < halfTerrainSize; yPos += cellSize)
	{
		for(float xPos = -halfTerrainSize; xPos < halfTerrainSize; xPos += cellSize)
		{
			for(float zPos = -halfTerrainSize; zPos < halfTerrainSize; zPos += cellSize)
			{
				/*if(yPos == 0.0f && xPos == 24.0f && zPos == -32.0f)
					std::cout << "foo" << std::endl;*/

				Cell cell(ci::Vec3f(xPos, yPos, zPos), cellSize);
				cell.sampleTerrain(densityFunction, edges, terrainSize);

				std::vector<ci::Vec3f> cellVertices = cell.getVertices();
				std::vector<unsigned int> cellIndices = cell.getIndices();
				std::vector<ci::Vec3f> cellNormals = cell.getNormals();

				addTriangles(vertices, indices, normals, cellVertices, cellIndices, cellNormals);
			}
		}
	}

	Terrain* terrain = new Terrain(vertices, indices, normals);
	return terrain;
}

Terrain* TerrainGenerator::generateTerrain(IDensityFunction& densityFunction, float terrainSize, float cellSize, const ci::Vec3i& seedCell)
{
	std::vector<ci::Vec3f> vertices;
	std::vector<unsigned int> indices;
	std::vector<ci::Vec3f> normals;

	m_visitedCellsSize = int(terrainSize/cellSize);
	initializeVisitedCells(m_visitedCellsSize);

	float xPos = (float)seedCell.x * cellSize - (0.5f * terrainSize) + (cellSize * 0.5f);
	float yPos = (float)seedCell.y * cellSize - (0.5f * terrainSize) + (cellSize * 0.5f);
	float zPos = (float)seedCell.z * cellSize - (0.5f * terrainSize) + (cellSize * 0.5f);

	std::list<ci::Vec3f> cellCenters;
	cellCenters.push_back(ci::Vec3f(xPos, yPos, zPos));
	m_visitedCells[seedCell.x][seedCell.y][seedCell.z] = true;

	std::map<int, Edge> edges;

	while(cellCenters.size() > 0)
	{
		Cell cell(cellCenters.front(), cellSize);
		cell.sampleTerrain(densityFunction, edges, terrainSize);

		std::vector<ci::Vec3f> cellVertices = cell.getVertices();
		std::vector<unsigned int> cellIndices = cell.getIndices();
		std::vector<ci::Vec3f> cellNormals = cell.getNormals();

		addTriangles(vertices, indices, normals, cellVertices, cellIndices, cellNormals);
		
		cellCenters.pop_front();

		std::vector<ci::Vec3f> activeNeighbours = cell.getActiveNeighbourCenters();
		for(unsigned int i = 0; i < activeNeighbours.size(); i++)
		{
			int x = int((activeNeighbours[i].x + (terrainSize * 0.5f)) / cellSize);
			int y = int((activeNeighbours[i].y + (terrainSize * 0.5f)) / cellSize);
			int z = int((activeNeighbours[i].z + (terrainSize * 0.5f)) / cellSize);

			if(x < 0 || y < 0 || z < 0 ||
				x >= m_visitedCellsSize || y >= m_visitedCellsSize || z >= m_visitedCellsSize)
			{
				continue;
			}
			else if(m_visitedCells[x][y][z] == true)
			{
				continue;
			}
			else
			{
				m_visitedCells[x][y][z] = true;
				cellCenters.push_back(activeNeighbours[i]);
			}
		}
	}

	std::stringstream message;
	message << vertices.size() << " vertices, " << indices.size() << " indices";
	LOG_INFO(message.str());

	Terrain* terrain = new Terrain(vertices, indices, normals);
	return terrain;
}

ci::Vec3i TerrainGenerator::findSeedCell(IDensityFunction& densityFunction, float terrainSize, float cellSize)
{
	ci::Vec3i result(0, 0, 0);

	float halfTerrainSize = terrainSize * 0.5f;
	float halfCellSize = cellSize * 0.5f;
	for(float zPos = -halfTerrainSize + halfCellSize; zPos < halfTerrainSize; zPos += cellSize)
	{
		for(float xPos = -halfTerrainSize + halfCellSize; xPos < halfTerrainSize; xPos += cellSize)
		{
			for(float yPos = -halfTerrainSize + halfCellSize; yPos < halfTerrainSize; yPos += cellSize)
			{
				Cell cell(ci::Vec3f(xPos, yPos, zPos), cellSize);
				unsigned int vertexCase = cell.calculateVertexCase(densityFunction);

				if(vertexCase > 0 && vertexCase < 255)
				{
					float x = xPos + halfTerrainSize;
					float y = yPos + halfTerrainSize;
					float z = zPos + halfTerrainSize;

					int xIndex = int(x / cellSize);
					int yIndex = int(y / cellSize);
					int zIndex = int(z / cellSize);

					result.x = xIndex;
					result.y = yIndex;
					result.z = zIndex;

					return result;
				}
			}
		}
	}

	return result;
}

void TerrainGenerator::initializeVisitedCells(int size)
{
	//m_visitedCells = new bool**[size];
	for(int i = 0; i < size; i++)
	{
		std::vector<std::vector<bool> > tmpVec;
		m_visitedCells.push_back(tmpVec);
		//m_visitedCells[i] = new bool*[size];
		for(int j = 0; j < size; j++)
		{	
			std::vector<bool> vec;
			m_visitedCells[i].push_back(vec);
			//m_visitedCells[i][j] = new bool[size];
			for(int k = 0; k < size; k++)
			{
				m_visitedCells[i][j].push_back(false);
			}
		}
	}
}

void TerrainGenerator::addTriangles(std::vector<ci::Vec3f>& vertices, std::vector<unsigned int>& indices, std::vector<ci::Vec3f>& normals,
									std::vector<ci::Vec3f>& cellVertices, std::vector<unsigned int>& cellIndices, std::vector<ci::Vec3f>& cellNormals)
{
	for(unsigned int i = 0; i < cellIndices.size(); i++)
	{
		int currentIdx = cellIndices[i];

		int vIdx = StlVectorUtility::find<ci::Vec3f>(vertices, cellVertices[currentIdx]);
		if(vIdx > -1)
		{
			indices.push_back(vIdx);
		}
		else
		{
			vertices.push_back(cellVertices[currentIdx]);
			normals.push_back(cellNormals[currentIdx]);
			indices.push_back(vertices.size()-1);
		}
	}
}