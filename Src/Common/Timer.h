#ifndef __TIMER_H__
#define __TIMER_H__

double GetClock();


class Timer
{
	public:
		Timer();

		double GetTime() const;

	private:
		double m_fStartTime;

	public:
		static Timer s_oTimer;
		static double Get() { return s_oTimer.GetTime(); }
};


#endif //__TIMER_H__
