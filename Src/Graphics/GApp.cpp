#include "GApp.h"
#include "GEngine.h"
#include "Timer.h"
#include "Event.h"
#include <complex>
#include "EventManager.h"

GAppBase::GAppBase()
	: m_pEngine(NULL)
	, m_bNoClearScreen(false)
	, m_bPause(false)
	, m_fSlomo(1.f)
{
}

GAppBase::~GAppBase()
{
	delete m_pEngine;
}


int GAppBase::Loop()
{
	int res;
	bool bQuit = false;
	double fTime = Timer::Get();
	double fLastTime = fTime;

	while (!bQuit)
	{
		fLastTime = fTime;
		fTime = Timer::Get();
		float dt = (float)(fTime - fLastTime);
		dt = std::min<float>(dt, 0.1f);

		if (!m_bPause)
		{
			res = Update(dt * m_fSlomo);
			if (res != 0)
				return res;
		}
		else
		{
			res = UpdatePause();
			if (res != 0)
				return res;
		}

		if (!m_bNoClearScreen)
			m_pEngine->Clear();

		res = Draw();
		if (res != 0)
			return res;

		//m_pEngine->ClampClear();
		//m_pEngine->Print(5, 5, m_pEngine->GetPrintFont(), 12, LeftTop, 255, 255, 255, "%f", dt);
		//m_pEngine->Print(5, 20, m_pEngine->GetPrintFont(), 12, LeftTop, 255, 255, 255, "%f", fTime);

		if (m_bPause)
		{
			m_pEngine->ClampClear();
			m_pEngine->CanvasBase::Print(m_pEngine->GetWidth()/2, 100, m_pEngine->GetPrintFont(), 50, Center, (int)(std::sin(fTime*4.f)*0.5f * 254.f) + 127, 0, 0, "PAUSE");
		}

		m_pEngine->Flip();

		m_pEngine->UpdateEvent();

		bQuit = m_pEngine->GetEventManager()->IsQuit();
		bQuit |= (m_pEngine->GetEventManager()->GetVirtualKey(KEY_ESC) == KeyPressed);

		if (m_pEngine->GetEventManager()->GetVirtualKey(KEY_SPACE) == KeyPressed)
			m_bPause = !m_bPause;
	}

	return 0;
}


