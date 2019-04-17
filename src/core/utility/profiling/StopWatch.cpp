#include "StopWatch.h"

StopWatch::StopWatch()
	: m_startTime()
	, m_endTime()
{

}

StopWatch::~StopWatch()
{

}

void StopWatch::start()
{
	QueryPerformanceCounter(&m_startTime);
}

void StopWatch::stop()
{
	QueryPerformanceCounter(&m_endTime);
}

LONGLONG StopWatch::getTime()
{
	return m_endTime.QuadPart - m_startTime.QuadPart;
}