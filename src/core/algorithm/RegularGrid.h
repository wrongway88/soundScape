#ifndef REGULAR_GRID_H
#define REGULAR_GRID_H

#include <vector>

#include "core/math/VectorBase.h"
#include "core/utility/logging/logging.h"

template <class T, unsigned int N>
class RegularGrid
{
public:
	RegularGrid();
	~RegularGrid();

	void setGridSideLength(const float sideLength);
	void setCellsPerDimension(const unsigned int cellsPerDimension);

	void addValue(const VectorBase<float, N>& position, const T& value);
	std::vector<std::vector<T>> getCells(const VectorBase<float, N>& position, const unsigned int nNeighbourhood) const;

	void setCenter(const VectorBase<float, N>& center);
	VectorBase<float, N> getCenter() const;

	void clearCells();

private:
	void initCells();

	bool getCellIndexByPosition(const VectorBase<float, N>& position, unsigned int& index) const;
	bool getCellIndexPerDimensionByPosition(const VectorBase<float, N>& position, VectorBase<unsigned int, N>& index) const;
	bool getCellIndexByDimensionWiseIndex(const VectorBase<unsigned int, N>& indexByDimension, unsigned int& index) const;

	void updateCellSize();

	float m_sideLength;
	float m_cellSize;
	unsigned int m_cellsPerDimension;

	std::vector<std::vector<T>> m_cells;
	VectorBase<float, N> m_center;
};

template <class T, unsigned int N>
RegularGrid<T, N>::RegularGrid()
	: m_sideLength(1.0f)
	, m_cellSize(1.0f)
	, m_cellsPerDimension(1)
	, m_cells()
{
	
}

template <class T, unsigned int N>
RegularGrid<T, N>::~RegularGrid()
{

}

template <class T, unsigned int N>
void RegularGrid<T, N>::setGridSideLength(const float sideLength)
{
	m_sideLength = sideLength;

	updateCellSize();
}

template <class T, unsigned int N>
void RegularGrid<T, N>::setCellsPerDimension(const unsigned int cellsPerDimension)
{
	m_cellsPerDimension = cellsPerDimension;

	updateCellSize();

	initCells();
}

template <class T, unsigned int N>
void RegularGrid<T, N>::addValue(const VectorBase<float, N>& position, const T& value)
{
	unsigned int cellIndex;

	if (getCellIndexByPosition(position - m_center, cellIndex))
	{
		m_cells[cellIndex].push_back(value);
	}
}

template <class T, unsigned int N>
std::vector<std::vector<T>> RegularGrid<T, N>::getCells(const VectorBase<float, N>& position, const unsigned int nNeighbourhood) const
{
	std::vector<std::vector<T>> result;

	VectorBase<unsigned int, N> dimIndex;
	if (getCellIndexPerDimensionByPosition(position - m_center, dimIndex))
	{
		unsigned int cellIndex;
		if (getCellIndexByDimensionWiseIndex(dimIndex, cellIndex))
		{
			VectorBase<unsigned int, N> startPos;
			VectorBase<unsigned int, N> endPos;
			for (unsigned int i = 0; i < N; i++)
			{
				int a = ((int)dimIndex[i] - (int)nNeighbourhood);
				int b = ((int)dimIndex[i] + (int)nNeighbourhood);

				startPos.setValue(i, std::max(a, 0));
				endPos.setValue(i, std::min(b, (int)m_cellsPerDimension-1));
			}

			
			GridIterator<T, N, N-1> iterator(m_cells, m_cellsPerDimension);
			iterator.getNeighbourCells(result, startPos, endPos, startPos);
		}
	}

	return result;
}

template <class T, unsigned int N>
void RegularGrid<T, N>::setCenter(const VectorBase<float, N>& center)
{
	m_center = center;
}

template <class T, unsigned int N>
VectorBase<float, N> RegularGrid<T, N>::getCenter() const
{
	return m_center;
}

template <class T, unsigned int N>
void RegularGrid<T, N>::clearCells()
{
	initCells();
}

