#ifndef PROFILING_H
#define PROFILING_H

#include <iostream>

#include "core/utility/logging/LogManager.h"

#include "StopWatch.h"

#define TIME_OPERATION(__operation__) \
do \
{ \
	StopWatch watch; \
	watch.start(); \
	__operation__; \
	watch.stop(); \
	LOG_WARNING_STREAM(<< "Operation time: " << watch.getTime()); \
} \
while (0) \

#define TIME_OPERATION_NAME(__operation__, __operation_name__) \
do \
{ \
	StopWatch watch; \
	watch.start(); \
	__operation__; \
	watch.stop(); \
	LOG_WARNING_STREAM(<< __operation_name__ << ": " << watch.getTime()); \
} \
while (0) \

#endif // PROFILING_H