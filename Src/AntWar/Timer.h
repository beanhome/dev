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
        timeval timer;
        float startTime;

        Timer()
        {

        };

        //starts the timer
        void Start()
        {
            gettimeofday(&timer, NULL);
            startTime = timer.tv_sec+(timer.tv_usec/1000000.0);
        };

        //returns how long it has been since the timer was last started in milliseconds
        float GetTime() const
        {
            gettimeofday(&timer, NULL);
            clock_t currentTime = timer.tv_sec+(timer.tv_usec/1000000.0);
            return (currentTime-startTime)*1000.0;
        };
    };
#endif


#endif //TIMER_H_
