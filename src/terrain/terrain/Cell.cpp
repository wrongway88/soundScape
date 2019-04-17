#include "Cell.h"

#include "terrain/utility/StlVectorUtility.h"
#include "LookUpTables.h"

Cell::Cell(ci::Vec3f& center, float size):
	m_cube(center, size),
	m_activeNeighbourCenters()
{
	m_cellFaces[0] = CellFace();
	m_cellFaces[1] = CellFace();
	m_cellFaces[2] = CellFace();
	m_cellFaces[3] = CellFace();
	m_cellFaces[4] = CellFace();
	m_cellFaces[5] = CellFace();
}

Cell::~Cell()
{
}

void Cell::sampleTerrain(IDensityFunction& densityFunction, std::map<int, Edge>& edges, float terrainSize)
{
	unsigned int vertexCase = calculateVertexCase(densityFunction);
	float densities[8];

	if(vertexCase == 0 || vertexCase == 255)
		return;

	for(unsigned int i = 0; i < 8; i++)
	{
		densities[i] = densityFunction.getValue(m_cube.getVertex(i));
	}

	std::vector<VertexOrder> foo = getVertexOrderCase(vertexCase, densities);

	//std::cout << foo.size() << std::endl;

	/*for(unsigned int i = 0; i < foo.size(); i++)
	{
		if(foo[i].m_order[0] == 12 || foo[i].m_order[1] == 12 || foo[i].m_order[2] == 12)
		{
			std::cout << "interior vertex" << std::endl;
			return;
		}
	}*/

	calculateActiveNeighbours(densities);

	/*calculateFaceSaddlePoints(densities);
	calculateBodySaddlePoints(densities);*/

	VertexOrderCase vertexOrderCase = TerrainUtility::m_edgeConnectList[vertexCase];

	for(unsigned int i = 0; i < foo.size(); i++)
	{

		for(unsigned int j = 0; j < 3; j++)
		{
			int edgeIndex = foo[i].m_order[j];

			ci::Vec3f vertex;
			ci::Vec3f normal;

			if(edgeIndex == 12)
			{
				vertex = calculateInnerVertex(densities);
				normal = calculateNormal(vertex, densityFunction);


			}
			else
			{
				EdgeIndex edge = Cube::getEdgeIndices((unsigned int)edgeIndex);

				ci::Vec3f v0 = m_cube.getVertex((unsigned int)edge.m_v0);
				ci::Vec3f v1 = m_cube.getVertex((unsigned int)edge.m_v1);

				int hashValue = calculateEdgeHashValue(v0, v1, terrainSize, int(terrainSize/m_cube.getSize())+1);

				if(edges.find(hashValue) != edges.end())
				{
					Edge vEdge = edges[hashValue];

					vertex = vEdge.m_intersection;
					normal = vEdge.m_normal;

					edges[hashValue].m_timesVisited++;
				}
				else
				{
					float d0 = densities[edge.m_v0];
					float d1 = densities[edge.m_v1];
					vertex = interpolateVertexPosition(v0, d0, v1, d1);
					normal = calculateNormal(vertex, densityFunction);

					Edge newEdge;
					newEdge.m_v0 = v0;
					newEdge.m_v1 = v1;
					newEdge.m_intersection = vertex;
					newEdge.m_normal = normal;
					newEdge.m_timesVisited++;

					edges[hashValue] = newEdge;
				}
			}

			int idx = StlVectorUtility::find<ci::Vec3f>(m_vertices, vertex);

			if(idx != -1)
			{
				m_indices.push_back(idx);
			}
			else
			{
				m_vertices.push_back(vertex);
				m_normals.push_back(normal);

				if(m_indices.size() <= 0)
				{
					m_indices.push_back(0);
				}
				else
				{
					m_indices.push_back(m_vertices.size() - 1);
				}
			}
		}
	}
}

unsigned int Cell::calculateVertexCase(IDensityFunction& densityFunction)
{
	unsigned int vertexCase = 0;
	float densities[8];

	for(unsigned int i = 0; i < 8; i++)
	{
		densities[i] = densityFunction.getValue(m_cube.getVertex(i));

		if(densities[i] > 0.0f)
		{
			vertexCase += (int)std::powf(2.0f, (float)i);
		}
	}

	return vertexCase;
}

std::vector<ci::Vec3f> Cell::getVertices()
{
	return m_vertices;
}

std::vector<unsigned int> Cell::getIndices()
{
	return m_indices;
}

