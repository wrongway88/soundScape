#ifndef VECTOR_UTILITY_H
#define VECTOR_UTILITY_H

#include "cinder/Vector.h"

#include "VectorBase.h"

class VectorUtility
{
public:
	static ci::Vec3f convert(const VectorBase<float, 3>& vector);
	static VectorBase<float, 3> convert(const ci::Vec3f& vector);
	static ci::Vec2f convert(const VectorBase<float, 2>& vector);
	static VectorBase<float, 2> convert(const ci::Vec2f& vector);

	static ci::Vec3i convert(const VectorBase<int, 3>& vector);
	static VectorBase<int, 3> convert(const ci::Vec3i& vector);
	static ci::Vec2i convert(const VectorBase<int, 2>& vector);
	static VectorBase<int, 2> convert(const ci::Vec2i& vector);

	static ci::Vec2f projectXZ(const ci::Vec3f& vector);
	static ci::Vec2i projectXZ(const ci::Vec3i& vector);

	static VectorBase<float, 2> projectXZ(const VectorBase<float, 3>& vector);
	static VectorBase<int, 2> projectXZ(const VectorBase<int, 3>& vector);
};

#endif // VECTOR_UTILITY_H