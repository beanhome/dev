#include "Timer.h"


#ifdef _WIN32

#if 1

#include <basetsd.h>
#include <WTypes.h>
#include <winbase.h>

float GetClock()
{
	LARGE_INTEGER iCount;
	QueryPerformanceCounter( &iCount );
	//return (uint64)iCount.QuadPart;

	LARGE_INTEGER iFreq;
	QueryPerformanceFrequency( &iFreq );

	return ((float)iCount.QuadPart) / (float)iFreq.QuadPart;
}

#else

#include <io.h>
#include <windows.h>
#include <time.h>

float GetClock()
{
	clock_t currentTime = clock();
	return ((float)currentTime) / (float)CLOCKS_PER_SEC;
}
#endif

#else

#include <sys/time.h>

float GetClock()
{
	timeval timer;
	gettimeofday(&timer, NULL);
	clock_t currentTime = timer.tv_sec+(long)((double)timer.tv_usec/1000000.0);
	return ((float)currentTime)*1000.0f;
}
#endif


Timer Timer::s_oTimer;

Timer::Timer()
	: m_fStartTime(GetClock())
{}

float Timer::GetTime() const
{
	return GetClock() - m_fStartTime;
}