std::vector<ci::Vec3f> Cell::getNormals()
{
	return m_normals;
}

std::vector<ci::Vec3f> Cell::getActiveNeighbourCenters()
{
	return m_activeNeighbourCenters;
}

ci::Vec3f Cell::interpolateVertexPosition(ci::Vec3f vector0, float weight0, ci::Vec3f vector1, float weight1)
{
	float dist = std::fabs(weight0) + std::fabs(weight1);

	float w0 = 1.0f - (std::fabs(weight0) / dist);
	float w1 = 1.0f - w0;

	return vector0*w0 + vector1*w1;
}

ci::Vec3f Cell::calculateNormal(ci::Vec3f& position, IDensityFunction& densityFunction)
{
	ci::Vec3f normal;
	float cellSize = m_cube.getSize();// * 0.01f;

	normal.x = densityFunction.getValue(ci::Vec3f(position.x + cellSize, position.y, position.z)) -
				densityFunction.getValue(ci::Vec3f(position.x - cellSize, position.y, position.z));
	normal.y = densityFunction.getValue(ci::Vec3f(position.x, position.y + cellSize, position.z)) -
				densityFunction.getValue(ci::Vec3f(position.x, position.y - cellSize, position.z));
	normal.z = densityFunction.getValue(ci::Vec3f(position.x, position.y, position.z + cellSize)) -
				densityFunction.getValue(ci::Vec3f(position.x, position.y, position.z - cellSize));

	return (normal.normalized() * -1.0f);
}

void Cell::calculateFaceSaddlePoints(float densities[])
{
	std::vector<ci::Vec2f> faceVertices;
	std::vector<unsigned int> faceIndices;

	for(unsigned int i = 0; i < 6; i++)
	{
		faceIndices = m_cube.getFaceIndices(i);
		faceVertices = m_cube.getFaceVertices(i);

		m_cellFaces[i].m_vertices[0] = faceVertices[0];
		m_cellFaces[i].m_vertices[1] = faceVertices[1];
		m_cellFaces[i].m_vertices[2] = faceVertices[2];
		m_cellFaces[i].m_vertices[3] = faceVertices[3];

		faceVertices.push_back(m_cellFaces[i].m_vertices[0]);
		faceVertices.push_back(m_cellFaces[i].m_vertices[1]);
		faceVertices.push_back(m_cellFaces[i].m_vertices[2]);
		faceVertices.push_back(m_cellFaces[i].m_vertices[3]);
		
		m_cellFaces[i].m_saddlePoint = TerrainUtility::calculateFaceSaddlePoint(faceVertices[0], faceVertices[2], densities[faceIndices[0]], densities[faceIndices[1]], densities[faceIndices[2]], densities[faceIndices[3]]);
	
		/*if((m_cellFaces[i].m_saddlePoint.x > 0.0f && m_cellFaces[i].m_saddlePoint.x < 1.0f) &&
			(m_cellFaces[i].m_saddlePoint.y > 0.0f && m_cellFaces[i].m_saddlePoint.y < 1.0f))
		{
			std::cout << m_cellFaces[i].m_saddlePoint.x << ", " << m_cellFaces[i].m_saddlePoint.y << std::endl;
		}*/
	}
}

void Cell::calculateBodySaddlePoints(float densities[])
{
	CubeCornerValues cubeCornerValues(densities[0], densities[1], densities[2], densities[3], densities[4], densities[5], densities[6], densities[7]);
	std::vector<ci::Vec3f> saddlePoints = TerrainUtility::calculateBodySaddlePoints(m_cube.getVertex(0), m_cube.getVertex(6), cubeCornerValues);

	for(unsigned int i = 0;i < saddlePoints.size(); i++)
	{
		if((saddlePoints[i].x > 0.0f && saddlePoints[i].x < 1.0f) &&
			(saddlePoints[i].y > 0.0f && saddlePoints[i].y < 1.0f) &&
			(saddlePoints[i].z > 0.0f && saddlePoints[i].z < 1.0f))
		{
			m_bodySaddlePoints.push_back(saddlePoints[i]);
		}
	}
}

