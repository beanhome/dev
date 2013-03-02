#include "TilesViewApp.h"
#include "Timer.h"
#include "Map\BLTiles.h"
#include "Map\BLMap.h"
#include "InputEvent.h"

TilesViewApp::TilesViewApp(int w, int h, const char* rootpath, const char* name)
	: GApp(w, h, rootpath)
	, m_pTiles(NULL)
	, mode(Explore)
	, lastmode(Explore)
{
	m_pEngine->SetPrintFont(FONT_PATH, 14);

	m_pTiles = new BLTiles(*m_pEngine, name);

	id = 200;
}

TilesViewApp::~TilesViewApp()
{
	delete m_pTiles;
}


int TilesViewApp::Update(float dt)
{
	lastmode = mode;

	bool bQuit = false;

	bool bLeft = false;
	bool bRight = false;

	if (m_pEngine->GetInputEvent().IsKeyboard() && m_pEngine->GetInputEvent().GetKeyboardEvent() == KeyDown)
	{
		switch (mode)
		{
			case Explore:
				if      (!bLeft && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_LEFT)		bLeft = true;
				else if (!bRight && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_RIGHT)	bRight = true;
				else if (m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_F1)		mode = Choose_TL;
				else if (m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_F2)		mode = Choose_TR;
				else if (m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_F3)		mode = Choose_BL;
				else if (m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_F4)		mode = Choose_BR;
				else if (m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_ESC)	bQuit = true;
				else if (m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_DELETE)
				{
					m_pTiles->Del(id);
				}
				break;

			case Choose_TL:
			case Choose_TR:
			case Choose_BL:
			case Choose_BR:
				if      (m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_ESC)	mode = Explore;
				else if (!bLeft && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_LEFT)		bLeft = true;
				else if (!bRight && m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_RIGHT)	bRight = true;
				else if (m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_F1)		mode = Choose_TL;
				else if (m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_F2)		mode = Choose_TR;
				else if (m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_F3)		mode = Choose_BL;
				else if (m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_F4)		mode = Choose_BR;
				else if (m_pEngine->GetInputEvent().GetKeyboardKey() == KEY_SPACE)
				{
					m_pTiles->Add(oKey, id);
					mode = Explore;
				}
				break;
		}
	}

	switch (mode)
	{
	case Explore:
		if (bLeft) id = max(0, id-1);
		if (bRight) id = min(id+1, m_pTiles->GetTilesCount());
		oKey = m_pTiles->Find(id);
		break;

	case Choose_TL:
		if (bLeft) oKey.TL = (oKey.TL-1) % CaseType_MAX;
		if (bRight) oKey.TL = (oKey.TL+1) % CaseType_MAX;
		break;

	case Choose_TR:
		if (bLeft) oKey.TR = (oKey.TR-1) % CaseType_MAX;
		if (bRight) oKey.TR = (oKey.TR+1) % CaseType_MAX;
		break;

	case Choose_BL:
		if (bLeft) oKey.BL = (oKey.BL-1) % CaseType_MAX;
		if (bRight) oKey.BL = (oKey.BL+1) % CaseType_MAX;
		break;

	case Choose_BR:
		if (bLeft) oKey.BR = (oKey.BR-1) % CaseType_MAX;
		if (bRight) oKey.BR = (oKey.BR+1) % CaseType_MAX;
		break;
	}

	return (bQuit ? -1 : (mode != lastmode || bLeft || bRight));
}

