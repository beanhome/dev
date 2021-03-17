#include "IBotTestApp.h"
#include "IBPlannerTest.h"
#include "World/IBCubeWorld.h"
#include "Graph/IBGraphPlannerDisplay.h"
#include "Graph/IBGPlanBox.h"
#include "Graph/IBGNodeBox.h"
#include "Canvas.h"
#include "GEngine.h"
#include "Event.h"
#include "EventManager.h"

DEFINE_APP(IBotTestApp)

int IBotTestApp::s_iDummy = 42;

IBotTestApp::IBotTestApp(GEngine* pEngine, int argc, char *argv[])
	: GAppBase(pEngine, argc, argv)
{
	int w = m_pEngine->GetWidth();
	int h = m_pEngine->GetHeight();

	float r = GetArgAsFloat('r', 0.3f, argc, argv);

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

void IBotTestApp::Init(int argc, char *argv[])
{
	const char* sInit = GAppBase::GetArgAsString('i', "a b c", argc, argv);
	const char* sGoal = GAppBase::GetArgAsString('g', "abc", argc, argv);

	m_pWorld->Init(sInit);
	m_pWorld->Print();

	for (uint i = 0; i < strlen(sGoal); ++i)
	{
		if (isalpha(sGoal[i]) && i + 1 < strlen(sGoal))
		{
			string sName = FormatString("Cube_%c", toupper(sGoal[i]));
			IBCube* pCube = m_pWorld->GetCube(sName);

			if (pCube == nullptr)
				continue;

			if (isalpha(sGoal[i + 1]))
			{
				string sTarget = FormatString("Cube_%c", toupper(sGoal[i+1]));
				IBCube* pTarget = m_pWorld->GetCube(sTarget);
				if (pTarget)
					m_pPlanner->AddGoal("IBFactDef_IsTopOf", true, pCube, pTarget);
			}
			else if (sGoal[i+1] == '_')
			{
				m_pPlanner->AddGoal("IBFactDef_IsOnTable", true, pCube);
			}
			else if (sGoal[i + 1] == '!')
			{
				m_pPlanner->AddGoal("IBFactDef_IsFree", true, pCube);
			}
		}
	}
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
		const IBNode* pBestNode = m_pPlanner->GetBestNode();
		if (pBestNode != nullptr)
		{
			const IBGNodeBox* pBestNodeBox = m_pPlannerDisplay->GetPlan()->GetNodeBox(pBestNode);
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