void Cell::calculateActiveNeighbours(float densities[])
{
	std::vector<ci::Vec3f> neighbourCenters;
	std::vector<unsigned int> faceIndices;
	
	for(unsigned int i = 0; i < 6; i++)
	{
		faceIndices = m_cube.getFaceIndices(i);
		unsigned int vertexCase = 0;

		for(unsigned int j = 0; j < faceIndices.size(); j++)
		{
			if(densities[faceIndices[j]] > 0.0f)
			{
				vertexCase += (int)std::powf(2.0f, (float)j);
			}
		}

		if(vertexCase != 0 && vertexCase != 15 && vertexCase != 1)
		{
			switch(i)
			{
			case 0:
				m_activeNeighbourCenters.push_back(m_cube.getCenter() + ci::Vec3f(0.0f, 0.0f, -m_cube.getSize()));
				break;
			case 1:
				m_activeNeighbourCenters.push_back(m_cube.getCenter() + ci::Vec3f(m_cube.getSize(), 0.0f, 0.0f));
				break;
			case 2:
				m_activeNeighbourCenters.push_back(m_cube.getCenter() + ci::Vec3f(0.0f, 0.0f, m_cube.getSize()));
				break;
			case 3:
				m_activeNeighbourCenters.push_back(m_cube.getCenter() + ci::Vec3f(-m_cube.getSize(), 0.0f, 0.0f));
				break;
			case 4:
				m_activeNeighbourCenters.push_back(m_cube.getCenter() + ci::Vec3f(0.0f, -m_cube.getSize(), 0.0f));
				break;
			case 5:
				m_activeNeighbourCenters.push_back(m_cube.getCenter() + ci::Vec3f(0.0f, m_cube.getSize(), 0.0f));
				break;
			}
		}
	}
}

int Cell::calculateEdgeHashValue(const ci::Vec3f& v0, const ci::Vec3f& v1, float terrainSize, int vertexCount1d)
{
	float cubeSize = m_cube.getSize();

	int x0 = int((v0.x + (terrainSize * 0.5f) + (cubeSize*0.5f)) / cubeSize);
	int y0 = int((v0.y + (terrainSize * 0.5f) + (cubeSize*0.5f)) / cubeSize);
	int z0 = int((v0.z + (terrainSize * 0.5f) + (cubeSize*0.5f)) / cubeSize);

	int x1 = int((v1.x + (terrainSize * 0.5f) + (cubeSize*0.5f)) / cubeSize);
	int y1 = int((v1.y + (terrainSize * 0.5f) + (cubeSize*0.5f)) / cubeSize);
	int z1 = int((v1.z + (terrainSize * 0.5f) + (cubeSize*0.5f)) / cubeSize);

	int result = 0;

	if(x0+y0+z0 < x1+y1+z1)
	{
		result = x0*(vertexCount1d*vertexCount1d) + y0*vertexCount1d + z0;
	}
	else
	{
		result = x1*(vertexCount1d*vertexCount1d) + y1*vertexCount1d + z1;
	}

	result *= 4;

	if((x0 - x1) != 0)
	{
		result += 1;
	}
	else if((y0 - y1) != 0)
	{
		result += 2;
	}
	else
	{
		result += 3;
	}

	return result;
}

