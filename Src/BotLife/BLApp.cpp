#include "BLApp.h"
#include "Canvas.h"
#include "BLWorld.h"
#include "Graph\IBPlannerGraph.h"
#include "BLBot.h"
#include "BLGoalMenu.h"
#include "Input.h"
#include "InputEvent.h"

BLApp::BLApp(int w, int h, float r, int sx, int sy, const char* tilesname)
	: GApp(w, h)
	, m_pGoalMenu(NULL)
{
	m_pEngine->SetPrintFont(FONT_PATH, 14);

	m_pWorldCanva = new Canvas(*m_pEngine, 0, 0, w, (uint16)(r*(float)h));
	m_pGraphCanva = new Canvas(*m_pEngine, 0, (sint16)(r*(float)h), w, (uint16)((1.f-r)*(float)h));

	m_pWorld = new BLWorld(*this, *m_pWorldCanva, sx, sy, tilesname);
	m_pPlannerDisplay = new IBPlannerGraph(m_pWorld->GetBot().GetPlanner(), *m_pGraphCanva);

	m_pGoalMenu = new BLGoalMenu(*m_pEngine);

	m_bPause = true;
	//m_fSlomo = 0.333f;
}

BLApp::~BLApp()
{
	delete m_pWorldCanva;
	delete m_pGraphCanva;

	delete m_pWorld;
	delete m_pPlannerDisplay;

	delete m_pGoalMenu;
}


int BLApp::Update(float dt)
{
	m_pWorld->Update(dt);
	m_pGoalMenu->SetVisible(false);

	return 0;
}

int BLApp::UpdatePause()
{
	if (m_pEngine->GetInput()->GetVirtualKey(MOUSE_LEFT) == KeyPressed)
	{
		const BLSquare* pSquare = NULL;
		int i, j;
		if (m_pWorld->GetMouseCase(&pSquare, i, j))
		{
			m_pGoalMenu->ConstructFromCase(*pSquare, i,j);
			m_pGoalMenu->SetVisible(m_pGoalMenu->GetGoals().size() > 0);

			if (m_pGoalMenu->GetGoals().size() > 0)
			{
				m_pGoalMenu->SetPos(m_pEngine->GetMouseX(), m_pEngine->GetMouseY());
			}
		}

		// test
		if (m_pGoalMenu->IsVisible())
		{
			m_pWorld->GetBot().AddGoal(m_pGoalMenu->GetGoals()[0]);
		}
	}

	if (m_pGoalMenu->IsVisible())
	{
		m_pGoalMenu->Update();
	}

	return 0;
}

int BLApp::Draw()
{
	m_pWorld->Draw();

	m_pPlannerDisplay->DrawGraph();

	if (m_pGoalMenu->IsVisible())
	{
		m_pGoalMenu->Draw();
	}

	return 0;
}


