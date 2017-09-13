#include "GApp.h"
#include "GEngine.h"
#include "Timer.h"
#include "Event.h"
//#include <complex>
#include "EventManager.h"

GAppBase::GAppBase()
	: m_pEngine(NULL)
	, m_bNoClearScreen(false)
	, m_bPause(false)
	, m_fSlomo(1.f)
	, m_bQuit(false)
{
}

GAppBase::~GAppBase()
{
	delete m_pEngine;
}

void GAppBase::CatchEvent(Event* pEvent)
{
	m_bQuit |= pEvent->IsQuit();

	if (pEvent->IsKeyboard())
	{
		m_bQuit |= (m_pEngine->GetEventManager()->GetVirtualKey(KEY_ESC) == KeyPressed);

		/*
		if (m_pEngine->GetEventManager()->GetVirtualKey(KEY_SPACE) == KeyPressed)
			m_bPause = !m_bPause;
		*/
	}

	if (pEvent->IsResize())
	{
		sint32 w, h;
		pEvent->GetResizeEvent(w, h);
		m_pEngine->Resize((uint16)w, (uint16)h);
	}
}


int GAppBase::Loop()
{
	int res;
	double fTime = Timer::Get();
	double fLastTime = fTime;

	while (!m_bQuit)
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

		m_pEngine->UpdateEvent(dt);
	}

	return 0;
}