std::vector<VertexOrder> Cell::getVertexOrderCase(const unsigned int vertexCase, const float densities[8])
{
	std::vector<VertexOrder> result;

	unsigned int uniqueCase = LookUpTables::m_cases[vertexCase][0];
	unsigned int configuration = LookUpTables::m_cases[vertexCase][1];
	int subConfig = 0;


	/*if(vertexCase != 0 && vertexCase != 255)
		std::cout << (int)LookUpTables::m_cases[vertexCase][0] << ", " << (int)LookUpTables::m_cases[vertexCase][1] << std::endl;*/

	switch(uniqueCase)
	{
	case 1:
		result = getVertexOrders(LookUpTables::m_tiling1[configuration], 3);
		break;
	case 2:
		result = getVertexOrders(LookUpTables::m_tiling2[configuration], 6);
		break;
	case 3:
		if(testFace(LookUpTables::m_test3[configuration], densities))
		{
			result = getVertexOrders(LookUpTables::m_tiling3_2[configuration], 12);
		}
		else
		{
			result = getVertexOrders(LookUpTables::m_tiling3_1[configuration], 6);
		}
		break;
	case 4:
		if(testInterior(vertexCase, configuration, 0, LookUpTables::m_test4[configuration], densities))
		{
			result = getVertexOrders(LookUpTables::m_tiling4_1[configuration], 6);
		}
		else
		{
			result = getVertexOrders(LookUpTables::m_tiling4_2[configuration], 18);
		}
		break;
	case 5:
		result = getVertexOrders(LookUpTables::m_tiling5[configuration], 9);
		break;
	case 6:
		if(testFace(LookUpTables::m_test6[configuration][0], densities))
		{
			result = getVertexOrders(LookUpTables::m_tiling6_2[configuration], 15);
		}
		else
		{
			if(testInterior(vertexCase, configuration, 0, LookUpTables::m_test6[configuration][1], densities))
			{
				result = getVertexOrders(LookUpTables::m_tiling6_1_1[configuration], 9);
			}
			else
			{
				//calculate interior vertex in this case...
				result = getVertexOrders(LookUpTables::m_tiling6_1_2[configuration], 27); //interior vertex
			}
		}
		break;
	case 7:
		if(testFace(LookUpTables::m_test7[configuration][0], densities))
			subConfig += 1;
		if(testFace(LookUpTables::m_test7[configuration][1], densities))
			subConfig += 2;
		if(testFace(LookUpTables::m_test7[configuration][2], densities))
			subConfig += 4;
		switch(subConfig)
		{
		case 0:
			result = getVertexOrders(LookUpTables::m_tiling7_1[configuration], 9);
			break;
		case 1:
			result = getVertexOrders(LookUpTables::m_tiling7_2[configuration][0], 15);
			break;
		case 2:
			result = getVertexOrders(LookUpTables::m_tiling7_2[configuration][1], 15);
			break;
		case 3:
			result = getVertexOrders(LookUpTables::m_tiling7_3[configuration][0], 27); //interior vertex
			break;
		case 4:
			result = getVertexOrders(LookUpTables::m_tiling7_2[configuration][2], 15);
			break;
		case 5:
			result = getVertexOrders(LookUpTables::m_tiling7_3[configuration][1], 27); //interior vertex
			break;
		case 6:
			result = getVertexOrders(LookUpTables::m_tiling7_3[configuration][2], 27); //interior vertex
			break;
		case 7:
			if(testInterior(vertexCase, configuration, subConfig, LookUpTables::m_test7[configuration][3], densities))
			{
				result = getVertexOrders(LookUpTables::m_tiling7_4_2[configuration], 27);
			}
			else
			{
				result = getVertexOrders(LookUpTables::m_tiling7_4_1[configuration], 15);
			}
			break;
		}
		break;
	case 8:
		result = getVertexOrders(LookUpTables::m_tiling8[configuration], 6);
		break;
	case 9:
		result = getVertexOrders(LookUpTables::m_tiling9[configuration], 12);
		break;
	case 10:
		if(testFace(LookUpTables::m_test10[configuration][0], densities))
		{
			if(testFace(LookUpTables::m_test10[configuration][1], densities))
			{
				result = getVertexOrders(LookUpTables::m_tiling10_1_1_[configuration], 12);
			}
			else
			{
				result = getVertexOrders(LookUpTables::m_tiling10_2[configuration], 24); //interior vertex
			}
		}
		else
		{
			if(testFace(LookUpTables::m_test10[configuration][1], densities))
			{
				result = getVertexOrders(LookUpTables::m_tiling10_2_[configuration], 24); //interior vertex
			}
			else
			{
				if(testInterior(vertexCase, configuration, 0, LookUpTables::m_test10[configuration][2], densities))
				{
					result = getVertexOrders(LookUpTables::m_tiling10_1_1[configuration], 12); //interior vertex
				}
				else
				{
					result = getVertexOrders(LookUpTables::m_tiling10_1_2[configuration], 24); //interior vertex
				}
			}
		}
		break;
	case 11:
		result = getVertexOrders(LookUpTables::m_tiling11[configuration], 12);
		break;
	case 12:
		if(testFace(LookUpTables::m_test12[configuration][0], densities))
		{
			if(testFace(LookUpTables::m_test12[configuration][1], densities))
			{
				result = getVertexOrders(LookUpTables::m_tiling12_1_1_[configuration], 12);
			}
			else
			{
				result = getVertexOrders(LookUpTables::m_tiling12_2[configuration], 24); //internal vertex
			}
		}
		else
		{
			if(testFace(LookUpTables::m_test12[configuration][1], densities))
			{
				result = getVertexOrders(LookUpTables::m_tiling12_2_[configuration], 24); //internal vertex
			}
			else
			{
				if(testInterior(vertexCase, configuration, 0, LookUpTables::m_test12[configuration][2], densities))
				{
					result = getVertexOrders(LookUpTables::m_tiling12_1_1[configuration], 12);
				}
				else
				{
					result = getVertexOrders(LookUpTables::m_tiling12_1_2[configuration], 24);
				}
			}
		}
		break;
	case 13:
		if(testFace(LookUpTables::m_test13[configuration][0], densities)) subConfig += 1;
		if(testFace(LookUpTables::m_test13[configuration][1], densities)) subConfig += 2;
		if(testFace(LookUpTables::m_test13[configuration][2], densities)) subConfig += 4;
		if(testFace(LookUpTables::m_test13[configuration][3], densities)) subConfig += 8;
		if(testFace(LookUpTables::m_test13[configuration][4], densities)) subConfig += 16;
		if(testFace(LookUpTables::m_test13[configuration][5], densities)) subConfig += 32;
		
		switch(LookUpTables::m_subconfig13[subConfig])
		{
		case 0:
			result = getVertexOrders(LookUpTables::m_tiling13_1[configuration], 12);
			break;
		case 1:
			result = getVertexOrders(LookUpTables::m_tiling13_2[configuration][0], 18);
			break;
		case 2:
			result = getVertexOrders(LookUpTables::m_tiling13_2[configuration][1], 18);
			break;
		case 3:
			result = getVertexOrders(LookUpTables::m_tiling13_2[configuration][2], 18);
			break;
		case 4:
			result = getVertexOrders(LookUpTables::m_tiling13_2[configuration][3], 18);
			break;
		case 5:
			result = getVertexOrders(LookUpTables::m_tiling13_2[configuration][4], 18);
			break;
		case 6:
			result = getVertexOrders(LookUpTables::m_tiling13_2[configuration][5], 18);
			break;
		case 7:
			result = getVertexOrders(LookUpTables::m_tiling13_3[configuration][0], 30); //interior vertex
			break;
		case 8:
			result = getVertexOrders(LookUpTables::m_tiling13_3[configuration][1], 30); //interior vertex
			break;
		case 9:
			result = getVertexOrders(LookUpTables::m_tiling13_3[configuration][2], 30); //interior vertex
			break;
		case 10:
			result = getVertexOrders(LookUpTables::m_tiling13_3[configuration][3], 30); //interior vertex
			break;
		case 11:
			result = getVertexOrders(LookUpTables::m_tiling13_3[configuration][4], 30); //interior vertex
			break;
		case 12:
			result = getVertexOrders(LookUpTables::m_tiling13_3[configuration][5], 30); //interior vertex
			break;
		case 13:
			result = getVertexOrders(LookUpTables::m_tiling13_3[configuration][6], 30); //interior vertex
			break;
		case 14:
			result = getVertexOrders(LookUpTables::m_tiling13_3[configuration][7], 30); //interior vertex
			break;
		case 15:
			result = getVertexOrders(LookUpTables::m_tiling13_3[configuration][8], 30); //interior vertex
			break;
		case 16:
			result = getVertexOrders(LookUpTables::m_tiling13_3[configuration][9], 30); //interior vertex
			break;
		case 17:
			result = getVertexOrders(LookUpTables::m_tiling13_3[configuration][10], 30); //interior vertex
			break;
		case 18:
			result = getVertexOrders(LookUpTables::m_tiling13_3[configuration][11], 30); //interior vertex
			break;
		case 19:
			result = getVertexOrders(LookUpTables::m_tiling13_4[configuration][0], 36); //interior vertex
			break;
		case 20:
			result = getVertexOrders(LookUpTables::m_tiling13_4[configuration][1], 36); //interior vertex
			break;
		case 21:
			result = getVertexOrders(LookUpTables::m_tiling13_4[configuration][2], 36); //interior vertex
			break;
		case 22:
			result = getVertexOrders(LookUpTables::m_tiling13_4[configuration][3], 36); //interior vertex
			break;
		case 23:
			subConfig = 0;
			if(testInterior(vertexCase, configuration, subConfig, LookUpTables::m_test13[configuration][6], densities))
			{
				result = getVertexOrders(LookUpTables::m_tiling13_5_1[configuration][0], 18);
			}
			else
			{
				result = getVertexOrders(LookUpTables::m_tiling13_5_2[configuration][0], 30);
			}
			break;
		case 24:
			subConfig = 1;
			if(testInterior(vertexCase, configuration, subConfig, LookUpTables::m_test13[configuration][6], densities))
			{
				result = getVertexOrders(LookUpTables::m_tiling13_5_1[configuration][1], 18);
			}
			else
			{
				result = getVertexOrders(LookUpTables::m_tiling13_5_2[configuration][1], 30);
			}
		case 25:
			subConfig = 2;
			if(testInterior(vertexCase, configuration, subConfig, LookUpTables::m_test13[configuration][6], densities))
			{
				result = getVertexOrders(LookUpTables::m_tiling13_5_1[configuration][2], 18);
			}
			else
			{
				result = getVertexOrders(LookUpTables::m_tiling13_5_2[configuration][2], 30);
			}
		case 26:
			subConfig = 3;
			if(testInterior(vertexCase, configuration, subConfig, LookUpTables::m_test13[configuration][6], densities))
			{
				result = getVertexOrders(LookUpTables::m_tiling13_5_1[configuration][3], 18);
			}
			else
			{
				result = getVertexOrders(LookUpTables::m_tiling13_5_2[configuration][3], 30);
			}
			break;
		case 27:
			result = getVertexOrders(LookUpTables::m_tiling13_3_[configuration][0], 30); //interior vertex
			break;
		case 28:
			result = getVertexOrders(LookUpTables::m_tiling13_3_[configuration][1], 30); //interior vertex
			break;
		case 29:
			result = getVertexOrders(LookUpTables::m_tiling13_3_[configuration][2], 30); //interior vertex
			break;
		case 30:
			result = getVertexOrders(LookUpTables::m_tiling13_3_[configuration][3], 30); //interior vertex
			break;
		case 31:
			result = getVertexOrders(LookUpTables::m_tiling13_3_[configuration][4], 30); //interior vertex
			break;
		case 32:
			result = getVertexOrders(LookUpTables::m_tiling13_3_[configuration][5], 30); //interior vertex
			break;
		case 33:
			result = getVertexOrders(LookUpTables::m_tiling13_3_[configuration][6], 30); //interior vertex
			break;
		case 34:
			result = getVertexOrders(LookUpTables::m_tiling13_3_[configuration][7], 30); //interior vertex
			break;
		case 35:
			result = getVertexOrders(LookUpTables::m_tiling13_3_[configuration][8], 30); //interior vertex
			break;
		case 36:
			result = getVertexOrders(LookUpTables::m_tiling13_3_[configuration][9], 30); //interior vertex
			break;
		case 37:
			result = getVertexOrders(LookUpTables::m_tiling13_3_[configuration][10], 30); //interior vertex
			break;
		case 38:
			result = getVertexOrders(LookUpTables::m_tiling13_3_[configuration][11], 30); //interior vertex
			break;
		case 39:
			result = getVertexOrders(LookUpTables::m_tiling13_2_[configuration][0], 18);
			break;
		case 40:
			result = getVertexOrders(LookUpTables::m_tiling13_2_[configuration][1], 18);
			break;
		case 41:
			result = getVertexOrders(LookUpTables::m_tiling13_2_[configuration][2], 18);
			break;
		case 42:
			result = getVertexOrders(LookUpTables::m_tiling13_2_[configuration][3], 18);
			break;
		case 43:
			result = getVertexOrders(LookUpTables::m_tiling13_2_[configuration][4], 18);
			break;
		case 44:
			result = getVertexOrders(LookUpTables::m_tiling13_2_[configuration][5], 18);
			break;
		case 45:
			result = getVertexOrders(LookUpTables::m_tiling13_1_[configuration], 12);
			break;
		}
		break;
	case 14:
		result = getVertexOrders(LookUpTables::m_tiling14[configuration], 12);
		break;
	/*default:
		break;*/
	}

	return result;
}

