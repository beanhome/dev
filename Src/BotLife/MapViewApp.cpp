#include "MapViewApp.h"
#include "Timer.h"
#include "Map\BLTiles.h"
#include "Map\BLMap.h"
#include "Canvas.h"
#include "GEngine.h"
#include "InputEvent.h"

MapViewApp::MapViewApp(int w, int h, const char* name)
	: GApp(w, h)
	, m_bDrag(false)
	, m_iStartOffsetX(0)
	, m_iStartOffsetY(0)
{
	m_pEngine->SetPrintFont(FONT_PATH, 14);

	m_pCanvas = new Canvas(*m_pEngine, 0, 0, m_pEngine->GetWidth(), m_pEngine->GetHeight());

	int seed = (int)GetClock();
	LOG("Seed : %d\n", seed);
	srand(seed);

	m_pTiles = new BLTiles(*m_pEngine, name);
	//m_pMap = new BLMap(canvas.GetWidth()/m_pTiles->GetTilesWidth(), canvas.GetHeight()/m_pTiles->GetTilesHeight(), *m_pTiles);
	m_pMap = new BLMap(64, 64, *m_pTiles);

	for (uint i=0 ; i<20 ; ++i)
	{
		m_pEngine->Clear();
		m_pMap->ConvertTypeToTiles();
		m_pMap->Display(*m_pCanvas);
		m_pMap->Step(i);
		m_pEngine->Flip();
	}
}

MapViewApp::~MapViewApp()
{
	delete m_pTiles;
	delete m_pMap;
	delete m_pCanvas;
}


int MapViewApp::Update(float dt)
{
	if (m_pEngine->GetInputEvent().IsMouse())
	{
		if (!m_bDrag && m_pEngine->GetInputEvent().GetMouseEvent() == LeftDown)
		{
			m_iStartOffsetX = m_pEngine->GetMouseX() + m_pCanvas->GetOrigX();
			m_iStartOffsetY = m_pEngine->GetMouseY() + m_pCanvas->GetOrigY();
			m_bDrag = true;
		}
		else if (m_bDrag && m_pEngine->GetInputEvent().GetMouseEvent() == LeftUp)
		{
			m_bDrag = false;
		}
		else if (m_bDrag)
		{
			sint16 x = std::max<sint16>(m_iStartOffsetX - (sint16)m_pEngine->GetMouseX(), 0);
			sint16 y = std::max<sint16>(m_iStartOffsetY - (sint16)m_pEngine->GetMouseY(), 0);
			x = std::min<sint16>(x, std::max<sint16>(m_pMap->GetWidth() * m_pTiles->GetTilesWidth() - m_pCanvas->GetWidth(), 0));
			y = std::min<sint16>(y, std::max<sint16>(m_pMap->GetHeight() * m_pTiles->GetTilesHeight() - m_pCanvas->GetHeight(), 0));
			m_pCanvas->SetOrigX(x);
			m_pCanvas->SetOrigY(y);
		}
		else
		{
			m_iMouseCaseX = m_pCanvas->GetMouseX() / m_pTiles->GetTilesWidth();
			m_iMouseCaseY = m_pCanvas->GetMouseY() / m_pTiles->GetTilesHeight();
		}
	}
	return 0;
}

int MapViewApp::Draw()
{
	m_pMap->Display(*m_pCanvas);

	if (!m_bDrag)
	{
		m_pEngine->Print(100, 100, m_pEngine->GetPrintFont(), 15, LeftTop, 255, 255, 255, "Mouse : %d %d", m_iMouseCaseX, m_iMouseCaseY);
		m_pEngine->Print(100, 130, m_pEngine->GetPrintFont(), 15, LeftTop, 255, 255, 255, "Tiles : %s", BLMap::s_sTilesType[m_pMap->GetTilesCase(m_iMouseCaseX, m_iMouseCaseY).eType]);
		m_pCanvas->DrawRect(m_iMouseCaseX * m_pTiles->GetTilesWidth(), m_iMouseCaseY * m_pTiles->GetTilesHeight(), m_pTiles->GetTilesWidth()-1, m_pTiles->GetTilesHeight()-1, 255, 255, 255);
	}

	//m_pEngine->Print(100, 100, m_pEngine->GetPrintFont(), 15, LeftTop, 255, 255, 255, "Mouse : %d %d", m_pEngine->GetMouseX(), m_pEngine->GetMouseY());

	return 0;
}


