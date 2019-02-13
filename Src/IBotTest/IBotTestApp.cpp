#include "IBotTestApp.h"
#include "IBPlannerTest.h"
#include "World/IBCubeWorld.h"
#include "Graph/IBGraphPlannerDisplay.h"
#include "Graph/IBGPlanBox.h"
#include "Graph/IBGWorldChangeBox.h"
#include "Canvas.h"
#include "GEngine.h"
#include "Event.h"
#include "EventManager.h"

IBotTestApp::IBotTestApp(int w, int h, int sx, int sy, float r, const char* rootpath)
	: GApp<GEngine_SDL>(w, h, rootpath)
{
	m_pEngine->SetPrintFont(FONT_PATH, 14);

	m_pWorldCanva = new Canvas(*m_pEngine, 0, 0, w, (uint16)(r*(float)h));
	m_pGraphCanva = new Canvas(*m_pEngine, 0, (sint16)(r*(float)h), w, (uint16)((1.f - r)*(float)h));

	m_pWorld = new IBCubeWorld();

	m_pPlanner = new IBPlannerTest(m_pWorld);

	m_pPlannerDisplay = new IBGraphPlannerDisplay(*m_pGraphCanva, *m_pPlanner);

}

IBotTestApp::~IBotTestApp()
{
	delete m_pPlannerDisplay;
	delete m_pPlanner;
	delete m_pWorld;
	delete m_pGraphCanva;
	delete m_pWorldCanva;
}

void IBotTestApp::Init()
{
	m_pWorld->Init(0);
	m_pWorld->Print();

	m_pPlanner->AddGoal("IBFactDef_IsTopOf", true, m_pWorld->GetCubeB(), m_pWorld->GetCubeC());
	m_pPlanner->AddGoal("IBFactDef_IsTopOf", true, m_pWorld->GetCubeA(), m_pWorld->GetCubeB());
	//m_pPlanner->AddGoal("IBFactDef_IsTopOf", true, m_pWorld->GetCubeC(), m_pWorld->GetCubeD());

	/* Test
	m_pPlanner->AddGoal("IBFactDef_IsOnTable", true, m_pWorld->GetCubeB());
	m_pPlanner->AddGoal("IBFactDef_IsFree", true, m_pWorld->GetCubeB());
	m_pPlanner->AddGoal("IBFactDef_IsFree", true, m_pWorld->GetCubeC());
	m_pPlanner->AddGoal("IBFactDef_IsTopOf", true, m_pWorld->GetCubeA(), m_pWorld->GetCubeB());
	*/
}

int IBotTestApp::Update(float dt)
{
	if (m_pEngine->GetEventManager()->GetVirtualKey(MOUSE_LEFT) == KeyPressed)
	{
		m_pPlannerDisplay->StartDrag();
	}
	else if (m_pEngine->GetEventManager()->GetVirtualKey(MOUSE_LEFT) == KeyDown
		|| m_pEngine->GetEventManager()->GetVirtualKey(MOUSE_LEFT) == KeyRepeat)
	{
		m_pPlannerDisplay->UpdateDrag();
	}
	else
	{
		m_pPlannerDisplay->StopDrag();
	}

	if (m_pEngine->GetEventManager()->GetVirtualKey(KEY_SPACE) == KeyReleased)
	{
		m_pPlanner->Step(true, false);
		m_pPlannerDisplay->RePanPlan(m_pPlanner);
	}

	if (m_pEngine->GetEventManager()->GetVirtualKey(MOUSE_RIGHT) == KeyDown)
	{
		sint32 x = m_pEngine->GetMouseX() - m_pPlannerDisplay->GetCanvas().GetScreenPosX();
		sint32 y = m_pEngine->GetMouseY() - m_pPlannerDisplay->GetCanvas().GetScreenPosY();
		m_pPlannerDisplay->StartSnap(x, y);
	}

	if (m_pEngine->GetEventManager()->GetVirtualKey(MOUSE_MIDDLE) == KeyPressed)
	{
		const IBWorldChange* pBestNode = m_pPlanner->GetBestNode();
		if (pBestNode != nullptr)
		{
			const IBGWorldChangeBox* pBestNodeBox = m_pPlannerDisplay->GetPlan()->GetWorldChangeBox(pBestNode);
			if (pBestNodeBox != nullptr)
			{
				sint32 x = pBestNodeBox->GetScreenX() - m_pPlannerDisplay->GetCanvas().GetScreenPosX() + pBestNodeBox->GetW() / 2;
				sint32 y = pBestNodeBox->GetScreenY() - m_pPlannerDisplay->GetCanvas().GetScreenPosY() + pBestNodeBox->GetH() / 2;
				m_pPlannerDisplay->StartSnap(x, y);
			}
		}
	}

	if (m_pPlannerDisplay->IsSnaping())
		m_pPlannerDisplay->UpdateSnap(dt);

	return 0;
}

int IBotTestApp::UpdatePause()
{
	return 0;
}


int IBotTestApp::Draw()
{
	m_pWorld->Draw(*m_pWorldCanva);
	m_pPlannerDisplay->DrawGraph();

	//m_pEngine->Print(m_pEngine->GetWidth(), 5, m_pEngine->GetPrintFont(), 20, ETextAlign::RightTop, Color(255, 255, 255), "Step Count : %d", m_pPlanner->GetStepCount());
	m_pEngine->Print(5, 5, m_pEngine->GetPrintFont(), 20, ETextAlign::LeftTop, Color(255, 255, 255), "Step Count : %d", m_pPlanner->GetStepCount());
	
	m_pEngine->Print(5, 30, m_pEngine->GetPrintFont(), 10, ETextAlign::LeftTop, Color(255, 255, 255), "%d %d", m_pPlannerDisplay->GetCanvas().GetOrigX(), m_pPlannerDisplay->GetCanvas().GetOrigY());

	

	return 0;
}