std::vector<VertexOrder> Cell::getVertexOrders(const char indices[], const unsigned int size)
{
	if(size % 3 != 0)
	{
		LOG_ERROR("Invalid indices");
	}

	std::vector<VertexOrder> result;

	for(unsigned int i = 0; i < size-2; i+=3)
	{
		VertexOrder vertexOrder;
		vertexOrder.m_order[0] = (int)indices[i];
		vertexOrder.m_order[1] = (int)indices[i+1];
		vertexOrder.m_order[2] = (int)indices[i+2];

		result.push_back(vertexOrder);
	}

	return result;
}

bool Cell::testFace(const int faceIndex, const float densities[8])
{
	int correctedIndex = 0;
	if(faceIndex > 0)
	{
		correctedIndex = faceIndex-1;
	}
	else
	{
		correctedIndex = faceIndex+1;
	}

	if(correctedIndex > 5 || correctedIndex < -5)
	{
		LOG_ERROR("Invalid face index");
		return false;
	}

	float a = 0.0f;
	float b = 0.0f;
	float c = 0.0f;
	float d = 0.0f;

	std::vector<unsigned int> faceIndices = m_cube.getFaceIndices(std::abs(correctedIndex));

	if(faceIndices.size() != 4)
	{
		LOG_ERROR("Invalid face indices");
		return false;
	}

	a = densities[faceIndices[0]];
	b = densities[faceIndices[1]];
	c = densities[faceIndices[2]];
	d = densities[faceIndices[3]];

	if(std::fabs(a*c - b*d) < FLT_EPSILON)
	{
		return faceIndex >= 0;
	}
	return faceIndex * a * (a*c - b*d) >= 0;
}

