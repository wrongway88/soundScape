#ifndef STL_VECTOR_UTILITY_H
#define STL_VECTOR_UTILITY_H

#include <vector>

class StlVectorUtility
{
public:
	template <class T>
	static int find(const std::vector<T>& vector, T value)
	{
		std::vector<T>::const_iterator it = std::find(vector.begin(), vector.end(), value);
	
		if(it != vector.end())
		{
			for(int i = 0; i < (int)vector.size(); i++)
			{
				if(vector[i] == *it)
				{
					return i;
				}
			}
		}
		return -1;
	}
};

#endif