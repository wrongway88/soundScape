#include "VectorUtility.h"

ci::Vec3f VectorUtility::convert(const VectorBase<float, 3>& vector)
{
	return ci::Vec3f(vector.getValue(0), vector.getValue(1), vector.getValue(2));
}

VectorBase<float, 3> VectorUtility::convert(const ci::Vec3f& vector)
{
	VectorBase<float, 3> result;
	result.setValue(0, vector.x);
	result.setValue(1, vector.y);
	result.setValue(2, vector.z);

	return result;
}

ci::Vec2f VectorUtility::convert(const VectorBase<float, 2>& vector)
{
	return ci::Vec2f(vector.getValue(0), vector.getValue(1));
}

VectorBase<float, 2> VectorUtility::convert(const ci::Vec2f& vector)
{
	VectorBase<float, 2> result;
	result.setValue(0, vector.x);
	result.setValue(1, vector.y);

	return result;
}

ci::Vec3i VectorUtility::convert(const VectorBase<int, 3>& vector)
{
	return ci::Vec3i(vector.getValue(0), vector.getValue(1), vector.getValue(2));
}

VectorBase<int, 3> VectorUtility::convert(const ci::Vec3i& vector)
{
	VectorBase<int, 3> result;
	result.setValue(0, vector.x);
	result.setValue(1, vector.y);
	result.setValue(2, vector.z);

	return result;
}

ci::Vec2i VectorUtility::convert(const VectorBase<int, 2>& vector)
{
	return ci::Vec2i(vector.getValue(0), vector.getValue(1));
}

VectorBase<int, 2> VectorUtility::convert(const ci::Vec2i& vector)
{
	VectorBase<int, 2> result;
	result.setValue(0, vector.x);
	result.setValue(1, vector.y);

	return result;
}

ci::Vec2f VectorUtility::projectXZ(const ci::Vec3f& vector)
{
	return ci::Vec2f(vector.x, vector.z);
}

ci::Vec2i VectorUtility::projectXZ(const ci::Vec3i& vector)
{
	return ci::Vec2i(vector.x, vector.z);
}

VectorBase<float, 2> VectorUtility::projectXZ(const VectorBase<float, 3>& vector)
{
	VectorBase<float, 2> result;
	result.setValue(0, vector.getValue(0));
	result.setValue(1, vector.getValue(2));

	return result;
}

VectorBase<int, 2> VectorUtility::projectXZ(const VectorBase<int, 3>& vector)
{
	VectorBase<int, 2> result;
	result.setValue(0, vector.getValue(0));
	result.setValue(1, vector.getValue(2));

	return result;
}