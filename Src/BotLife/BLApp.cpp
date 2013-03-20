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

BLApp::BLApp(int w, int h, const char* rootpath, float r, int sx, int sy, const char* tilesname)
	: GApp<GEngine_SDL>(w, h, rootpath)
	, m_pGoalMenu(NULL)
	, m_pSelectSquare(NULL)
{
	m_pEngine->SetPrintFont(FONT_PATH, 14);

	m_pWorldCanva = new Canvas(*m_pEngine, 0, 0, w, (uint16)(r*(float)h));
	m_pGraphCanva = new Canvas(*m_pEngine, 0, (sint16)(r*(float)h), w, (uint16)((1.f-r)*(float)h));

	m_pWorld = new BLWorld(*this, *m_pWorldCanva, sx, sy, tilesname);

	m_pGoalMenu = new BLGoalMenu(*m_pEngine, m_pWorld->GetBot());

	//m_bPause = true;
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
	//m_pGoalMenu->SetVisible(false);
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
				const BLSquare* pSquare = m_pWorld->GetMouseCase();
				if (pSquare != NULL)
				{
					/*
					if (m_pSelectSquare != NULL && pSquare != m_pSelectSquare && pSquare->GetPos() == m_pWorld->GetBot().GetPos())
					{
						const BLSquare* pTmp = pSquare;
						pSquare = m_pSelectSquare;
						m_pSelectSquare = pTmp;
					}
					*/

					m_pGoalMenu->ConstructFromCase(pSquare, m_pSelectSquare);
					m_pGoalMenu->SetVisible(m_pGoalMenu->GetGoals().size() > 0);

					if (m_pGoalMenu->IsVisible())
					{
						m_pGoalMenu->UpdatePos();
					}
					else
					{
						if (pSquare->GetProp() != NULL || m_pWorld->GetBot().GetPos() == pSquare->GetPos())
						{
							m_pSelectSquare = (m_pSelectSquare == pSquare ? NULL : pSquare);
						}
						else
						{
							m_pSelectSquare = NULL;
						}
					}
				}
			}
			else
			{
				m_pGoalMenu->Click();				
				m_pGoalMenu->SetVisible(false);
				m_pSelectSquare = NULL;
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

		//SetPause(m_pGoalMenu->IsVisible());
	}

	IBGPlanner& oPlanner = (IBGPlanner&)m_pWorld->GetBot().GetPlanner();

	if (m_pEngine->GetInput()->GetVirtualKey(MOUSE_RIGHT) == KeyPressed)
	{
		if (m_pWorldCanva->IsMouseInside())
			m_pWorld->StartDrag();
		else if (m_pGraphCanva->IsMouseInside())
			oPlanner.StartDrag();
	}
	else if (m_pEngine->GetInput()->GetVirtualKey(MOUSE_RIGHT) == KeyDown)
	{
		if (m_pWorld->IsDraging())
			m_pWorld->UpdateDrag();
		else if (oPlanner.IsDraging())
			oPlanner.UpdateDrag();
	}
	else if (m_pEngine->GetInput()->GetVirtualKey(MOUSE_RIGHT) == KeyUp)
	{
		m_pWorld->StopDrag();
		oPlanner.StopDrag();
	}

	if (m_pGoalMenu->IsVisible())
	{
		m_pGoalMenu->Update();
	}

}

int BLApp::Draw()
{
	m_pWorld->Draw();

	int x = (m_pWorld->GetCanvas().GetMouseX() / m_pWorld->GetGridSize()) * m_pWorld->GetGridSize();
	int y = (m_pWorld->GetCanvas().GetMouseY() / m_pWorld->GetGridSize()) * m_pWorld->GetGridSize();

	if (!m_pWorld->IsDraging())
		m_pWorld->GetCanvas().DrawRect(x, y, m_pWorld->GetGridSize()-1, m_pWorld->GetGridSize()-1, 255, 255, 255);

	if (m_pSelectSquare != NULL)
	{
		m_pWorld->GetCanvas().DrawRect(m_pSelectSquare->GetPos().x*m_pWorld->GetGridSize()-1, m_pSelectSquare->GetPos().y*m_pWorld->GetGridSize()-1, m_pWorld->GetGridSize(), m_pWorld->GetGridSize(), 0, 255, 0);
	}

	((IBGPlanner&)m_pWorld->GetBot().GetPlanner()).Draw();

	if (m_pGoalMenu->IsVisible())
	{
		m_pGoalMenu->Draw();
	}

	return 0;
}


