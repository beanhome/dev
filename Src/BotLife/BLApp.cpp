#include "BLApp.h"
#include "Canvas.h"
#include "BLWorld.h"
#include "BLBot.h"
#include "Map/BLSquare.h"
#include "BLGoalMenu.h"

#include "Graph/IBGraphPlannerDisplay.h"

#include "GEngine.h"
#include "Event.h"
#include "EventManager.h"

BLApp::BLApp(int w, int h, const char* rootpath, float r, int sx, int sy, const char* tilesname)
	: GApp<GEngine_SDL>(w, h, rootpath)
	, m_pGoalMenu(nullptr)
	, m_pSelectSquare(nullptr)
{
	m_pEngine->SetPrintFont(FONT_PATH, 14);

	m_pWorldCanva = new Canvas(*m_pEngine, 0, 0, w, (uint16)(r*(float)h));
	m_pGraphCanva = new Canvas(*m_pEngine, 0, (sint16)(r*(float)h), w, (uint16)((1.f-r)*(float)h));

	m_pWorld = new BLWorld(*this, *m_pWorldCanva, sx, sy, tilesname);

	m_pGoalMenu = new BLGoalMenu(*m_pEngine, m_pWorld->GetBot());

	m_pPlannerDisplay = new IBGraphPlannerDisplay(*m_pGraphCanva, m_pWorld->GetBot().GetPlanner());
}

BLApp::~BLApp()
{
	delete m_pWorldCanva;
	delete m_pGraphCanva;

	delete m_pGoalMenu;
	delete m_pWorld;

	delete m_pPlannerDisplay;
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
	if (m_pEngine->GetEventManager()->GetVirtualKey(MOUSE_LEFT) == KeyPressed)
	{
		if (m_pWorldCanva->IsMouseInside())
		{
			if (!m_pGoalMenu->IsVisible())
			{
				const BLSquare* pSquare = m_pWorld->GetMouseCase();
				if (pSquare != nullptr)
				{
					/*
					if (m_pSelectSquare != nullptr && pSquare != m_pSelectSquare && pSquare->GetPos() == m_pWorld->GetBot().GetPos())
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
						if (pSquare->GetProp() != nullptr || m_pWorld->GetBot().GetPos() == pSquare->GetPos())
						{
							m_pSelectSquare = (m_pSelectSquare == pSquare ? nullptr : pSquare);
						}
						else
						{
							m_pSelectSquare = nullptr;
						}
					}
				}
			}
			else
			{
				m_pGoalMenu->Click();				
				m_pGoalMenu->SetVisible(false);
				m_pSelectSquare = nullptr;
			}
		}
		/*
		else if (m_pGraphCanva->IsMouseInside())
		{
			m_pGoalMenu->SetVisible(false);
			const FactSet& oGoals = m_pWorld->GetBot().GetPlanner().GetGoals();

			for (FactSet::const_iterator it = oGoals.begin() ; it != oGoals.end() ; ++it)
			{
				IBGFact* pFact = static_cast<IBGFact*>(*it);
				if (pFact->GetFactBox()->GetCanvas().IsMouseInside())
				{
					pFact->PrepareToDestroy();
					break;
				}
			}
		}
		*/

		//SetPause(m_pGoalMenu->IsVisible());
	}

	if (m_pEngine->GetEventManager()->GetVirtualKey(MOUSE_RIGHT) == KeyPressed)
	{
		if (m_pWorldCanva->IsMouseInside())
			m_pWorld->StartDrag();
		else if (m_pGraphCanva->IsMouseInside())
			m_pPlannerDisplay->StartDrag();
	}
	else if (m_pEngine->GetEventManager()->GetVirtualKey(MOUSE_RIGHT) == KeyDown
		|| m_pEngine->GetEventManager()->GetVirtualKey(MOUSE_RIGHT) == KeyRepeat)
	{
		m_pWorld->UpdateDrag();
		m_pPlannerDisplay->UpdateDrag();
	}
	else if (m_pEngine->GetEventManager()->GetVirtualKey(MOUSE_RIGHT) == KeyUp)
	{
		m_pWorld->StopDrag();
		m_pPlannerDisplay->StopDrag();
	}

	if (m_pEngine->GetEventManager()->GetVirtualKey(KEY_SPACE) == KeyPressed)
		SetPause(!IsPaused());

	if (m_pGoalMenu->IsVisible())
		m_pGoalMenu->Update();
}

int BLApp::Draw()
{
	m_pWorld->Draw();
	

	int x = (m_pWorld->GetCanvas().GetMouseX() / m_pWorld->GetGridSize()) * m_pWorld->GetGridSize();
	int y = (m_pWorld->GetCanvas().GetMouseY() / m_pWorld->GetGridSize()) * m_pWorld->GetGridSize();

	if (!m_pWorld->IsDraging())
		m_pWorld->GetCanvas().DrawRect(x, y, m_pWorld->GetGridSize()-1, m_pWorld->GetGridSize()-1, 255, 255, 255);

	if (m_pSelectSquare != nullptr)
	{
		m_pWorld->GetCanvas().DrawRect(m_pSelectSquare->GetPos().x*m_pWorld->GetGridSize()-1, m_pSelectSquare->GetPos().y*m_pWorld->GetGridSize()-1, m_pWorld->GetGridSize(), m_pWorld->GetGridSize(), 0, 255, 0);
	}

	const BLSquare* pSquare = m_pWorld->GetMouseCase();
	if (pSquare != nullptr)
		m_pWorldCanva->GetGEngine()->Print(5, m_pWorldCanva->GetHeight()-5, m_pWorld->GetCanvas().GetPrintFont(), 12, LeftBottom, Color(255, 255, 255), "%d %d", pSquare->GetPos().x, pSquare->GetPos().y);

	m_pPlannerDisplay->DrawGraph();

	if (m_pGoalMenu->IsVisible())
	{
		m_pGoalMenu->Draw();
	}

	return 0;
}


