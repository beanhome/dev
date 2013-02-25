#include "BLApp.h"
#include "Canvas.h"
#include "BLWorld.h"
#include "Graph\IBPlannerGraph.h"
#include "BLBot.h"

BLApp::BLApp(int w, int h, float r, int sx, int sy, const char* tilesname)
	: GApp(w, h)
{
	m_pEngine->SetPrintFont(FONT_PATH, 14);

	m_pWorldCanva = new Canvas(*m_pEngine, 0, 0, w, (uint16)(r*(float)h));
	m_pGraphCanva = new Canvas(*m_pEngine, 0, (sint16)(r*(float)h), w, (uint16)((1.f-r)*(float)h));

	m_pWorld = new BLWorld(*this, *m_pWorldCanva, sx, sy, tilesname);
	m_pPlannerDisplay = new IBPlannerGraph(m_pWorld->GetBot().GetPlanner(), *m_pGraphCanva);

	m_bPause = true;
	//m_fSlomo = 0.333f;
}

BLApp::~BLApp()
{
	delete m_pWorldCanva;
	delete m_pGraphCanva;

	delete m_pWorld;
	delete m_pPlannerDisplay;
}


int BLApp::Update(float dt)
{
	m_pWorld->Update(dt);

	return 0;
}

int BLApp::Draw()
{
	m_pWorld->Draw();

	m_pPlannerDisplay->DrawGraph();

	return 0;
}


