#include "TerrainUtility.h"

const int TerrainUtility::m_caseToNumPolys[] = {
													0, 1, 1, 2, 1, 2, 2, 3,  1, 2, 2, 3, 2, 3, 3, 2,  1, 2, 2, 3, 2, 3, 3, 4,  2, 3, 3, 4, 3, 4, 4, 3,  
													1, 2, 2, 3, 2, 3, 3, 4,  2, 3, 3, 4, 3, 4, 4, 3,  2, 3, 3, 2, 3, 4, 4, 3,  3, 4, 4, 3, 4, 5, 5, 2,  
													1, 2, 2, 3, 2, 3, 3, 4,  2, 3, 3, 4, 3, 4, 4, 3,  2, 3, 3, 4, 3, 4, 4, 5,  3, 4, 4, 5, 4, 5, 5, 4,  
													2, 3, 3, 4, 3, 4, 2, 3,  3, 4, 4, 5, 4, 5, 3, 2,  3, 4, 4, 3, 4, 5, 3, 2,  4, 5, 5, 4, 5, 2, 4, 1,  
													1, 2, 2, 3, 2, 3, 3, 4,  2, 3, 3, 4, 3, 4, 4, 3,  2, 3, 3, 4, 3, 4, 4, 5,  3, 2, 4, 3, 4, 3, 5, 2,  
													2, 3, 3, 4, 3, 4, 4, 5,  3, 4, 4, 5, 4, 5, 5, 4,  3, 4, 4, 3, 4, 5, 5, 4,  4, 3, 5, 2, 5, 4, 2, 1,  
													2, 3, 3, 4, 3, 4, 4, 5,  3, 4, 4, 5, 2, 3, 3, 2,  3, 4, 4, 5, 4, 5, 5, 2,  4, 3, 5, 4, 3, 2, 4, 1,  
													3, 4, 4, 5, 4, 5, 3, 4,  4, 5, 5, 2, 3, 4, 2, 1,  2, 3, 3, 2, 3, 4, 2, 1,  3, 2, 4, 1, 2, 1, 1, 0
												};

