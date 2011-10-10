#include "Utils.h"
#include "Time.h"

#ifdef MYDEBUG
#define USE_TIMER 1
#endif

#ifdef USE_TIMER
#include <sys/timeb.h>
#endif

#define NBE_SEC 100

#ifdef USE_TIMER
uint GetTime()
{
	struct _timeb timebuffer;
	_ftime_s(&timebuffer);

	return (timebuffer.time % NBE_SEC) * 1000 + timebuffer.millitm;
}
#else
uint GetTime()
{
	return 0;
}
#endif


// t2 > t1
uint GetDelta(uint t1, uint t2)
{
	if (t2 < t1)
		t2 += NBE_SEC;

	return t2 - t1;
}

