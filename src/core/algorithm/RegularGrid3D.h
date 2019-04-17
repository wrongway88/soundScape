#ifndef REGULAR_GRID_3_D_H
#define REGULAR_GRID_3_D_H

#include "cinder/Vector.h"

template <class T>
class RegularGrid3D
{
public:
	RegularGrid3D();
	~RegularGrid3D();

	void setGridSideLength(const float sideLength);
	void setCellsPerDimension(const unsigned int cellsPerDimension);

	void addValue(const ci::Vec3f& position, const T& value);
	std::vector<std::vector<T>> getCells(const ci::Vec3f& position, const unsigned int nNeighbourhood) const;

	std::vector<std::vector<T>> getHorizontalSlices() const;

	void setCenter(const ci::Vec3f& center);
	ci::Vec3f getCenter() const;

	void clearCells();

private:
	void initCells();

	bool getCellIndexByPosition(const ci::Vec3f& position, unsigned int& index) const;
	bool getCellIndexPerDimensionByPosition(const ci::Vec3f& position, ci::Vec3i& index) const;
	bool getCellIndexByDimensionWiseIndex(const ci::Vec3i& indexByDimension, unsigned int& index) const;

	void updateCellSize();

	float m_sideLength;
	float m_cellSize;
	unsigned int m_cellsPerDimension;

	std::vector<std::vector<T>> m_cells;
	ci::Vec3f m_center;
};

template <class T>
RegularGrid3D<T>::RegularGrid3D()
: m_sideLength(1.0f)
, m_cellSize(1.0f)
, m_cellsPerDimension(1)
, m_cells()
, m_center(0.0f, 0.0f, 0.0f)
{

}

template <class T>
RegularGrid3D<T>::~RegularGrid3D()
{

}

template <class T>
void RegularGrid3D<T>::setGridSideLength(const float sideLength)
{
	m_sideLength = sideLength;

	updateCellSize();
}

template <class T>
void RegularGrid3D<T>::setCellsPerDimension(const unsigned int cellsPerDimension)
{
	m_cellsPerDimension = cellsPerDimension;

	updateCellSize();

	initCells();
}

template <class T>
void RegularGrid3D<T>::addValue(const ci::Vec3f& position, const T& value)
{
	unsigned int cellIndex;

	if (getCellIndexByPosition(position - m_center, cellIndex) && cellIndex < m_cells.size())
	{
		m_cells[cellIndex].push_back(value);
	}
}

template <class T>
std::vector<std::vector<T>> RegularGrid3D<T>::getCells(const ci::Vec3f& position, const unsigned int nNeighbourhood) const
{
	std::vector<std::vector<T>> result;

	ci::Vec3i dimIndex;
	if (getCellIndexPerDimensionByPosition(position - m_center, dimIndex))
	{
		unsigned int cellIndex;
		if (getCellIndexByDimensionWiseIndex(dimIndex, cellIndex))
		{
			ci::Vec3i startPos;
			ci::Vec3i endPos;

			startPos.x = std::max(dimIndex.x - (int)nNeighbourhood, 0);
			startPos.y = std::max(dimIndex.y - (int)nNeighbourhood, 0);
			startPos.z = std::max(dimIndex.z - (int)nNeighbourhood, 0);

			endPos.x = std::min(dimIndex.x + (int)nNeighbourhood, (int)m_cellsPerDimension - 1);
			endPos.y = std::min(dimIndex.y + (int)nNeighbourhood, (int)m_cellsPerDimension - 1);
			endPos.z = std::min(dimIndex.z + (int)nNeighbourhood, (int)m_cellsPerDimension - 1);

			for (unsigned int x = startPos.x; x < endPos.x + 1; x++)
			{
				for (unsigned int y = startPos.y; y < endPos.y + 1; y++)
				{
					for (unsigned int z = startPos.z; z < endPos.z + 1; z++)
					{
						unsigned int idx = 0;
						getCellIndexByDimensionWiseIndex(ci::Vec3i(x, y, z), idx);

						result.push_back(m_cells[idx]);
					}
				}
			}
		}
	}

	return result;
}

template <class T>
std::vector<std::vector<T>> RegularGrid3D<T>::getHorizontalSlices() const
{
	std::vector<std::vector<T>> slices;

	for (unsigned int y = 0; y < m_cellsPerDimension; y++)
	{
		std::vector<T> slice;

		for (unsigned int x = 0; x < m_cellsPerDimension; x++)
		{
			for (unsigned int z = 0; z < m_cellsPerDimension; z++)
			{
				unsigned int idx = 0;
				getCellIndexByDimensionWiseIndex(ci::Vec3i(x, y, z), idx);

				for (unsigned int i = 0; i < m_cells[idx].size(); i++)
				{
					slice.push_back(m_cells[idx][i]);
				}
			}
		}

		slices.push_back(slice);
	}

	return slices;
}

template <class T>
void RegularGrid3D<T>::setCenter(const ci::Vec3f& center)
{
	m_center = center;
}

template <class T>
ci::Vec3f RegularGrid3D<T>::getCenter() const
{
	return m_center;
}

template <class T>
void RegularGrid3D<T>::clearCells()
{
	initCells();
}

template <class T>
void RegularGrid3D<T>::initCells()
{
	unsigned int cellCount = std::pow(m_cellsPerDimension, 3);

	m_cells.clear();

	for (unsigned int i = 0; i < cellCount; i++)
	{
		m_cells.push_back(std::vector<T>());
	}
}

template <class T>
bool RegularGrid3D<T>::getCellIndexByPosition(const ci::Vec3f& position, unsigned int& index) const
{
	index = 0;

	for (unsigned int i = 0; i < 3; i++)
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
bool RegularGrid3D<T>::getCellIndexPerDimensionByPosition(const ci::Vec3f& position, ci::Vec3i& index) const
{
	index = ci::Vec3i(0, 0, 0);

	for (unsigned int i = 0; i < 3; i++)
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
bool RegularGrid3D<T>::getCellIndexByDimensionWiseIndex(const ci::Vec3i& indexByDimension, unsigned int& index) const
{
	index = 0;

	for (unsigned int i = 0; i < 3; i++)
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
void RegularGrid3D<T>::updateCellSize()
{
	m_cellSize = m_sideLength / (float)m_cellsPerDimension;
}

#endif // REGULAR_GRID_3_D_H