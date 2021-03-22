#include "IBotTestApp.h"
#include "IBPlannerTest.h"
#include "World/IBCubeWorld.h"
#include "Graph/IBGraphPlannerDisplay.h"
#include "Tree/IBTreePlannerDisplay.h"
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

	//m_pPlannerDisplay = new IBGraphPlannerDisplay(*m_pGraphCanva, *m_pPlanner);
	m_pPlannerDisplay = new IBTreePlannerDisplay(*m_pGraphCanva, *m_pPlanner);

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

	m_pPlannerDisplay->Refresh();
}

int IBotTestApp::Update(float dt)
{
	if (m_pEngine->GetEventManager()->GetVirtualKey(KEY_SPACE) == KeyReleased)
	{
		m_pPlanner->Step(true, false);
		m_pPlannerDisplay->Refresh();
	}

	m_pPlannerDisplay->Update(dt);

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

	m_pEngine->Print(5, 45, m_pEngine->GetPrintFont(), 10, ETextAlign::LeftTop, Color(255, 255, 255), "%d %d", m_pGraphCanva->GetOrigX(), m_pGraphCanva->GetOrigY());

	return 0;
}