template <class T, unsigned int N>
void RegularGrid<T, N>::initCells()
{
	unsigned int cellCount = std::pow(m_cellsPerDimension, N);

	m_cells.clear();

	for (unsigned int i = 0; i < cellCount; i++)
	{
		m_cells.push_back(std::vector<T>());
	}
}

template <class T, unsigned int N>
bool RegularGrid<T, N>::getCellIndexByPosition(const VectorBase<float, N>& position, unsigned int& index) const
{
	index = 0;

	for (unsigned int i = 0; i < N; i++)
	{
		float dimPos = position.getValue(i) + (m_sideLength * 0.5f);

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

template <class T, unsigned int N>
bool RegularGrid<T, N>::getCellIndexPerDimensionByPosition(const VectorBase<float, N>& position, VectorBase<unsigned int, N>& index) const
{
	for (unsigned int i = 0; i < N; i++)
	{
		index.setValue(i, 0);
	}

	for (unsigned int i = 0; i < N; i++)
	{
		float dimPos = position.getValue(i) + (m_sideLength * 0.5f);

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

		index.setValue(i, dimCellIndex);
	}

	return true;
}

template <class T, unsigned int N>
bool RegularGrid<T, N>::getCellIndexByDimensionWiseIndex(const VectorBase<unsigned int, N>& indexByDimension, unsigned int& index) const
{
	index = 0;

	for (unsigned int i = 0; i < N; i++)
	{
		unsigned int dimIndex = indexByDimension.getValue(i);

		if (dimIndex >= m_cellsPerDimension)
		{
			return false;
		}

		index += (dimIndex * std::pow(m_cellsPerDimension, i));
	}

	return true;
}

template <class T, unsigned int N>
void RegularGrid<T, N>::updateCellSize()
{
	m_cellSize = m_sideLength / (float)m_cellsPerDimension;
}

template<class T, unsigned int N, unsigned int IT_LEVEL>
struct GridIterator
{
public:
	GridIterator(const std::vector<std::vector<T>>& cells, const unsigned int cellsPerDimension)
		: m_cells(cells)
		, m_cellsPerDimension(cellsPerDimension)
	{

	}

	void getNeighbourCells(std::vector<std::vector<T>>& cells, const VectorBase<unsigned int, N>& startIndex, const VectorBase<unsigned int, N>& endIndex, VectorBase<unsigned int, N> currentIndex)
	{
		for (unsigned int i = startIndex.getValue(IT_LEVEL); i <= endIndex.getValue(IT_LEVEL); i++)
		{
			GridIterator<T, N, IT_LEVEL-1> iterator(m_cells, m_cellsPerDimension); //getNeighbourCells<IT_LEVEL - 1>(neighbourCells, startIndex, endIndex, currentVolume + volume);
			currentIndex.setValue(IT_LEVEL, i);
			iterator.getNeighbourCells(cells, startIndex, endIndex, currentIndex);
		}
	}

	const std::vector<std::vector<T>>& m_cells;
	const unsigned int m_cellsPerDimension;
};

template<class T, unsigned int N>
struct GridIterator<T, N, 0>
{
public:
	GridIterator(const std::vector<std::vector<T>>& cells, const unsigned int cellsPerDimension)
		: m_cells(cells)
		, m_cellsPerDimension(cellsPerDimension)
	{

	}

	void getNeighbourCells(std::vector<std::vector<T>>& cells, const VectorBase<unsigned int, N>& startIndex, const VectorBase<unsigned int, N>& endIndex, VectorBase<unsigned int, N> currentIndex)
	{
		for (unsigned int i = startIndex.getValue(0); i <= endIndex.getValue(0); i++)
		{
			currentIndex.setValue(0, i);

			unsigned int index = 0;

			// calculate index
			for (unsigned int i = 0; i < N; i++)
			{
				unsigned int dimIndex = currentIndex.getValue(i);

				index += (dimIndex * std::pow(m_cellsPerDimension, i));
			}

			// LOG_WARNING_STREAM(<< "pushing " << index);

			cells.push_back(m_cells[index]);
		}
	}

	const std::vector<std::vector<T>>& m_cells;
	const unsigned int m_cellsPerDimension;
};

#endif // REGULAR_GRID_H