const VertexOrderCase TerrainUtility::m_edgeConnectList[] = {
																VertexOrderCase(VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 8, 3),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 1, 9),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 8, 3),VertexOrder(9, 8, 1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 2, 10),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 8, 3),VertexOrder(1, 2, 10),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 2, 10),VertexOrder(0, 2, 9),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 8, 3),VertexOrder(2, 10, 8),VertexOrder(10, 9, 8),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 11, 2),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 11, 2),VertexOrder(8, 11, 0),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 9, 0),VertexOrder(2, 3, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 11, 2),VertexOrder(1, 9, 11),VertexOrder(9, 8, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 10, 1),VertexOrder(11, 10, 3),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 10, 1),VertexOrder(0, 8, 10),VertexOrder(8, 11, 10),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 9, 0),VertexOrder(3, 11, 9),VertexOrder(11, 10, 9),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 8, 10),VertexOrder(10, 8, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 7, 8),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 3, 0),VertexOrder(7, 3, 4),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 1, 9),VertexOrder(8, 4, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 1, 9),VertexOrder(4, 7, 1),VertexOrder(7, 3, 1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 2, 10),VertexOrder(8, 4, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 4, 7),VertexOrder(3, 0, 4),VertexOrder(1, 2, 10),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 2, 10),VertexOrder(9, 0, 2),VertexOrder(8, 4, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 10, 9),VertexOrder(2, 9, 7),VertexOrder(2, 7, 3),VertexOrder(7, 9, 4),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 4, 7),VertexOrder(3, 11, 2),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(11, 4, 7),VertexOrder(11, 2, 4),VertexOrder(2, 0, 4),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 0, 1),VertexOrder(8, 4, 7),VertexOrder(2, 3, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 7, 11),VertexOrder(9, 4, 11),VertexOrder(9, 11, 2),VertexOrder(9, 2, 1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 10, 1),VertexOrder(3, 11, 10),VertexOrder(7, 8, 4),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 11, 10),VertexOrder(1, 4, 11),VertexOrder(1, 0, 4),VertexOrder(7, 11, 4),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 7, 8),VertexOrder(9, 0, 11),VertexOrder(9, 11, 10),VertexOrder(11, 0, 3),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 7, 11),VertexOrder(4, 11, 9),VertexOrder(9, 11, 10),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 5, 4),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 5, 4),VertexOrder(0, 8, 3),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 5, 4),VertexOrder(1, 5, 0),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 5, 4),VertexOrder(8, 3, 5),VertexOrder(3, 1, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 2, 10),VertexOrder(9, 5, 4),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 0, 8),VertexOrder(1, 2, 10),VertexOrder(4, 9, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 2, 10),VertexOrder(5, 4, 2),VertexOrder(4, 0, 2),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 10, 5),VertexOrder(3, 2, 5),VertexOrder(3, 5, 4),VertexOrder(3, 4, 8),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 5, 4),VertexOrder(2, 3, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 11, 2),VertexOrder(0, 8, 11),VertexOrder(4, 9, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 5, 4),VertexOrder(0, 1, 5),VertexOrder(2, 3, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 1, 5),VertexOrder(2, 5, 8),VertexOrder(2, 8, 11),VertexOrder(4, 8, 5),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 3, 11),VertexOrder(10, 1, 3),VertexOrder(9, 5, 4),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 9, 5),VertexOrder(0, 8, 1),VertexOrder(8, 10, 1),VertexOrder(8, 11, 10),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 4, 0),VertexOrder(5, 0, 11),VertexOrder(5, 11, 10),VertexOrder(11, 0, 3),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 4, 8),VertexOrder(5, 8, 10),VertexOrder(10, 8, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 7, 8),VertexOrder(5, 7, 9),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 3, 0),VertexOrder(9, 5, 3),VertexOrder(5, 7, 3),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 7, 8),VertexOrder(0, 1, 7),VertexOrder(1, 5, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 5, 3),VertexOrder(3, 5, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 7, 8),VertexOrder(9, 5, 7),VertexOrder(10, 1, 2),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 1, 2),VertexOrder(9, 5, 0),VertexOrder(5, 3, 0),VertexOrder(5, 7, 3),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 0, 2),VertexOrder(8, 2, 5),VertexOrder(8, 5, 7),VertexOrder(10, 5, 2),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 10, 5),VertexOrder(2, 5, 3),VertexOrder(3, 5, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(7, 9, 5),VertexOrder(7, 8, 9),VertexOrder(3, 11, 2),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 5, 7),VertexOrder(9, 7, 2),VertexOrder(9, 2, 0),VertexOrder(2, 7, 11),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 3, 11),VertexOrder(0, 1, 8),VertexOrder(1, 7, 8),VertexOrder(1, 5, 7),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(11, 2, 1),VertexOrder(11, 1, 7),VertexOrder(7, 1, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 5, 8),VertexOrder(8, 5, 7),VertexOrder(10, 1, 3),VertexOrder(10, 3, 11),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 7, 0),VertexOrder(5, 0, 9),VertexOrder(7, 11, 0),VertexOrder(1, 0, 10),VertexOrder(11, 10, 0)),
																VertexOrderCase(VertexOrder(11, 10, 0),VertexOrder(11, 0, 3),VertexOrder(10, 5, 0),VertexOrder(8, 0, 7),VertexOrder(5, 7, 0)),
																VertexOrderCase(VertexOrder(11, 10, 5),VertexOrder(7, 11, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 6, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 8, 3),VertexOrder(5, 10, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 0, 1),VertexOrder(5, 10, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 8, 3),VertexOrder(1, 9, 8),VertexOrder(5, 10, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 6, 5),VertexOrder(2, 6, 1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 6, 5),VertexOrder(1, 2, 6),VertexOrder(3, 0, 8),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 6, 5),VertexOrder(9, 0, 6),VertexOrder(0, 2, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 9, 8),VertexOrder(5, 8, 2),VertexOrder(5, 2, 6),VertexOrder(3, 2, 8),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 3, 11),VertexOrder(10, 6, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(11, 0, 8),VertexOrder(11, 2, 0),VertexOrder(10, 6, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 1, 9),VertexOrder(2, 3, 11),VertexOrder(5, 10, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 10, 6),VertexOrder(1, 9, 2),VertexOrder(9, 11, 2),VertexOrder(9, 8, 11),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(6, 3, 11),VertexOrder(6, 5, 3),VertexOrder(5, 1, 3),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 8, 11),VertexOrder(0, 11, 5),VertexOrder(0, 5, 1),VertexOrder(5, 11, 6),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 11, 6),VertexOrder(0, 3, 6),VertexOrder(0, 6, 5),VertexOrder(0, 5, 9),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(6, 5, 9),VertexOrder(6, 9, 11),VertexOrder(11, 9, 8),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 10, 6),VertexOrder(4, 7, 8),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 3, 0),VertexOrder(4, 7, 3),VertexOrder(6, 5, 10),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 9, 0),VertexOrder(5, 10, 6),VertexOrder(8, 4, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 6, 5),VertexOrder(1, 9, 7),VertexOrder(1, 7, 3),VertexOrder(7, 9, 4),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(6, 1, 2),VertexOrder(6, 5, 1),VertexOrder(4, 7, 8),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 2, 5),VertexOrder(5, 2, 6),VertexOrder(3, 0, 4),VertexOrder(3, 4, 7),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 4, 7),VertexOrder(9, 0, 5),VertexOrder(0, 6, 5),VertexOrder(0, 2, 6),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(7, 3, 9),VertexOrder(7, 9, 4),VertexOrder(3, 2, 9),VertexOrder(5, 9, 6),VertexOrder(2, 6, 9)),
																VertexOrderCase(VertexOrder(3, 11, 2),VertexOrder(7, 8, 4),VertexOrder(10, 6, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 10, 6),VertexOrder(4, 7, 2),VertexOrder(4, 2, 0),VertexOrder(2, 7, 11),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 1, 9),VertexOrder(4, 7, 8),VertexOrder(2, 3, 11),VertexOrder(5, 10, 6),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 2, 1),VertexOrder(9, 11, 2),VertexOrder(9, 4, 11),VertexOrder(7, 11, 4),VertexOrder(5, 10, 6)),
																VertexOrderCase(VertexOrder(8, 4, 7),VertexOrder(3, 11, 5),VertexOrder(3, 5, 1),VertexOrder(5, 11, 6),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 1, 11),VertexOrder(5, 11, 6),VertexOrder(1, 0, 11),VertexOrder(7, 11, 4),VertexOrder(0, 4, 11)),
																VertexOrderCase(VertexOrder(0, 5, 9),VertexOrder(0, 6, 5),VertexOrder(0, 3, 6),VertexOrder(11, 6, 3),VertexOrder(8, 4, 7)),
																VertexOrderCase(VertexOrder(6, 5, 9),VertexOrder(6, 9, 11),VertexOrder(4, 7, 9),VertexOrder(7, 11, 9),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 4, 9),VertexOrder(6, 4, 10),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 10, 6),VertexOrder(4, 9, 10),VertexOrder(0, 8, 3),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 0, 1),VertexOrder(10, 6, 0),VertexOrder(6, 4, 0),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 3, 1),VertexOrder(8, 1, 6),VertexOrder(8, 6, 4),VertexOrder(6, 1, 10),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 4, 9),VertexOrder(1, 2, 4),VertexOrder(2, 6, 4),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 0, 8),VertexOrder(1, 2, 9),VertexOrder(2, 4, 9),VertexOrder(2, 6, 4),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 2, 4),VertexOrder(4, 2, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 3, 2),VertexOrder(8, 2, 4),VertexOrder(4, 2, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 4, 9),VertexOrder(10, 6, 4),VertexOrder(11, 2, 3),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 8, 2),VertexOrder(2, 8, 11),VertexOrder(4, 9, 10),VertexOrder(4, 10, 6),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 11, 2),VertexOrder(0, 1, 6),VertexOrder(0, 6, 4),VertexOrder(6, 1, 10),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(6, 4, 1),VertexOrder(6, 1, 10),VertexOrder(4, 8, 1),VertexOrder(2, 1, 11),VertexOrder(8, 11, 1)),
																VertexOrderCase(VertexOrder(9, 6, 4),VertexOrder(9, 3, 6),VertexOrder(9, 1, 3),VertexOrder(11, 6, 3),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 11, 1),VertexOrder(8, 1, 0),VertexOrder(11, 6, 1),VertexOrder(9, 1, 4),VertexOrder(6, 4, 1)),
																VertexOrderCase(VertexOrder(3, 11, 6),VertexOrder(3, 6, 0),VertexOrder(0, 6, 4),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(6, 4, 8),VertexOrder(11, 6, 8),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(7, 10, 6),VertexOrder(7, 8, 10),VertexOrder(8, 9, 10),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 7, 3),VertexOrder(0, 10, 7),VertexOrder(0, 9, 10),VertexOrder(6, 7, 10),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 6, 7),VertexOrder(1, 10, 7),VertexOrder(1, 7, 8),VertexOrder(1, 8, 0),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 6, 7),VertexOrder(10, 7, 1),VertexOrder(1, 7, 3),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 2, 6),VertexOrder(1, 6, 8),VertexOrder(1, 8, 9),VertexOrder(8, 6, 7),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 6, 9),VertexOrder(2, 9, 1),VertexOrder(6, 7, 9),VertexOrder(0, 9, 3),VertexOrder(7, 3, 9)),
																VertexOrderCase(VertexOrder(7, 8, 0),VertexOrder(7, 0, 6),VertexOrder(6, 0, 2),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(7, 3, 2),VertexOrder(6, 7, 2),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 3, 11),VertexOrder(10, 6, 8),VertexOrder(10, 8, 9),VertexOrder(8, 6, 7),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 0, 7),VertexOrder(2, 7, 11),VertexOrder(0, 9, 7),VertexOrder(6, 7, 10),VertexOrder(9, 10, 7)),
																VertexOrderCase(VertexOrder(1, 8, 0),VertexOrder(1, 7, 8),VertexOrder(1, 10, 7),VertexOrder(6, 7, 10),VertexOrder(2, 3, 11)),
																VertexOrderCase(VertexOrder(11, 2, 1),VertexOrder(11, 1, 7),VertexOrder(10, 6, 1),VertexOrder(6, 7, 1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 9, 6),VertexOrder(8, 6, 7),VertexOrder(9, 1, 6),VertexOrder(11, 6, 3),VertexOrder(1, 3, 6)),
																VertexOrderCase(VertexOrder(0, 9, 1),VertexOrder(11, 6, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(7, 8, 0),VertexOrder(7, 0, 6),VertexOrder(3, 11, 0),VertexOrder(11, 6, 0),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(7, 11, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(7, 6, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 0, 8),VertexOrder(11, 7, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 1, 9),VertexOrder(11, 7, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 1, 9),VertexOrder(8, 3, 1),VertexOrder(11, 7, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 1, 2),VertexOrder(6, 11, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 2, 10),VertexOrder(3, 0, 8),VertexOrder(6, 11, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 9, 0),VertexOrder(2, 10, 9),VertexOrder(6, 11, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(6, 11, 7),VertexOrder(2, 10, 3),VertexOrder(10, 8, 3),VertexOrder(10, 9, 8),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(7, 2, 3),VertexOrder(6, 2, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(7, 0, 8),VertexOrder(7, 6, 0),VertexOrder(6, 2, 0),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 7, 6),VertexOrder(2, 3, 7),VertexOrder(0, 1, 9),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 6, 2),VertexOrder(1, 8, 6),VertexOrder(1, 9, 8),VertexOrder(8, 7, 6),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 7, 6),VertexOrder(10, 1, 7),VertexOrder(1, 3, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 7, 6),VertexOrder(1, 7, 10),VertexOrder(1, 8, 7),VertexOrder(1, 0, 8),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 3, 7),VertexOrder(0, 7, 10),VertexOrder(0, 10, 9),VertexOrder(6, 10, 7),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(7, 6, 10),VertexOrder(7, 10, 8),VertexOrder(8, 10, 9),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(6, 8, 4),VertexOrder(11, 8, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 6, 11),VertexOrder(3, 0, 6),VertexOrder(0, 4, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 6, 11),VertexOrder(8, 4, 6),VertexOrder(9, 0, 1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 4, 6),VertexOrder(9, 6, 3),VertexOrder(9, 3, 1),VertexOrder(11, 3, 6),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(6, 8, 4),VertexOrder(6, 11, 8),VertexOrder(2, 10, 1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 2, 10),VertexOrder(3, 0, 11),VertexOrder(0, 6, 11),VertexOrder(0, 4, 6),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 11, 8),VertexOrder(4, 6, 11),VertexOrder(0, 2, 9),VertexOrder(2, 10, 9),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 9, 3),VertexOrder(10, 3, 2),VertexOrder(9, 4, 3),VertexOrder(11, 3, 6),VertexOrder(4, 6, 3)),
																VertexOrderCase(VertexOrder(8, 2, 3),VertexOrder(8, 4, 2),VertexOrder(4, 6, 2),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 4, 2),VertexOrder(4, 6, 2),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 9, 0),VertexOrder(2, 3, 4),VertexOrder(2, 4, 6),VertexOrder(4, 3, 8),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 9, 4),VertexOrder(1, 4, 2),VertexOrder(2, 4, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 1, 3),VertexOrder(8, 6, 1),VertexOrder(8, 4, 6),VertexOrder(6, 10, 1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 1, 0),VertexOrder(10, 0, 6),VertexOrder(6, 0, 4),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 6, 3),VertexOrder(4, 3, 8),VertexOrder(6, 10, 3),VertexOrder(0, 3, 9),VertexOrder(10, 9, 3)),
																VertexOrderCase(VertexOrder(10, 9, 4),VertexOrder(6, 10, 4),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 9, 5),VertexOrder(7, 6, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 8, 3),VertexOrder(4, 9, 5),VertexOrder(11, 7, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 0, 1),VertexOrder(5, 4, 0),VertexOrder(7, 6, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(11, 7, 6),VertexOrder(8, 3, 4),VertexOrder(3, 5, 4),VertexOrder(3, 1, 5),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 5, 4),VertexOrder(10, 1, 2),VertexOrder(7, 6, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(6, 11, 7),VertexOrder(1, 2, 10),VertexOrder(0, 8, 3),VertexOrder(4, 9, 5),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(7, 6, 11),VertexOrder(5, 4, 10),VertexOrder(4, 2, 10),VertexOrder(4, 0, 2),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 4, 8),VertexOrder(3, 5, 4),VertexOrder(3, 2, 5),VertexOrder(10, 5, 2),VertexOrder(11, 7, 6)),
																VertexOrderCase(VertexOrder(7, 2, 3),VertexOrder(7, 6, 2),VertexOrder(5, 4, 9),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 5, 4),VertexOrder(0, 8, 6),VertexOrder(0, 6, 2),VertexOrder(6, 8, 7),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 6, 2),VertexOrder(3, 7, 6),VertexOrder(1, 5, 0),VertexOrder(5, 4, 0),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(6, 2, 8),VertexOrder(6, 8, 7),VertexOrder(2, 1, 8),VertexOrder(4, 8, 5),VertexOrder(1, 5, 8)),
																VertexOrderCase(VertexOrder(9, 5, 4),VertexOrder(10, 1, 6),VertexOrder(1, 7, 6),VertexOrder(1, 3, 7),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 6, 10),VertexOrder(1, 7, 6),VertexOrder(1, 0, 7),VertexOrder(8, 7, 0),VertexOrder(9, 5, 4)),
																VertexOrderCase(VertexOrder(4, 0, 10),VertexOrder(4, 10, 5),VertexOrder(0, 3, 10),VertexOrder(6, 10, 7),VertexOrder(3, 7, 10)),
																VertexOrderCase(VertexOrder(7, 6, 10),VertexOrder(7, 10, 8),VertexOrder(5, 4, 10),VertexOrder(4, 8, 10),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(6, 9, 5),VertexOrder(6, 11, 9),VertexOrder(11, 8, 9),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 6, 11),VertexOrder(0, 6, 3),VertexOrder(0, 5, 6),VertexOrder(0, 9, 5),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 11, 8),VertexOrder(0, 5, 11),VertexOrder(0, 1, 5),VertexOrder(5, 6, 11),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(6, 11, 3),VertexOrder(6, 3, 5),VertexOrder(5, 3, 1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 2, 10),VertexOrder(9, 5, 11),VertexOrder(9, 11, 8),VertexOrder(11, 5, 6),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 11, 3),VertexOrder(0, 6, 11),VertexOrder(0, 9, 6),VertexOrder(5, 6, 9),VertexOrder(1, 2, 10)),
																VertexOrderCase(VertexOrder(11, 8, 5),VertexOrder(11, 5, 6),VertexOrder(8, 0, 5),VertexOrder(10, 5, 2),VertexOrder(0, 2, 5)),
																VertexOrderCase(VertexOrder(6, 11, 3),VertexOrder(6, 3, 5),VertexOrder(2, 10, 3),VertexOrder(10, 5, 3),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 8, 9),VertexOrder(5, 2, 8),VertexOrder(5, 6, 2),VertexOrder(3, 8, 2),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 5, 6),VertexOrder(9, 6, 0),VertexOrder(0, 6, 2),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 5, 8),VertexOrder(1, 8, 0),VertexOrder(5, 6, 8),VertexOrder(3, 8, 2),VertexOrder(6, 2, 8)),
																VertexOrderCase(VertexOrder(1, 5, 6),VertexOrder(2, 1, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 3, 6),VertexOrder(1, 6, 10),VertexOrder(3, 8, 6),VertexOrder(5, 6, 9),VertexOrder(8, 9, 6)),
																VertexOrderCase(VertexOrder(10, 1, 0),VertexOrder(10, 0, 6),VertexOrder(9, 5, 0),VertexOrder(5, 6, 0),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 3, 8),VertexOrder(5, 6, 10),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 5, 6),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(11, 5, 10),VertexOrder(7, 5, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(11, 5, 10),VertexOrder(11, 7, 5),VertexOrder(8, 3, 0),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 11, 7),VertexOrder(5, 10, 11),VertexOrder(1, 9, 0),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 7, 5),VertexOrder(10, 11, 7),VertexOrder(9, 8, 1),VertexOrder(8, 3, 1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(11, 1, 2),VertexOrder(11, 7, 1),VertexOrder(7, 5, 1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 8, 3),VertexOrder(1, 2, 7),VertexOrder(1, 7, 5),VertexOrder(7, 2, 11),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 7, 5),VertexOrder(9, 2, 7),VertexOrder(9, 0, 2),VertexOrder(2, 11, 7),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(7, 5, 2),VertexOrder(7, 2, 11),VertexOrder(5, 9, 2),VertexOrder(3, 2, 8),VertexOrder(9, 8, 2)),
																VertexOrderCase(VertexOrder(2, 5, 10),VertexOrder(2, 3, 5),VertexOrder(3, 7, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 2, 0),VertexOrder(8, 5, 2),VertexOrder(8, 7, 5),VertexOrder(10, 2, 5),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 0, 1),VertexOrder(5, 10, 3),VertexOrder(5, 3, 7),VertexOrder(3, 10, 2),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 8, 2),VertexOrder(9, 2, 1),VertexOrder(8, 7, 2),VertexOrder(10, 2, 5),VertexOrder(7, 5, 2)),
																VertexOrderCase(VertexOrder(1, 3, 5),VertexOrder(3, 7, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 8, 7),VertexOrder(0, 7, 1),VertexOrder(1, 7, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 0, 3),VertexOrder(9, 3, 5),VertexOrder(5, 3, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 8, 7),VertexOrder(5, 9, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 8, 4),VertexOrder(5, 10, 8),VertexOrder(10, 11, 8),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 0, 4),VertexOrder(5, 11, 0),VertexOrder(5, 10, 11),VertexOrder(11, 3, 0),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 1, 9),VertexOrder(8, 4, 10),VertexOrder(8, 10, 11),VertexOrder(10, 4, 5),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(10, 11, 4),VertexOrder(10, 4, 5),VertexOrder(11, 3, 4),VertexOrder(9, 4, 1),VertexOrder(3, 1, 4)),
																VertexOrderCase(VertexOrder(2, 5, 1),VertexOrder(2, 8, 5),VertexOrder(2, 11, 8),VertexOrder(4, 5, 8),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 4, 11),VertexOrder(0, 11, 3),VertexOrder(4, 5, 11),VertexOrder(2, 11, 1),VertexOrder(5, 1, 11)),
																VertexOrderCase(VertexOrder(0, 2, 5),VertexOrder(0, 5, 9),VertexOrder(2, 11, 5),VertexOrder(4, 5, 8),VertexOrder(11, 8, 5)),
																VertexOrderCase(VertexOrder(9, 4, 5),VertexOrder(2, 11, 3),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 5, 10),VertexOrder(3, 5, 2),VertexOrder(3, 4, 5),VertexOrder(3, 8, 4),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(5, 10, 2),VertexOrder(5, 2, 4),VertexOrder(4, 2, 0),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 10, 2),VertexOrder(3, 5, 10),VertexOrder(3, 8, 5),VertexOrder(4, 5, 8),VertexOrder(0, 1, 9)),
																VertexOrderCase(VertexOrder(5, 10, 2),VertexOrder(5, 2, 4),VertexOrder(1, 9, 2),VertexOrder(9, 4, 2),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 4, 5),VertexOrder(8, 5, 3),VertexOrder(3, 5, 1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 4, 5),VertexOrder(1, 0, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(8, 4, 5),VertexOrder(8, 5, 3),VertexOrder(9, 0, 5),VertexOrder(0, 3, 5),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 4, 5),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 11, 7),VertexOrder(4, 9, 11),VertexOrder(9, 10, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 8, 3),VertexOrder(4, 9, 7),VertexOrder(9, 11, 7),VertexOrder(9, 10, 11),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 10, 11),VertexOrder(1, 11, 4),VertexOrder(1, 4, 0),VertexOrder(7, 4, 11),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 1, 4),VertexOrder(3, 4, 8),VertexOrder(1, 10, 4),VertexOrder(7, 4, 11),VertexOrder(10, 11, 4)),
																VertexOrderCase(VertexOrder(4, 11, 7),VertexOrder(9, 11, 4),VertexOrder(9, 2, 11),VertexOrder(9, 1, 2),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 7, 4),VertexOrder(9, 11, 7),VertexOrder(9, 1, 11),VertexOrder(2, 11, 1),VertexOrder(0, 8, 3)),
																VertexOrderCase(VertexOrder(11, 7, 4),VertexOrder(11, 4, 2),VertexOrder(2, 4, 0),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(11, 7, 4),VertexOrder(11, 4, 2),VertexOrder(8, 3, 4),VertexOrder(3, 2, 4),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 9, 10),VertexOrder(2, 7, 9),VertexOrder(2, 3, 7),VertexOrder(7, 4, 9),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 10, 7),VertexOrder(9, 7, 4),VertexOrder(10, 2, 7),VertexOrder(8, 7, 0),VertexOrder(2, 0, 7)),
																VertexOrderCase(VertexOrder(3, 7, 10),VertexOrder(3, 10, 2),VertexOrder(7, 4, 10),VertexOrder(1, 10, 0),VertexOrder(4, 0, 10)),
																VertexOrderCase(VertexOrder(1, 10, 2),VertexOrder(8, 7, 4),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 9, 1),VertexOrder(4, 1, 7),VertexOrder(7, 1, 3),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 9, 1),VertexOrder(4, 1, 7),VertexOrder(0, 8, 1),VertexOrder(8, 7, 1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 0, 3),VertexOrder(7, 4, 3),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(4, 8, 7),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 10, 8),VertexOrder(10, 11, 8),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 0, 9),VertexOrder(3, 9, 11),VertexOrder(11, 9, 10),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 1, 10),VertexOrder(0, 10, 8),VertexOrder(8, 10, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 1, 10),VertexOrder(11, 3, 10),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 2, 11),VertexOrder(1, 11, 9),VertexOrder(9, 11, 8),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 0, 9),VertexOrder(3, 9, 11),VertexOrder(1, 2, 9),VertexOrder(2, 11, 9),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 2, 11),VertexOrder(8, 0, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(3, 2, 11),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 3, 8),VertexOrder(2, 8, 10),VertexOrder(10, 8, 9),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(9, 10, 2),VertexOrder(0, 9, 2),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(2, 3, 8),VertexOrder(2, 8, 10),VertexOrder(0, 1, 8),VertexOrder(1, 10, 8),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 10, 2),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(1, 3, 8),VertexOrder(9, 1, 8),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 9, 1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(0, 3, 8),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1)),
																VertexOrderCase(VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1),VertexOrder(-1, -1, -1))
															};

