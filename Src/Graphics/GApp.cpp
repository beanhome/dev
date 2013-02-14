#include "GApp.h"
#include "GEngine.h"
#include "Timer.h"
#include "InputEvent.h"
#include <complex>

GAppBase::GAppBase()
	: m_pEngine(NULL)
	, m_bNoClearScreen(false)
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
	bool bPause = false;
	double fTime = Timer::Get();
	double fLastTime = fTime;

	while (!bQuit)
	{
		fLastTime = fTime;
		fTime = Timer::Get();
		float dt = (float)(fTime - fLastTime);
		dt = min(dt, 0.1f);

		if (!bPause)
		{
			res = Update(dt);
			if (res != 0)
				return res;
		}

		if (!m_bNoClearScreen)
			m_pEngine->Clear();

		res = Draw();
		if (res != 0)
			return res;

		if (bPause)
			m_pEngine->CanvasBase::Print(m_pEngine->GetWidth()/2, 100, m_pEngine->GetPrintFont(), 50, Center, (int)(std::sin(fTime*4.f)*0.5f * 254.f) + 127, 0, 0, "PAUSE");

		m_pEngine->Flip();

		m_pEngine->SaveEvent();
		if (m_pEngine->PollEvent())
		{
			if (m_pEngine->GetInputEvent().IsQuit()
				|| m_pEngine->GetInputEvent().IsKeyboard() && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_ESC)
				bQuit = true;

			if (bPause && m_pEngine->GetInputEvent().IsKeyboard() && m_pEngine->GetInputEvent().GetKeyboardEvent() == KeyDown && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_SPACE)
				bPause = false;

			else if (!bPause && m_pEngine->GetInputEvent().IsKeyboard() && m_pEngine->GetInputEvent().GetKeyboardEvent() == KeyDown && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_SPACE)
				bPause = true;

			if (m_pEngine->GetInputEvent().IsMouse())
			{
				uint16 x, y;
				m_pEngine->GetInputEvent().GetMouseMove(x, y);
				m_pEngine->SetMouse(x, y);
			}

		}
	}

	return 0;
}


