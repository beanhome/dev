#include "Timer.h"


#ifdef _WIN32

#if 1

#include <basetsd.h>
#include <WTypes.h>
#include <winbase.h>

double GetClock()
{
	LARGE_INTEGER iCount;
	QueryPerformanceCounter( &iCount );
	//return (uint64)iCount.QuadPart;

	LARGE_INTEGER iFreq;
	QueryPerformanceFrequency( &iFreq );

	return ((double)iCount.QuadPart) / (double)iFreq.QuadPart;
}

#else

#include <io.h>
#include <windows.h>
#include <time.h>

double GetClock()
{
	clock_t currentTime = clock();
	return ((double)currentTime) / (double)CLOCKS_PER_SEC;
}
#endif

#else

//#include <sys/time.h>
#include <time.h>

double GetClock()
{
	timespec timer;
	clock_gettime(CLOCK_REALTIME, &timer);
	double currentTime = (double)timer.tv_sec+((double)timer.tv_nsec/1000000000.0);
	return currentTime;

	/*
	timeval timer;
	gettimeofday(&timer, NULL);
	clock_t currentTime = timer.tv_sec+(long)((double)timer.tv_usec/1000000.0);
	return ((double)currentTime)*1000.0;
	*/
}
#endif


Timer Timer::s_oTimer;

Timer::Timer()
	: m_fStartTime(GetClock())
{}

double Timer::GetTime() const
{
	return GetClock() - m_fStartTime;
}

