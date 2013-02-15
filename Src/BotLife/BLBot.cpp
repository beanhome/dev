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

float BLBot::s_fDirArrayX[8] = { 0.f, 1.f, 1.f, 1.f, 0.f, -1.f, -1.f, -1.f};
float BLBot::s_fDirArrayY[8] = { 1.f, 1.f, 0.f, -1.f, -1.f, -1.f, 0.f, 1.f};
Vector2 BLBot::s_vDirArray[8] = { Vector2(0,1), Vector2(1,1), Vector2(1,0), Vector2(1,-1), Vector2(0,-1), Vector2(-1,-1), Vector2(-1,0), Vector2(-1,1) };


BLBot::BLBot(GEngine& ge, BLWorld& oWorld)
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
	m_pWalkImage = new ImageFlipBook(ge, ge.GetImageResource(DATA_DIR "/BotLife/peasant_walk.png"), 8, 5);
	m_pWalkImage->SetCenter(16, 25);
	//m_iWidth = 32;
	//m_iHeight = 32;
	m_pWalkImage->SetCurrent(0);

	m_pWorkImage = new ImageFlipBook(ge, ge.GetImageResource(DATA_DIR "/BotLife/peasant_work.png"), 8, 5);
	m_pWorkImage->SetCenter(24, 35);
	m_pWorkImage->SetCurrent(0);

	m_pPlanner = new IBPlanner_BL(this);
}

BLBot::~BLBot()
{
	delete m_pWalkImage;
	delete m_pPlanner;
}

void BLBot::SetLoc(float x, float y)
{
	m_fLocX = x;
	m_fLocY = y;
	
	//m_vPos.x = (int)x / m_oWorld.GetGridSize();
	//m_vPos.y = (int)y / m_oWorld.GetGridSize();

	m_pWalkImage->SetPos((sint)x, (sint)y);
	m_pWorkImage->SetPos((sint)x, (sint)y);
}

void BLBot::SetPos(int i, int j)
{
	//SetLoc((float)(i * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2), (float)(j * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2));

	m_vPos.x = i;
	m_vPos.y = j;
}

void BLBot::SetPos(const Vector2& p)
{
	m_vPos = p;
}

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


void BLBot::SetState(BotState state, BotDir dir, float delay)
{
	m_eState = state;
	m_eDir = dir;
	m_vTarget = m_vPos + s_vDirArray[dir];
	m_fStateDelay = delay;
	m_fStateTime = 0.f;
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

	float t = min(m_fStateTime / m_fStateDelay, 1.f);
	float fGrid = (float)m_oWorld.GetGridSize();
	float fSpeed = fGrid / m_fStateDelay;

	switch (m_eState)
	{
		case Idle:
			m_pWalkImage->SetCurrent(0);
			//m_eDir = Down;
			break;

		case Walk:
			m_pWalkImage->SetCurrent((m_eDir*m_pWalkImage->GetColCount()) + (int)((float) m_pWalkImage->GetColCount() * t));
			SetLoc(m_fLocX + s_fDirArrayX[m_eDir] * fSpeed * dt, m_fLocY + s_fDirArrayY[m_eDir] * fSpeed * dt);
			break;

		case Action:
			m_pWorkImage->SetCurrent(((m_eDir)*m_pWorkImage->GetColCount()) + (int)((float) m_pWorkImage->GetColCount() * t));
			break;

		default:
			assert(false);
	}

	if (m_fStateTime > m_fStateDelay)
	{
		m_eState = Idle;
		m_fStateTime = 0.f;
		m_fStateDelay = -1.f;
	}

	m_fStepTime += dt;
	if (m_fStepTime > m_fStepDelay)
	{
		m_pPlanner->Step();
		m_fStepTime = 0.f;
	}
}


void BLBot::Draw(CanvasBase& canva) const
{
	switch (m_eState)
	{
		case Idle:
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

	/*
	for (uint i=1 ; i<m_oPath.GetLength() ; ++i)
	{
		int x1 = m_oPath.GetList()[i-1].x * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2;
		int y1 = m_oPath.GetList()[i-1].y * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2;
		int x2 = m_oPath.GetList()[i].x * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2;
		int y2 = m_oPath.GetList()[i].y * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2;

		canva.DrawLine(x1, y1, x2, y2, Color(0, 255, 0));

		x1 = m_vPos.x * m_oWorld.GetGridSize();
		y1 = m_vPos.y * m_oWorld.GetGridSize();

		canva.DrawRect(x1, y1, m_oWorld.GetGridSize(), m_oWorld.GetGridSize(), 255, 0, 0);
	}
	*/
}
