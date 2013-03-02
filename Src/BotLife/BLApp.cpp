#include "BLApp.h"
#include "Canvas.h"
#include "BLWorld.h"
#include "BLBot.h"
#include "BLGoalMenu.h"
#include "Input.h"
#include "InputEvent.h"
#include "Graph\IBGPlanner.h"
#include "Graph\IBGFact.h"
#include "Graph\IBGFactBox.h"

BLApp::BLApp(int w, int h, float r, int sx, int sy, const char* tilesname)
	: GApp(w, h)
	, m_pGoalMenu(NULL)
{
	m_pEngine->SetPrintFont(FONT_PATH, 14);

	m_pWorldCanva = new Canvas(*m_pEngine, 0, 0, w, (uint16)(r*(float)h));
	m_pGraphCanva = new Canvas(*m_pEngine, 0, (sint16)(r*(float)h), w, (uint16)((1.f-r)*(float)h));

	m_pWorld = new BLWorld(*this, *m_pWorldCanva, sx, sy, tilesname);

	m_pGoalMenu = new BLGoalMenu(*m_pEngine, m_pWorld->GetBot());

	m_bPause = true;
	//m_fSlomo = 0.333f;
}

BLApp::~BLApp()
{
	delete m_pWorldCanva;
	delete m_pGraphCanva;

	delete m_pWorld;

	delete m_pGoalMenu;
}


int BLApp::Update(float dt)
{
	m_pWorld->Update(dt);
	m_pGoalMenu->SetVisible(false);
	UpdateUserInterface();

	return 0;
}

int BLApp::UpdatePause()
{
	UpdateUserInterface();
	return 0;
}


void BLApp::UpdateUserInterface()
{
	if (m_pEngine->GetInput()->GetVirtualKey(MOUSE_LEFT) == KeyPressed)
	{
		if (m_pWorldCanva->IsMouseInside())
		{
			if (!m_pGoalMenu->IsVisible())
			{
				const BLSquare* pSquare = NULL;
				int i, j;
				if (m_pWorld->GetMouseCase(&pSquare, i, j))
				{
					m_pGoalMenu->ConstructFromCase(*pSquare, i,j);
					m_pGoalMenu->SetVisible(m_pGoalMenu->GetGoals().size() > 0);

					if (m_pGoalMenu->IsVisible())
					{
						m_pGoalMenu->UpdatePos();
					}
				}
			}
			else
			{
				m_pGoalMenu->Click();
				m_pGoalMenu->SetVisible(false);
			}
		}
		else if (m_pGraphCanva->IsMouseInside())
		{
			m_pGoalMenu->SetVisible(false);
			const FactSet& oGoals = m_pWorld->GetBot().GetPlanner().GetGoals();

			for (FactSet::const_iterator it = oGoals.begin() ; it != oGoals.end() ; ++it)
			{
				IBGFact* pFact = static_cast<IBGFact*>(*it);
				if (pFact->GetFactBox()->GetCanvas().IsMouseInside())
				{
					pFact->PrepareToDelete();
					break;
				}
			}
		}

		SetPause(m_pGoalMenu->IsVisible());
	}

	if (m_pEngine->GetInput()->GetVirtualKey(MOUSE_RIGHT) == KeyPressed)
	{
		m_pWorld->StartDrag();
	}
	else if (m_pEngine->GetInput()->GetVirtualKey(MOUSE_RIGHT) == KeyDown)
	{
		m_pWorld->UpdateDrag();
	}

	if (m_pGoalMenu->IsVisible())
	{
		m_pGoalMenu->Update();
	}

}

int BLApp::Draw()
{
	m_pWorld->Draw();

	((IBGPlanner&)m_pWorld->GetBot().GetPlanner()).Draw();

	if (m_pGoalMenu->IsVisible())
	{
		m_pGoalMenu->Draw();
	}

	return 0;
}


