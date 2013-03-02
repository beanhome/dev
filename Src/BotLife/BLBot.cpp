#include "BLBot.h"
#include "CanvasBase.h"
#include "ImageFlipBook.h"
#include "GEngine.h"
#include "ImageResource.h"
#include "BLWorld.h"
#include "IBPlanner_BL.h"
#include "World\IBVector2.h"
#include "World\BLProp.h"
#include "Canvas.h"

/*
Down,
DownRight,
Right,
UpRight,
Up,
UpLeft,
Left,
DownLeft
*/

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
	: IBObject("Bot")
	, m_oWorld(oWorld)
	, m_pWalkImage(NULL)
	, m_pWorkImage(NULL)
	, m_vPos("Current")
	, m_eState(Idle)
	, m_fStateTime(0.f)
	, m_fStateDelay(0.2f)
	, m_fStepTime(0.f)
	, m_fStepDelay(0.1f)
	, m_pCarryObject(NULL)
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

	m_pPlanner = new IBPlanner_BL(this, oPlannerCanvas);
}

BLBot::~BLBot()
{
	if (m_pCarryObject != NULL)
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
	SetLoc((float)m_vPos.x * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2, (float)m_vPos.y * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2);
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

void BLBot::AddGoal(const IBGoal& goal) { ASSERT(m_pPlanner != NULL); m_pPlanner->AddGoal(goal); }
void BLBot::AddGoal(const string& name) { ASSERT(m_pPlanner != NULL); m_pPlanner->AddGoal(name); }
void BLBot::AddGoal(const string& name, IBObject* pUserData) { ASSERT(m_pPlanner != NULL); m_pPlanner->AddGoal(name, pUserData); }
void BLBot::AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2) { ASSERT(m_pPlanner != NULL); m_pPlanner->AddGoal(name, pUserData1, pUserData2); }
void BLBot::AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3) { ASSERT(m_pPlanner != NULL); m_pPlanner->AddGoal(name, pUserData1, pUserData2, pUserData3); }

void BLBot::PickProp(BLProp* pProp)
{
	ASSERT(m_pCarryObject == NULL);

	BLSquare& sq = GetWorld().GetGrid().GetCase(pProp->GetPos());
	ASSERT(sq.GetProp() == pProp);
	sq.SetProp(NULL);

	m_pCarryObject = pProp;
	pProp->SetVisible(false);
}

void BLBot::DropObject(BLProp* pProp, const IBVector2& pos)
{
	ASSERT(m_pCarryObject == pProp);

	BLSquare& sq = GetWorld().GetGrid().GetCase(pos);
	ASSERT(sq.GetProp() == NULL);
	ASSERT(GetWorld().GetGrid().Distance(pos, GetPos()) <= 1);

	sq.SetProp(pProp);
	m_pCarryObject = NULL;
	pProp->SetVisible(true);
	pProp->SetPos(pos);
}


void BLBot::SetState(BotState state, BotDir dir, float delay)
{
	if (m_eState == state)
	{
		m_fStateTime -= m_fStateDelay;
	}
	else
	{
		m_fStateTime = 0.f;
		m_fStateDelay = delay;
	}

	m_eState = state;
	m_eDir = dir;
	m_vTarget = m_vPos + s_vDirArray[dir];
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
	if (m_fStateDelay > 0.f)
		m_fStateTime += dt;

	if (m_fStateTime > m_fStateDelay)
	{
		//m_eState = Idle;
		m_pPlanner->Step();
		m_fStepTime = 0.f;
		//m_fStateTime = 0.f;
		//m_fStateDelay = -1.f;
		//m_oWorld.GetApp().SetPause(true);
	}
	else
	{
		float t = min(m_fStateTime / m_fStateDelay, 0.999999f);
		float fGrid = (float)m_oWorld.GetGridSize();
		float fSpeed = fGrid / m_fStateDelay;

		switch (m_eState)
		{
			case Idle:
				m_pIdleImage->SetCurrent(m_eDir);
				FixLoc();
				break;

			case Walk:
				//LOG("Image : %f %d\n", t, (int)((float) m_pWalkImage->GetColCount() * t));
				m_pWalkImage->SetCurrent((m_eDir*m_pWalkImage->GetColCount()) + (int)((float) m_pWalkImage->GetColCount() * t));
				//SetLoc(m_fLocX + s_fDirArrayX[m_eDir] * fSpeed * dt, m_fLocY + s_fDirArrayY[m_eDir] * fSpeed * dt);
				SetLoc( (float)(m_oWorld.GetGridSize()/2 + m_vPos.x * (int)m_oWorld.GetGridSize()) + (float)((m_vTarget.x - m_vPos.x) * (int)m_oWorld.GetGridSize()) * t, (float)(m_oWorld.GetGridSize()/2 + m_vPos.y * (int)m_oWorld.GetGridSize()) + (float)((m_vTarget.y - m_vPos.y) * (int)m_oWorld.GetGridSize()) * t);
				break;

			case Action:
				m_pWorkImage->SetCurrent(((m_eDir)*m_pWorkImage->GetColCount()) + (int)((float) m_pWorkImage->GetColCount() * t));
				FixLoc();
				break;

			default:
				assert(false);
		}
	}

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
			m_pWalkImage->Draw();
			break;

		case Action:
			m_pWorkImage->Draw();
			break;

		default:
			ASSERT(false);
	}

	if (m_pCarryObject != NULL)
		m_oWorld.GetCanvas().DrawImage(*m_pCarryObject->GetImageResource(), (sint16)m_fLocX, (sint16)m_fLocY, 0, 0.8f);

	//m_oWorld.GetCanvas().DrawRect(m_vPos.x * m_oWorld.GetGridSize(), m_vPos.y * m_oWorld.GetGridSize(), m_oWorld.GetGridSize()-1, m_oWorld.GetGridSize()-1, 255, 255, 255);
	//m_oWorld.GetCanvas().DrawRect(m_vTarget.x * m_oWorld.GetGridSize(), m_vTarget.y * m_oWorld.GetGridSize(), m_oWorld.GetGridSize()-1, m_oWorld.GetGridSize()-1, 0, 255, 255);

	//m_oWorld.GetCanvas().GetGEngine()->SetPrintParameter(20, 20, m_oWorld.GetCanvas().GetPrintFont(), 12, LeftTop, Color(255, 255, 255));
	//m_oWorld.GetCanvas().GetGEngine()->Print("State : %d", m_eState);
	//m_oWorld.GetCanvas().GetGEngine()->Print("Dir : %s", s_sDirString[m_eDir]);
	//m_oWorld.GetCanvas().GetGEngine()->Print("Pos X : %8.3f (%8.3f)", m_fLocX, m_fLocX - (float)m_vPos.x * (float)m_oWorld.GetGridSize());
	//m_oWorld.GetCanvas().GetGEngine()->Print("Pos Y : %8.3f (%8.3f)", m_fLocY, m_fLocY - (float)m_vPos.y * (float)m_oWorld.GetGridSize());


}
