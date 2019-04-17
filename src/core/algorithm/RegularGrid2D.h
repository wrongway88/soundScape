#ifndef REGULAR_GRID_2_D_H
#define REGULAR_GRID_2_D_H

#include "cinder/Vector.h"

template <class T>
class RegularGrid2D
{
public:
	RegularGrid2D();
	~RegularGrid2D();

	void setGridSideLength(const float sideLength);
	void setCellsPerDimension(const unsigned int cellsPerDimension);

	void addValue(const ci::Vec2f& position, const T& value);
	std::vector<std::vector<T>> getCells(const ci::Vec2f& position, const unsigned int nNeighbourhood) const;

	void setCenter(const ci::Vec2f& center);
	ci::Vec2f getCenter() const;

	void clearCells();

	unsigned int getMaxTrianglePerCell() const;
	unsigned int getMinTrianglePerCell() const;

private:
	void initCells();

	bool getCellIndexByPosition(const ci::Vec2f& position, unsigned int& index) const;
	bool getCellIndexPerDimensionByPosition(const ci::Vec2f& position, ci::Vec2i& index) const;
	bool getCellIndexByDimensionWiseIndex(const ci::Vec2i& indexByDimension, unsigned int& index) const;

	void updateCellSize();

	float m_sideLength;
	float m_cellSize;
	unsigned int m_cellsPerDimension;

	std::vector<std::vector<T>> m_cells;
	ci::Vec2f m_center;

	unsigned int m_maxTrianglePerCell;
	unsigned int m_minTrianglePerCell;
};

template <class T>
RegularGrid2D<T>::RegularGrid2D()
	: m_sideLength(1.0f)
	, m_cellSize(1.0f)
	, m_cellsPerDimension(1)
	, m_cells()
	, m_center(0.0f, 0.0f)
	, m_maxTrianglePerCell(0)
	, m_minTrianglePerCell(-1)
{

}

template <class T>
RegularGrid2D<T>::~RegularGrid2D()
{

}

template <class T>
void RegularGrid2D<T>::setGridSideLength(const float sideLength)
{
	m_sideLength = sideLength;

	updateCellSize();
}

template <class T>
void RegularGrid2D<T>::setCellsPerDimension(const unsigned int cellsPerDimension)
{
	m_cellsPerDimension = cellsPerDimension;

	updateCellSize();

	initCells();
}

template <class T>
void RegularGrid2D<T>::addValue(const ci::Vec2f& position, const T& value)
{
	unsigned int cellIndex;

	if (getCellIndexByPosition(position - m_center, cellIndex))
	{
		if (cellIndex < m_cells.size())
		{
			m_cells[cellIndex].push_back(value);

			if (m_cells[cellIndex].size() > m_maxTrianglePerCell)
			{
				m_maxTrianglePerCell = m_cells[cellIndex].size();
			}
			if (m_cells[cellIndex].size() < m_minTrianglePerCell)
			{
				m_minTrianglePerCell = m_cells[cellIndex].size();
			}
		}
	}
}

template <class T>
std::vector<std::vector<T>> RegularGrid2D<T>::getCells(const ci::Vec2f& position, const unsigned int nNeighbourhood) const
{
	std::vector<std::vector<T>> result;

	ci::Vec2i dimIndex;
	if (getCellIndexPerDimensionByPosition(position - m_center, dimIndex))
	{
		unsigned int cellIndex;
		if (getCellIndexByDimensionWiseIndex(dimIndex, cellIndex))
		{
			ci::Vec2i startPos;
			ci::Vec2i endPos;

			startPos.x = std::max(dimIndex.x - (int)nNeighbourhood, 0);
			startPos.y = std::max(dimIndex.y - (int)nNeighbourhood, 0);

			endPos.x = std::min(dimIndex.x + (int)nNeighbourhood, (int)m_cellsPerDimension - 1);
			endPos.y = std::min(dimIndex.y + (int)nNeighbourhood, (int)m_cellsPerDimension - 1);

			for (unsigned int x = startPos.x; x < endPos.x+1; x++)
			{
				for (unsigned int y = startPos.y; y < endPos.y+1; y++)
				{
					unsigned int idx = 0;
					getCellIndexByDimensionWiseIndex(ci::Vec2i(x, y), idx);

					result.push_back(m_cells[idx]);
				}
			}
		}
	}

	return result;
}

template <class T>
void RegularGrid2D<T>::setCenter(const ci::Vec2f& center)
{
	m_center = center;
}

template <class T>
ci::Vec2f RegularGrid2D<T>::getCenter() const
{
	return m_center;
}

template <class T>
void RegularGrid2D<T>::clearCells()
{
	initCells();

	m_maxTrianglePerCell = 0;
	m_minTrianglePerCell = -1;
}

template <class T>
unsigned int RegularGrid2D<T>::getMaxTrianglePerCell() const
{
	return m_maxTrianglePerCell;
}

template <class T>
unsigned int RegularGrid2D<T>::getMinTrianglePerCell() const
{
	return m_minTrianglePerCell;
}

template <class T>
void RegularGrid2D<T>::initCells()
{
	unsigned int cellCount = std::pow(m_cellsPerDimension, 2);

	m_cells.clear();

	for (unsigned int i = 0; i < cellCount; i++)
	{
		m_cells.push_back(std::vector<T>());
	}
}

template <class T>
bool RegularGrid2D<T>::getCellIndexByPosition(const ci::Vec2f& position, unsigned int& index) const
{
	index = 0;

	for (unsigned int i = 0; i < 2; i++)
	{
		float dimPos = position[i] + (m_sideLength * 0.5f);

		if (dimPos < 0.0f || dimPos > m_sideLength)
		{
			return false;
		}

		unsigned int dimCellIndex = 0;

		while (dimPos > m_cellSize && dimCellIndex < m_cellsPerDimension)
		{
			dimPos -= m_cellSize;
			++dimCellIndex;
		}

		index += (dimCellIndex * std::pow(m_cellsPerDimension, i));
	}

	return true;
}

template <class T>
bool RegularGrid2D<T>::getCellIndexPerDimensionByPosition(const ci::Vec2f& position, ci::Vec2i& index) const
{
	index = ci::Vec2i(0, 0);

	for (unsigned int i = 0; i < 2; i++)
	{
		float dimPos = position[i] + (m_sideLength * 0.5f);

		if (dimPos < 0.0f || dimPos > m_sideLength)
		{
			return false;
		}

		unsigned int dimCellIndex = 0;

		while (dimPos > m_cellSize && dimCellIndex < m_cellsPerDimension)
		{
			dimPos -= m_cellSize;
			++dimCellIndex;
		}

		index[i] = dimCellIndex;
	}

	return true;
}

template <class T>
bool RegularGrid2D<T>::getCellIndexByDimensionWiseIndex(const ci::Vec2i& indexByDimension, unsigned int& index) const
{
	index = 0;

	for (unsigned int i = 0; i < 2; i++)
	{
		unsigned int dimIndex = indexByDimension[i];

		if (dimIndex >= m_cellsPerDimension)
		{
			return false;
		}

		index += (dimIndex * std::pow(m_cellsPerDimension, i));
	}

	return true;
}

template <class T>
void RegularGrid2D<T>::updateCellSize()
{
	m_cellSize = m_sideLength / (float)m_cellsPerDimension;
}

#endif // REGULAR_GRID_2_D_H