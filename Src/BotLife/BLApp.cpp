#include "BLApp.h"
#include "Canvas.h"
#include "BLWorld.h"
#include "Graph\IBPlannerGraph.h"
#include "BLBot.h"

BLApp::BLApp(int w, int h, float r)
	: GApp(w, h)
{
	m_pEngine->SetPrintFont(FONT_PATH, 14);

	m_pWorldCanva = new Canvas(*m_pEngine, 0, 0, w, (uint16)(r*(float)h));
	m_pGraphCanva = new Canvas(*m_pEngine, 0, (sint16)(r*(float)h), w, (uint16)((1.f-r)*(float)h));

	m_pWorld = new BLWorld(*m_pWorldCanva, 20);
	m_pPlannerDisplay = new IBPlannerGraph(m_pWorld->GetBot().GetPlanner(), *m_pGraphCanva);
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