bool Cell::testInterior(const unsigned int vertexCase, const unsigned int configuration, const unsigned int subConfiguration, const int testCase, const float densities[8])
{
	float at = 0.0f;
	float bt = 0.0f;
	float ct = 0.0f;
	float dt = 0.0f;
	float a = 0.0f;
	float b = 0.0f;
	float t = 0.0f;

	switch(vertexCase)
	{
	case 4:
	case 10:
		a = (densities[4]-densities[0])*(densities[6]-densities[2]) - (densities[7]-densities[3])*(densities[5]-densities[1]);
		b = densities[2] * (densities[4]-densities[0]) + densities[0] * (densities[6]-densities[2]) -
			densities[1] * (densities[7]-densities[3]) - densities[3] * (densities[5]-densities[1]);
		t = -b/(2*a);
		if(t < 0.0f || t > 1.0f)
		{
			return testCase > 0;
		}

		at = densities[0] + (densities[4] - densities[0]) * t;
		bt = densities[3] + (densities[7] - densities[3]) * t;
		ct = densities[2] + (densities[6] - densities[2]) * t;
		dt = densities[1] + (densities[5] - densities[1]) * t;
		break;

	case 6:
	case 7:
	case 12:
	case 13:
		int edge = -1;
		switch(vertexCase)
		{
			case 6: edge = LookUpTables::m_test6[configuration][2]; break;
			case 7: edge = LookUpTables::m_test7[configuration][4]; break;
			case 12: edge = LookUpTables::m_test12[configuration][3]; break;
			case 13: edge = LookUpTables::m_tiling13_5_1[configuration][subConfiguration][0]; break;
		}
		switch(edge)
		{
		case  0 :
			t  = densities[0] / ( densities[0] - densities[1] ) ;
			at = 0 ;
			bt = densities[3] + ( densities[2] - densities[3] ) * t ;
			ct = densities[7] + ( densities[6] - densities[7] ) * t ;
			dt = densities[4] + ( densities[5] - densities[4] ) * t ;
			break ;
		case  1 :
			t  = densities[1] / ( densities[1] - densities[2] ) ;
			at = 0 ;
			bt = densities[0] + ( densities[3] - densities[0] ) * t ;
			ct = densities[4] + ( densities[7] - densities[4] ) * t ;
			dt = densities[5] + ( densities[6] - densities[5] ) * t ;
			break ;
		case  2 :
			t  = densities[2] / ( densities[2] - densities[3] ) ;
			at = 0 ;
			bt = densities[1] + ( densities[0] - densities[1] ) * t ;
			ct = densities[5] + ( densities[4] - densities[5] ) * t ;
			dt = densities[6] + ( densities[7] - densities[6] ) * t ;
			break ;
		case  3 :
			t  = densities[3] / ( densities[3] - densities[0] ) ;
			at = 0 ;
			bt = densities[2] + ( densities[1] - densities[2] ) * t ;
			ct = densities[6] + ( densities[5] - densities[6] ) * t ;
			dt = densities[7] + ( densities[4] - densities[7] ) * t ;
			break ;
		case  4 :
			t  = densities[4] / ( densities[4] - densities[5] ) ;
			at = 0 ;
			bt = densities[7] + ( densities[6] - densities[7] ) * t ;
			ct = densities[3] + ( densities[2] - densities[3] ) * t ;
			dt = densities[0] + ( densities[1] - densities[0] ) * t ;
			break ;
		case  5 :
			t  = densities[5] / ( densities[5] - densities[6] ) ;
			at = 0 ;
			bt = densities[4] + ( densities[7] - densities[4] ) * t ;
			ct = densities[0] + ( densities[3] - densities[0] ) * t ;
			dt = densities[1] + ( densities[2] - densities[1] ) * t ;
			break ;
		case  6 :
			t  = densities[6] / ( densities[6] - densities[7] ) ;
			at = 0 ;
			bt = densities[5] + ( densities[4] - densities[5] ) * t ;
			ct = densities[1] + ( densities[0] - densities[1] ) * t ;
			dt = densities[2] + ( densities[3] - densities[2] ) * t ;
			break ;
		case  7 :
			t  = densities[7] / ( densities[7] - densities[4] ) ;
			at = 0 ;
			bt = densities[6] + ( densities[5] - densities[6] ) * t ;
			ct = densities[2] + ( densities[1] - densities[2] ) * t ;
			dt = densities[3] + ( densities[0] - densities[3] ) * t ;
			break ;
		case  8 :
			t  = densities[0] / ( densities[0] - densities[4] ) ;
			at = 0 ;
			bt = densities[3] + ( densities[7] - densities[3] ) * t ;
			ct = densities[2] + ( densities[6] - densities[2] ) * t ;
			dt = densities[1] + ( densities[5] - densities[1] ) * t ;
			break ;
		case  9 :
			t  = densities[1] / ( densities[1] - densities[5] ) ;
			at = 0 ;
			bt = densities[0] + ( densities[4] - densities[0] ) * t ;
			ct = densities[3] + ( densities[7] - densities[3] ) * t ;
			dt = densities[2] + ( densities[6] - densities[2] ) * t ;
			break ;
		case 10 :
			t  = densities[2] / ( densities[2] - densities[6] ) ;
			at = 0 ;
			bt = densities[1] + ( densities[5] - densities[1] ) * t ;
			ct = densities[0] + ( densities[4] - densities[0] ) * t ;
			dt = densities[3] + ( densities[7] - densities[3] ) * t ;
			break ;
		case 11 :
			t  = densities[3] / ( densities[3] - densities[7] ) ;
			at = 0 ;
			bt = densities[2] + ( densities[6] - densities[2] ) * t ;
			ct = densities[1] + ( densities[5] - densities[1] ) * t ;
			dt = densities[0] + ( densities[4] - densities[0] ) * t ;
			break ;
		}

		int test = 0;
		if( at >= 0 ) test ++ ;
		if( bt >= 0 ) test += 2 ;
		if( ct >= 0 ) test += 4 ;
		if( dt >= 0 ) test += 8 ;
		switch( test )
		{
			case  0 : return testCase>0 ;
			case  1 : return testCase>0 ;
			case  2 : return testCase>0 ;
			case  3 : return testCase>0 ;
			case  4 : return testCase>0 ;
			case  5 : if( at * ct - bt * dt <  FLT_EPSILON ) return testCase>0 ; break ;
			case  6 : return testCase>0 ;
			case  7 : return testCase<0 ;
			case  8 : return testCase>0 ;
			case  9 : return testCase>0 ;
			case 10 : if( at * ct - bt * dt >= FLT_EPSILON ) return testCase>0 ; break ;
			case 11 : return testCase<0 ;
			case 12 : return testCase>0 ;
			case 13 : return testCase<0 ;
			case 14 : return testCase<0 ;
			case 15 : return testCase<0 ;
		}
		break;
	/*default:
		LOG_ERROR("invalid vertexCase");
		break;*/
	}
	
	return testCase<0;
}

ci::Vec3f Cell::calculateInnerVertex(const float densities[8])
{
	std::vector<ci::Vec3f> edgeVertices;

	for(unsigned int i = 0; i < 12; i++)
	{
		EdgeIndex edge = m_cube.getEdgeIndices(i);
		float d0 = densities[edge.m_v0];
		float d1 = densities[edge.m_v1];

		if((d0 * d1) < 0.0f) //check if only one value is below 0
		{
			ci::Vec3f v0 = m_cube.getVertex(edge.m_v0);
			ci::Vec3f v1 = m_cube.getVertex(edge.m_v1);

			ci::Vec3f vertex = interpolateVertexPosition(v0, d0, v1, d1);
			edgeVertices.push_back(vertex);
		}
	}

	ci::Vec3f result;
	for(unsigned int i = 0; i < edgeVertices.size(); i++)
	{
		result += edgeVertices[i];
	}
	result /= (float)edgeVertices.size();

	return result;
}