float TerrainUtility::interpolate(ci::Vec2f& position, ci::Vec2f& vertex00, ci::Vec2f& vertex11, float value00, float value10, float value01, float value11)
{
	float x0 = vertex00.x;
	float y0 = vertex00.y;
	
	float x1 = vertex11.x;
	float y1 = vertex11.y;

	float x = position.x;
	float y = position.y;

	float nx = x1 - x0;
	float ny = y1 - y0;

	float x1mx = x1 - x;
	float xmx0 = x - x0;

	float y1my = y1 - y;
	float ymy0 = y - y0;

	float result = (x1mx/nx) * (y1my/ny) * value00 +
					(xmx0/nx) * (y1my/ny) * value10 +
					(x1mx/nx) * (ymy0/ny) * value01 +
					(xmx0/nx) * (ymy0/ny) * value11;

	float a = value00 - value10 - value01 + value11;
	float b = value01 - value00;
	float c = value10 - value00;
	float d = value00;

	float xFoo = (x - x0) / (x1 - x0);
	float yFoo = (y - y0) / (y1 - y0);

	float result1 = a*xFoo*yFoo + b*yFoo + c*xFoo + d;

	return result;
}

float TerrainUtility::interpolate(ci::Vec3f& position, ci::Vec3f& vertex000, ci::Vec3f& vertex111, CubeCornerValues& cubeCornerValues)
{
	float x0 = vertex000.x;
	float y0 = vertex000.y;
	float z0 = vertex000.z;

	float x1 = vertex111.x;
	float y1 = vertex111.y;
	float z1 = vertex111.z;

	float x = position.x;
	float y = position.y;
	float z = position.z;

	float nx = x1 - x0;
	float ny = y1 - y0;
	float nz = z1 - z0;

	float x1mx = x1 - x;
	float y1my = y1 - y;
	float z1mz = z1 - z;

	float xmx0 = x - x0;
	float ymy0 = y - y0;
	float zmz0 = z - z0;

	float x1mx_nx = x1mx/nx;
	float xmx0_nx = xmx0/nx;

	float y1my_ny = y1my/ny;
	float ymy0_ny = ymy0/ny;

	float z1mz_nz = z1mz/nz;
	float zmz0_nz = zmz0/nz;

	float result = x1mx_nx * y1my_ny * z1mz_nz * cubeCornerValues.m_value0 +
					x1mx_nx * ymy0_ny * z1mz_nz * cubeCornerValues.m_value1 +
					xmx0_nx * ymy0_ny * z1mz_nz * cubeCornerValues.m_value2 +
					xmx0_nx * y1my_ny * z1mz_nz * cubeCornerValues.m_value3 +
					x1mx_nx * y1my_ny * zmz0_nz * cubeCornerValues.m_value4 +
					x1mx_nx * ymy0_ny * zmz0_nz * cubeCornerValues.m_value5 +
					xmx0_nx * ymy0_ny * zmz0_nz * cubeCornerValues.m_value6 +
					xmx0_nx * y1my_ny * zmz0_nz * cubeCornerValues.m_value7;

	float a = cubeCornerValues.m_value6 - cubeCornerValues.m_value2 - cubeCornerValues.m_value7 - cubeCornerValues.m_value5 + cubeCornerValues.m_value3 + cubeCornerValues.m_value1 + cubeCornerValues.m_value4 - cubeCornerValues.m_value0;
	float b = cubeCornerValues.m_value2 - cubeCornerValues.m_value3 - cubeCornerValues.m_value1 + cubeCornerValues.m_value0;
	float c = cubeCornerValues.m_value5 - cubeCornerValues.m_value1 - cubeCornerValues.m_value4 + cubeCornerValues.m_value0;
	float d = cubeCornerValues.m_value7 - cubeCornerValues.m_value3 - cubeCornerValues.m_value4 + cubeCornerValues.m_value0;
	float e = cubeCornerValues.m_value3 - cubeCornerValues.m_value0;
	float f = cubeCornerValues.m_value1 - cubeCornerValues.m_value0;
	float g = cubeCornerValues.m_value4 - cubeCornerValues.m_value0;
	float h = cubeCornerValues.m_value0;

	float xFoo = (x - x0) / (x1 - x0);
	float yFoo = (y - y0) / (y1 - y0);
	float zFoo = (z - z0) / (z1 - z0);

	float result2 = a*xFoo*yFoo*zFoo + b*xFoo*yFoo + c*yFoo*zFoo + d*xFoo*zFoo + e*xFoo + f*yFoo + g*zFoo + h;

	//float result3 = (1.0f - x)(1.0f - y)(1.0f - z)

	return result;
}

