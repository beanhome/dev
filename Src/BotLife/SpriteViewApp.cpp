#include "SpriteViewApp.h"
#include "Timer.h"
#include "Event.h"
#include "ImageFlipBook.h"

SpriteViewApp::SpriteViewApp(int w, int h, const char* rootpath)
	: GApp<GEngine_SDL>(w, h, rootpath)
	, m_bLeft(false)
	, m_bRight(false)
	, m_bUp(false)
	, m_bDown(false)
	, m_bEnter(false)
	, m_bPlay(false)
	, m_fStateTime(0.f)
	, m_fStateDelay(0.2f)
{
	m_pEngine->SetPrintFont(FONT_PATH, 14);

	m_pImage = new ImageFlipBook(*m_pEngine, m_pEngine->GetImageResource(DATA_DIR "/BotLife/peasant_walk.png"), 8, 6);
	m_pImage->SetCurrent(0);

	m_pImage->SetPos(400, 400);

}

SpriteViewApp::~SpriteViewApp()
{
}


int SpriteViewApp::Update(float dt)
{
	int col = m_pImage->GetCurrent() % m_pImage->GetColCount();
	int row = m_pImage->GetCurrent() / m_pImage->GetColCount();

	if (m_pEngine->GetInputEvent().IsKeyboard() && m_pEngine->GetInputEvent().GetKeyboardEvent() == KeyDown)
	{
		if      (!m_bLeft && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_LEFT)
		{
			m_bLeft = true;
			m_bPlay = false;
			col = (col + m_pImage->GetColCount() - 1) % m_pImage->GetColCount();
		}
		else if (!m_bRight && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_RIGHT)
		{
			m_bRight = true;
			m_bPlay = false;
			col = (col + 1) % m_pImage->GetColCount();
		}
		else if (!m_bUp && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_UP)
		{
			m_bUp = true;
			m_bPlay = false;
			row = (row + m_pImage->GetRowCount() - 1) % m_pImage->GetRowCount();
		}
		else if (!m_bDown && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_DOWN)
		{
			m_bDown = true;
			m_bPlay = false;
			row = (row + 1) % m_pImage->GetRowCount();
		}
		else if (!m_bEnter && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_ENTER)
		{
			m_bEnter = true;
			m_bPlay = !m_bPlay;
		}
	}
	else if (m_pEngine->GetInputEvent().IsKeyboard() && m_pEngine->GetInputEvent().GetKeyboardEvent() == KeyUp)
	{
		if      (m_bLeft && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_LEFT)	m_bLeft = false;
		else if (m_bRight && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_RIGHT)	m_bRight = false;
		else if (m_bUp && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_UP)		m_bUp = false;
		else if (m_bDown && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_DOWN)	m_bDown = false;
		else if (m_bEnter && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_ENTER)
		{
			m_bEnter = false;
		}
	}

	if (m_bPlay)
	{
		m_fStateTime += dt;
		if (m_fStateTime > m_fStateDelay)
		{
			m_fStateTime -= m_fStateDelay;
			col = (col + 1) % m_pImage->GetColCount();
		}
	}

	m_pImage->SetCurrent(row * m_pImage->GetColCount() + col);

	return 0;
}

int SpriteViewApp::Draw()
{
	m_pImage->Draw(4.f);
	m_pEngine->DrawRect(400-64, 400-64, 128-1, 128-1, 0, 0, 0);

	int col = m_pImage->GetCurrent() % m_pImage->GetColCount();
	int row = m_pImage->GetCurrent() / m_pImage->GetColCount();
	m_pEngine->Print(400, 300, m_pEngine->GetPrintFont(), 14, Center, 255, 255, 255, "%d %d", col, row);

	return 0;
}


