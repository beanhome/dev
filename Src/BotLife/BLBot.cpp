#include "BLBot.h"
#include "CanvasBase.h"
#include "ImageFlipBook.h"
#include "GEngine.h"
#include "ImageResource.h"
#include "BLWorld.h"

float BLBot::s_fDirArrayX[4] = { 0.f, 1.f, 0.f, -1.f};
float BLBot::s_fDirArrayY[4] = { 1.f, 0.f, -1.f, 0.f};
Vector2 BLBot::s_vDirArray[4] = { Vector2(0,1), Vector2(1,0), Vector2(0,-1), Vector2(-1,0) };



BLBot::BLBot(GEngine& ge, BLWorld& oWorld)
	: IBObject("Bot")
	, m_oWorld(oWorld)
	, m_pImage(NULL)
	, m_eState(Idle)
{
	m_pImage = new ImageFlipBook(ge, ge.GetImageResource(DATA_DIR "/Test/Bomberman.png"), 4, 5);
	m_iWidth = 20;
	m_iHeight = 32;
	m_iCenterX = 10;
	m_iCenterY = 28;
	m_iAnimImgcount = 5;

	m_pImage->SetCurrent(0);

	m_pNavDijkstra = new NavDijkstra<BLSquare>(m_oWorld.GetGrid(), false);
	//m_pNavDijkstra->FindPath(Vector2(1, 1), Cond_Dist<BLSquare>(Vector2(14, 14), 0), m_oPath);
	//m_pNavDijkstra->FindPath(Vector2(1, 1), Vector2(14, 14), 0, m_oPath);
	m_pNavDijkstra->Navigation::FindPath(Vector2(1, 1), Vector2(14, 14), m_oPath);

	m_pNavAStar = new NavAStar<BLSquare>(m_oWorld.GetGrid(), false);
	//m_pNavAStar->FindPath(Vector2(1, 1), Vector2(14, 14), 0, m_oPath);
	//m_pNavAStar->Navigation::FindPath(Vector2(1, 1), Vector2(14, 14), m_oPath);
}

BLBot::~BLBot()
{
	delete m_pImage;
	delete m_pNavDijkstra;
	delete m_pNavAStar;
}

void BLBot::SetPos(float x, float y)
{
	m_fLocX = x;
	m_fLocY = y;
	
	m_vPos.x = (int)x / m_oWorld.GetGridSize();
	m_vPos.y = (int)y / m_oWorld.GetGridSize();

	m_pImage->SetPos((sint)x - (m_iCenterX - m_iWidth/2), (sint)y - m_iHeight/2 + (m_iHeight - m_iCenterY));
}

void BLBot::SetLoc(float i, float j)
{
	SetPos(i * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2, j * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2);
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
	return (Start.x == Target.x ? (Target.y > Start.y ? Down : Up) : (Target.x < Start.x ? Left : Right));
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
			m_pImage->SetCurrent(2);
			break;

		case Walk:
			m_pImage->SetCurrent((m_eDir*m_iAnimImgcount) + (int)((float) m_iAnimImgcount * t));
			SetPos(m_fLocX + s_fDirArrayX[m_eDir] * fSpeed * dt, m_fLocY + s_fDirArrayY[m_eDir] * fSpeed * dt);
			break;

		case Action:
			m_pImage->SetCurrent(2);
			break;

		default:
			assert(false);
	}

	if (m_fStateTime > m_fStateDelay)
	{
		if (m_oPath.GetLength() > 0 && m_oPath.GetStart() == m_vPos)
		{
			m_vTarget = m_oPath.PopFront();
			m_eDir = ComputeDir(m_vPos, m_vTarget);

			SetState(Walk, m_eDir, 1.f);
		}
		else
		{
			m_eState = Idle;
			m_fStateTime = 0.f;
			m_fStateDelay = -1.f;
		}
	}

}


void BLBot::Draw(CanvasBase& canva) const
{
	m_pImage->Draw();

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
}
