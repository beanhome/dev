#include "BLBot.h"
#include "CanvasBase.h"
#include "ImageFlipBook.h"
#include "GEngine.h"
#include "ImageResource.h"
#include "BLWorld.h"
#include "IBPlanner.h"
#include "IBPlanner_BL.h"
#include "BLGoal.h"
#include "BLApp.h"
#include "Vector2.h"
#include "World/BLProp.h"
#include "Canvas.h"
#include "BotAction/BotAction.h"

const char* BLBot::s_sStateString[BotState_MAX] =
{
	"Idle",
	"Walk",
	"Action",
	"Push"
};


const char* BLBot::s_sDirString[8] =
{
	"Down",
	"DownRight",
	"Right",
	"UpRight",
	"Up",
	"UpLeft",
	"Left",
	"DownLeft"
};

float BLBot::s_fDirArrayX[8] = { 0.f, 1.f, 1.f, 1.f, 0.f, -1.f, -1.f, -1.f};
float BLBot::s_fDirArrayY[8] = { 1.f, 1.f, 0.f, -1.f, -1.f, -1.f, 0.f, 1.f};
Vector2 BLBot::s_vDirArray[8] = { Vector2(0,1), Vector2(1,1), Vector2(1,0), Vector2(1,-1), Vector2(0,-1), Vector2(-1,-1), Vector2(-1,0), Vector2(-1,1) };


BLBot::BLBot(GEngine& ge, BLWorld& oWorld, CanvasBase& oPlannerCanvas)
	: BLActor("Bot")
	, m_oWorld(oWorld)
	, m_pWalkImage(nullptr)
	, m_pWorkImage(nullptr)
	, m_eState(Idle)
	, m_eDir(BotDir::Down)
	, m_pCurrentAction(nullptr)
	, m_pPendingAction(nullptr)
	, m_fStepTime(0.f)
	, m_fStepDelay(0.1f)
	, m_pCarryObject(nullptr)
	, m_pPushObject(nullptr)
{
	m_pIdleImage = new ImageFlipBook(oWorld.GetCanvas(), ge.GetImageResource(DATA_DIR "/BotLife/peasant_idle.png"), 8, 1);
	m_pIdleImage->SetCenter(16, 25);
	m_pIdleImage->SetCurrent(0);

	m_pWalkImage = new ImageFlipBook(oWorld.GetCanvas(), ge.GetImageResource(DATA_DIR "/BotLife/peasant_walk.png"), 8, 6);
	m_pWalkImage->SetCenter(16, 25);
	m_pWalkImage->SetCurrent(0);

	m_pWorkImage = new ImageFlipBook(oWorld.GetCanvas(), ge.GetImageResource(DATA_DIR "/BotLife/peasant_work.png"), 8, 5);
	m_pWorkImage->SetCenter(24, 35);
	m_pWorkImage->SetCurrent(0);

	m_pPlanner = new IBPlanner_BL(this);
}

BLBot::~BLBot()
{
	if (m_pCarryObject != nullptr)
		delete m_pCarryObject;

	delete m_pIdleImage;
	delete m_pWalkImage;
	delete m_pWorkImage;
	delete m_pPlanner;
}

void BLBot::SetLoc(float x, float y)
{
	m_fLocX = x;
	m_fLocY = y;
	
	m_pWalkImage->SetPos((sint)x, (sint)y);
	m_pWorkImage->SetPos((sint)x, (sint)y);
	m_pIdleImage->SetPos((sint)x, (sint)y);
}

void BLBot::FixLoc()
{
	SetLoc((float)m_vPos.x * m_oWorld.GetGridSize()/* + m_oWorld.GetGridSize()/2*/, (float)m_vPos.y * m_oWorld.GetGridSize()/* + m_oWorld.GetGridSize()/2*/);
}


void BLBot::SetPos(int i, int j)
{
	m_vPos.x = i;
	m_vPos.y = j;
}

void BLBot::SetPos(const Vector2& p)
{
	m_vPos = p;
}

void BLBot::AddGoal(const BLGoal& oGoal)
{
	m_aGoals.push_back(oGoal);
	BLGoal& oOwnedGoal = m_aGoals.back();

	ASSERT(m_pPlanner != nullptr);
	
	m_pPlanner->AddGoal(oOwnedGoal.GetFact()->Clone());
}

void BLBot::AddGoal(const string& name) { ASSERT(m_pPlanner != nullptr); m_pPlanner->AddGoal(name, true); }
void BLBot::AddGoal(const string& name, IBObject* pUserData) { ASSERT(m_pPlanner != nullptr); m_pPlanner->AddGoal(name, true, pUserData); }
void BLBot::AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2) { ASSERT(m_pPlanner != nullptr); m_pPlanner->AddGoal(name, true, pUserData1, pUserData2); }
void BLBot::AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3) { ASSERT(m_pPlanner != nullptr); m_pPlanner->AddGoal(name, true, pUserData1, pUserData2, pUserData3); }

bool BLBot::StartAction(BotAction* pAction)
{
	if (m_pPendingAction != nullptr)
		return false;

	m_pPendingAction = pAction;
	return true;
}

void BLBot::PickProp(BLProp* pProp)
{
	ASSERT(m_pCarryObject == nullptr);

	BLSquare& sq = GetWorld().GetGrid().GetCase(pProp->GetPos());
	ASSERT(sq.GetProp() == pProp);
	sq.SetProp(nullptr);

	m_pCarryObject = pProp;
	pProp->SetVisible(false);
}