int TilesViewApp::Draw()
{
	int iTileSize = 128;

	m_pEngine->Print(400, 150, m_pEngine->GetPrintFont(), 40, CenterBottom, 0, 0, 0, "%d", id);
	m_pTiles->DrawTile(*m_pEngine, id, 400, 400, iTileSize, iTileSize);

	if (oKey.TL != (uint8)-1)
	{
		m_pTiles->DrawTile(*m_pEngine, m_pTiles->Find((CaseType)oKey.TL), 400-iTileSize, 400-iTileSize, iTileSize, iTileSize);
		m_pEngine->Print(400-iTileSize, 400-iTileSize, m_pEngine->GetPrintFont(), 20, Center, 0, 0, 0, "%s", BLMap::s_sCaseType[oKey.TL]);
	}

	if (oKey.TR != (uint8)-1)
	{
		m_pTiles->DrawTile(*m_pEngine, m_pTiles->Find((CaseType)oKey.TR), 400+iTileSize, 400-iTileSize, iTileSize, iTileSize);
		m_pEngine->Print(400+iTileSize, 400-iTileSize, m_pEngine->GetPrintFont(), 20, Center, 0, 0, 0, "%s", BLMap::s_sCaseType[oKey.TR]);
	}

	if (oKey.BL != (uint8)-1)
	{
		m_pTiles->DrawTile(*m_pEngine, m_pTiles->Find((CaseType)oKey.BL), 400-iTileSize, 400+iTileSize, iTileSize, iTileSize);
		m_pEngine->Print(400-iTileSize, 400+iTileSize, m_pEngine->GetPrintFont(), 20, Center, 0, 0, 0, "%s", BLMap::s_sCaseType[oKey.BL]);
	}

	if (oKey.BR != (uint8)-1)
	{
		m_pTiles->DrawTile(*m_pEngine, m_pTiles->Find((CaseType)oKey.BR), 400+iTileSize, 400+iTileSize, iTileSize, iTileSize);
		m_pEngine->Print(400+iTileSize, 400+iTileSize, m_pEngine->GetPrintFont(), 20, Center, 0, 0, 0, "%s", BLMap::s_sCaseType[oKey.BR]);
	}

	if (oKey.TL != (uint8)-1 && oKey.TR != (uint8)-1)
		m_pTiles->DrawTile(*m_pEngine, m_pTiles->Find((CaseType)oKey.TL, (CaseType)oKey.TR, (CaseType)oKey.TL, (CaseType)oKey.TR), 400, 400-iTileSize, iTileSize, iTileSize);

	if (oKey.BL != (uint8)-1 && oKey.BR != (uint8)-1)
		m_pTiles->DrawTile(*m_pEngine, m_pTiles->Find((CaseType)oKey.BL, (CaseType)oKey.BR, (CaseType)oKey.BL, (CaseType)oKey.BR), 400, 400+iTileSize, iTileSize, iTileSize);

	if (oKey.TL != (uint8)-1 && oKey.BL != (uint8)-1)
		m_pTiles->DrawTile(*m_pEngine, m_pTiles->Find((CaseType)oKey.TL, (CaseType)oKey.TL, (CaseType)oKey.BL, (CaseType)oKey.BL), 400-iTileSize, 400, iTileSize, iTileSize);

	if (oKey.TR != (uint8)-1 && oKey.BR != (uint8)-1)
		m_pTiles->DrawTile(*m_pEngine, m_pTiles->Find((CaseType)oKey.TR, (CaseType)oKey.TR, (CaseType)oKey.BR, (CaseType)oKey.BR), 400+iTileSize, 400, iTileSize, iTileSize);

	switch (mode)
	{
		case Explore:
			break;

		case Choose_TL:
			m_pEngine->DrawRect(400-iTileSize*3/2, 400-iTileSize*3/2, iTileSize-1, iTileSize-1, 0, 0, 0);
			break;

		case Choose_TR:
			m_pEngine->DrawRect(400+iTileSize/2, 400-iTileSize*3/2, iTileSize-1, iTileSize-1, 0, 0, 0);
			break;

		case Choose_BL:
			m_pEngine->DrawRect(400-iTileSize*3/2, 400+iTileSize/2, iTileSize-1, iTileSize-1, 0, 0, 0);
			break;

		case Choose_BR:
			m_pEngine->DrawRect(400+iTileSize/2, 400+iTileSize/2, iTileSize-1, iTileSize-1, 0, 0, 0);
			break;
	}

	return 0;
}

int TilesViewApp::Loop()
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
		dt = min(dt, 0.1f);

		m_pEngine->Clear();

		res = Draw();
		if (res != 0)
			return res;

		m_pEngine->Flip();

		res = 0;
		while (res == 0)
		{
			m_pEngine->SaveEvent();
			if (m_pEngine->PollEvent())
			{
				res = Update(dt);
				bQuit = (res == -1);
			}
		}
	}
	return 0;
}