ci::Vec2f TerrainUtility::calculateFaceSaddlePoint(ci::Vec2f& vertex00, ci::Vec2f& vertex11, float value00, float value10, float value01, float value11)
{
	float a = value00 - value10 - value01 + value11;
	float b = value01 - value00;
	float c = value10 - value00;
	float d = value00;

	float x = a + c;
	float y = a + b;

	return ci::Vec2f(x, y);
}

std::vector<ci::Vec3f> TerrainUtility::calculateBodySaddlePoints(ci::Vec3f& vertex000, ci::Vec3f& vertex111, CubeCornerValues& cubeCornerValues)
{
	std::vector<ci::Vec3f> result;

	float a = cubeCornerValues.m_value6 - cubeCornerValues.m_value2 - cubeCornerValues.m_value7 - cubeCornerValues.m_value5 + cubeCornerValues.m_value3 + cubeCornerValues.m_value1 + cubeCornerValues.m_value4 - cubeCornerValues.m_value0;
	float b = cubeCornerValues.m_value2 - cubeCornerValues.m_value3 - cubeCornerValues.m_value1 + cubeCornerValues.m_value0;
	float c = cubeCornerValues.m_value5 - cubeCornerValues.m_value1 - cubeCornerValues.m_value4 + cubeCornerValues.m_value0;
	float d = cubeCornerValues.m_value7 - cubeCornerValues.m_value3 - cubeCornerValues.m_value4 + cubeCornerValues.m_value0;
	float e = cubeCornerValues.m_value3 - cubeCornerValues.m_value0;
	float f = cubeCornerValues.m_value1 - cubeCornerValues.m_value0;
	float g = cubeCornerValues.m_value4 - cubeCornerValues.m_value0;
	float h = cubeCornerValues.m_value0;

	if((0.0f - std::abs(a)) > -0.00000001f)
		return result;

	float ax = a*e - c*d;
	float ay = a*f - b*d;
	float az = a*g - b*c;

	float xSquare = -(ay*az)/ax;
	float ySquare = -(ax*az)/ay;
	float zSquare = -(ax*ay)/az;

	if(xSquare < 0.0f || ySquare < 0.0f || zSquare < 0.0f)
		return result;

	float x0 = (1.0f/a) * std::sqrt(xSquare);
	float y0 = (1.0f/a) * std::sqrt(ySquare);
	float z0 = (1.0f/a) * std::sqrt(zSquare);

	ci::Vec3f v(x0, y0, z0);
	ci::Vec3f m((1.0f/a)*-c, (1.0f/a)*-d, (1.0f/a)*-b);
	ci::Vec3f s0 = m - v;
	ci::Vec3f s1 = m + v;

	//if(s0.x != 
	result.push_back(s0);
	result.push_back(s1);

	return result;
}