void BLBot::DropObject(BLProp* pProp, const Vector2& pos)
{
	ASSERT(m_pCarryObject == pProp);

	BLSquare& sq = GetWorld().GetGrid().GetCase(pos);
	ASSERT(sq.GetProp() == nullptr);
	ASSERT(GetWorld().GetGrid().Distance(pos, GetPos()) <= 1);

	sq.SetProp(pProp);
	m_pCarryObject = nullptr;
	pProp->SetVisible(true);
	pProp->SetPos(pos);
}


void BLBot::SetState(BotState state, BotDir dir, float delay, BLProp* pObj)
{
	m_eState = state;
	m_eDir = dir;
	m_pPushObject = pObj;
}


void BLBot::SetDir(BotDir eDir)
{
	m_eDir = eDir;
}

void BLBot::SetDir(const Vector2& vTarget)
{
	SetDir(ComputeDir(m_vPos, vTarget));
}

BLBot::BotDir BLBot::ComputeDir(const Vector2& Target) const
{
	const Vector2& Start = GetPos();

	ASSERT(Start != Target);
	ASSERT(abs(Start.x - Target.x) <= 1);
	ASSERT(abs(Start.y - Target.y) <= 1);

	for (uint i = 0; i < 8; ++i)
		if (Target - Start == s_vDirArray[i])
			return (BLBot::BotDir)i;

	return Down;
}

BLBot::BotDir BLBot::ComputeDir(const Vector2& Start, const Vector2& Target) const
{
	ASSERT(Start != Target);
	ASSERT(abs(Start.x - Target.x) <= 1);
	ASSERT(abs(Start.y - Target.y) <= 1);

	for (uint i=0 ; i<8 ; ++i)
		if (Target - Start == s_vDirArray[i]) 
			return (BLBot::BotDir)i;

	return Down;
}


void BLBot::Update(float dt)
{
	if (m_pCurrentAction == nullptr)
	{
		if (m_pPendingAction != nullptr)
		{
			m_pCurrentAction = m_pPendingAction;
			m_pPendingAction = nullptr;

			m_pCurrentAction->m_dOnFinish.AddLambda([this](bool bInterrupted) { m_pCurrentAction = nullptr; });
			m_pCurrentAction->Start();
		}
	}

	if (m_pCurrentAction != nullptr)
	{
		m_pCurrentAction->Update(dt);
	}


	float t = (m_pCurrentAction != nullptr ? m_pCurrentAction->GetProgression() : 0.f);

	m_pIdleImage->SetCurrent(m_eDir);
	m_pWalkImage->SetCurrent((m_eDir*m_pWalkImage->GetColCount()) + (int)((float)m_pWalkImage->GetColCount() * t));
	m_pWorkImage->SetCurrent(((m_eDir)*m_pWorkImage->GetColCount()) + (int)((float)m_pWorkImage->GetColCount() * t));

	m_fStepTime += dt;
	if (m_fStepTime > m_fStepDelay)
	{
		m_pPlanner->Step();
		m_fStepTime = 0.f;
		//m_oWorld.GetApp().SetPause(true);
	}

	//LOG("Dir : %s\n", s_sDirString[m_eDir]);
}


void BLBot::Draw() const
{
	switch (m_eState)
	{
		case Idle:
			m_pIdleImage->Draw();
			break;

		case Walk:
		case Push:
			m_pWalkImage->Draw();
			break;

		case Action:
			m_pWorkImage->Draw();
			break;

		default:
			ASSERT(false);
	}

	if (m_pCarryObject != nullptr)
		m_oWorld.GetCanvas().DrawImage(*m_pCarryObject->GetImageResource(), (sint16)m_fLocX, (sint16)m_fLocY, 0, 0.8f);

	//m_oWorld.GetCanvas().DrawRect(m_vPos.x * m_oWorld.GetGridSize(), m_vPos.y * m_oWorld.GetGridSize(), m_oWorld.GetGridSize()-1, m_oWorld.GetGridSize()-1, 255, 255, 255);
	//m_oWorld.GetCanvas().DrawRect(m_vTarget.x * m_oWorld.GetGridSize(), m_vTarget.y * m_oWorld.GetGridSize(), m_oWorld.GetGridSize()-1, m_oWorld.GetGridSize()-1, 0, 255, 255);

	m_oWorld.GetCanvas().GetGEngine()->SetPrintParameter(20, 20, m_oWorld.GetCanvas().GetPrintFont(), 12, LeftTop, Color(255, 255, 255));
	m_oWorld.GetCanvas().GetGEngine()->Print("State : %s", s_sStateString[m_eState]);
	m_oWorld.GetCanvas().GetGEngine()->Print("Dir : %s", s_sDirString[m_eDir]);
	m_oWorld.GetCanvas().GetGEngine()->Print("Pos X : %8.3f (%8.3f)", m_fLocX, m_fLocX - (float)m_vPos.x * (float)m_oWorld.GetGridSize());
	m_oWorld.GetCanvas().GetGEngine()->Print("Pos Y : %8.3f (%8.3f)", m_fLocY, m_fLocY - (float)m_vPos.y * (float)m_oWorld.GetGridSize());
}
