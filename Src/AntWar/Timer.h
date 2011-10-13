#ifndef TIMER_H_
#define TIMER_H_


/*
    struct for checking how long it has been since the start of the turn.
*/
#ifdef _WIN32 //Windows timer (DON'T USE THIS TIMER UNLESS YOU'RE ON WINDOWS!)
    #include <io.h>
    #include <windows.h>
	#include <time.h>

    struct Timer
    {
        clock_t startTime;

        Timer()
        {

        };

        void Start()
        {
            startTime = clock();
        };

        float GetTime() const
        {
            clock_t currentTime = clock();

            return (float)(currentTime - startTime);
        };
    };

#else //Mac/Linux Timer
	#include <sys/time.h>

	struct Timer
    {
        float startTime;

        Timer()
        {

        };

        //starts the timer
        void Start()
        {
			timeval timer;
			gettimeofday(&timer, NULL);
            startTime = (float)timer.tv_sec+((float)timer.tv_usec/1000000.0f);
        };

        //returns how long it has been since the timer was last started in milliseconds
        float GetTime() const
        {
			timeval timer;
			gettimeofday(&timer, NULL);
            clock_t currentTime = timer.tv_sec+(long)((double)timer.tv_usec/1000000.0);
            return ((float)currentTime-startTime)*1000.0f;
        };
    };
#endif


#endif //TIMER_H_
