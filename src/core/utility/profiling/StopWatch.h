#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include <Windows.h>

class StopWatch
{
public:
	StopWatch();
	~StopWatch();

	void start();
	void stop();
	LONGLONG getTime();

private:
	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_endTime;
};

#endif // STOP_WATCH_H