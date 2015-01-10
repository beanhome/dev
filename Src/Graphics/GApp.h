#ifndef __GAPP_H__
#define __GAPP_H__

#include "Utils.h"

class GEngine;
class Event;

class GAppBase
{
	public:
		GAppBase();
		virtual ~GAppBase();

		//void SetNoClearScreen(bool bNoClearScreen) { m_bNoClearScreen = bNoClearScreen; }
		//bool GetNoClearScreen() const { return m_bNoClearScreen; }

		void SetSlomo(float slomo) { m_fSlomo = slomo; }
		float GetSlomo() const { return m_fSlomo; }

		bool IsPaused() const { return m_bPause; }
		void SetPause(bool bPause) { m_bPause = bPause; }

		virtual int Update(float dt) = 0;
		virtual int UpdatePause() { return 0; };
		virtual int Draw() = 0;

		virtual void Init() {}
		virtual int Loop();
		virtual void Close() {}

		virtual void CatchEvent(Event* pEvent);
	protected:
		GEngine* m_pEngine;
		bool m_bNoClearScreen;
		bool m_bPause;
		float m_fSlomo;
		bool m_bQuit;
};

template <typename ENGINE>
class GApp : public GAppBase
{
	public:
		GApp(int w, int h, const char* rootpath)
		{
			m_pEngine = new ENGINE(this, w, h, 32, rootpath);
		}

		virtual void Init()
		{
		}
};


#endif // __GAPP_H__

