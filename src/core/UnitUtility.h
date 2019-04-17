#ifndef UNIT_UTILITY_H
#define UNIT_UTILITY_H

#include "Defines.h"

#include "cinder/Vector.h"

ci::Vec3f screenToMeter(const ci::Vec3f& vector);
float screenToMeter(const float flt);



ci::Vec3f meterToScreen(const ci::Vec3f& vector);
float meterToScreen(const float flt);

#endif // UNIT_UTILITY_H