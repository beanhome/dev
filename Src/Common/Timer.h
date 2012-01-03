#ifndef __TIMER_H__
#define __TIMER_H__

float GetClock();


class Timer
{
	public:
		Timer();

		float GetTime() const;

	private:
		float m_fStartTime;

	public:
		static Timer s_oTimer;
		static float Get() { return s_oTimer.GetTime(); }
};


#endif //__TIMER_H__
