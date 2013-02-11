#ifndef __GAPP_H__
#define __GAPP_H__

#include "Utils.h"

class GEngine;

class GAppBase
{
	public:
		GAppBase();
		virtual ~GAppBase();

		//void SetNoClearScreen(bool bNoClearScreen) { m_bNoClearScreen = bNoClearScreen; }
		//bool GetNoClearScreen() const { return m_bNoClearScreen; }

		virtual int Update(float dt) = 0;
		virtual int Draw() = 0;

		virtual int Loop();

	protected:
		GEngine* m_pEngine;
		bool m_bNoClearScreen;
};

template <typename ENGINE>
class GApp : public GAppBase
{
	public:
		GApp(int w, int h)
		{
			m_pEngine = new ENGINE(w, h, 32);
		}
};


#endif // __GAPP_H__

