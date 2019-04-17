#include "UnitUtility.h"

ci::Vec3f screenToMeter(const ci::Vec3f& vector)
{
	return ci::Vec3f(vector.x * SCREEN_TO_METER, vector.y * SCREEN_TO_METER, vector.z * SCREEN_TO_METER);
}

float screenToMeter(const float flt)
{
	return flt * SCREEN_TO_METER;
}



ci::Vec3f meterToScreen(const ci::Vec3f& vector)
{
	return ci::Vec3f(vector.x * METER_TO_SCREEN, vector.y * METER_TO_SCREEN, vector.z * METER_TO_SCREEN);
}

float meterToScreen(const float flt)
{
	return flt * METER_TO_SCREEN;
}
