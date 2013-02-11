#include "MapViewApp.h"
#include "Timer.h"
#include "Map\BLTiles.h"
#include "Map\BLMap.h"

MapViewApp::MapViewApp(int w, int h, const char* name)
	: GApp(w, h)
{
	m_bNoClearScreen = true;
	m_pEngine->SetPrintFont(FONT_PATH, 14);

	int seed = (int)GetClock();
	LOG("Seed : %d\n", seed);
	srand(seed);

	m_pTiles = new BLTiles(*m_pEngine, name);
	m_pMap = new BLMap(m_pEngine->GetWidth()/m_pTiles->GetTilesWidth(), m_pEngine->GetHeight()/m_pTiles->GetTilesHeight(), *m_pTiles);

	for (uint i=0 ; i<20 ; ++i)
	{
		m_pEngine->Clear();
		m_pMap->Display(*m_pEngine);
		m_pMap->Step(i);
		m_pEngine->Flip();
	}
}

MapViewApp::~MapViewApp()
{
	delete m_pTiles;
	delete m_pMap;
}


int MapViewApp::Update(float dt)
{
	return 0;
}

int MapViewApp::Draw()
{

	return 0;
}


