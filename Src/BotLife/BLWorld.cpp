#include "BLWorld.h"
#include "CanvasBase.h"
#include "Canvas.h"
#include "BLBot.h"
#include "InputEvent.h"
#include "GEngine.h"
#include "IBPlanner.h" // To Del
#include "World\BLProp.h"
#include "Path.h"
#include "World\BLProp_SI.h"
#include "World\BLDoor.h"
#include "Map\BLMap.h"

int _map_[16][16] = {
	{ 1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1 },
	{ 1, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1 },
	{ 1, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1 },
	{ 1, 0, 0, 1,  1, 1, 0, 1,  1, 1, 1, 1,  0, 0, 0, 1 },

	{ 1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1 },
	{ 1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1 },
	{ 1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1 },
	{ 1, 0, 0, 0,  0, 0, 0, 1,  1, 0, 0, 0,  0, 0, 0, 1 },

	{ 1, 0, 0, 1,  0, 0, 0, 1,  1, 0, 0, 0,  0, 0, 0, 1 },
	{ 1, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1 },
	{ 1, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1 },
	{ 1, 1, 1, 1,  1, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1 },

	{ 1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1 },
	{ 1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1 },
	{ 1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1,  0, 0, 0, 1 },
	{ 1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1 }
};




BLWorld::BLWorld(Canvas& canva, uint grid)
	: m_oCanva(canva)
	, m_iGrid(grid)
{
	m_iWidth = canva.GetWidth() - canva.GetWidth() % m_iGrid;
	m_iHeight = canva.GetHeight() - canva.GetHeight() % m_iGrid;

	m_oGrid.Init(16, 16);
	for (uint i=0 ; i<m_oGrid.GetWidth() ; ++i)
	{
		for (uint j=0 ; j<m_oGrid.GetHeight() ; ++j)
		{
			m_oGrid[i][j].SetType(_map_[i][j]);
		}
	}

	m_pBot = new BLBot(*canva.GetGEngine(), *this);
	m_pBot->SetLoc(grid*1.5f, grid*1.5f);
	m_pBot->SetPos(1, 1);
	//m_pBot->SetState(BLBot::Walk, BLBot::Down, 1.f);
	//m_pBot->SetState(BLBot::Idle, BLBot::Down, 1.f);

	m_pProp = new BLProp_SI(*this, "Mine", DATA_DIR "/Test/Mine.png", Vector2(2,4));

	BLDoor* pDoor = new BLDoor(*this, "Door", BLDoor::Verti, Vector2(3, 6));
	pDoor->Close();

	//m_pBot->AddGoal("IBFactDef_BotAtPos", new IBVector2("Dest", 14, 14));
	m_pBot->AddGoal("IBFactDef_BotHasObject", m_pProp);
}

BLWorld::~BLWorld()
{
	delete m_pBot;
	delete m_pProp;
}

bool BLWorld::TestPath(const Path& oPath) const
{
	for (uint i=0 ; i<oPath.GetLength() ; ++i)
	{
		const BLSquare& sq = m_oGrid[oPath[i]];
		if (sq.GetProp() != NULL && sq.IsTempBlock())
			return false;
	}

	return true;
}



void BLWorld::Update(float dt)
{
	m_pBot->Update(dt);

	/*
	const InputEvent& ie = m_oCanva.GetGEngine()->GetInputEvent();
	if (m_pBot->GetState() == BLBot::Idle && ie.GetKeyboardEvent() == KeyDown)
	{
		float fDelay = 1.f;
		switch (ie.GetKeyboardKey())
		{
			case KEY_DOWN:	m_pBot->SetState(BLBot::Walk, BLBot::Down, fDelay);		break;
			case KEY_UP:	m_pBot->SetState(BLBot::Walk, BLBot::Up, fDelay);		break;
			case KEY_LEFT:	m_pBot->SetState(BLBot::Walk, BLBot::Left, fDelay);		break;
			case KEY_RIGHT:	m_pBot->SetState(BLBot::Walk, BLBot::Right, fDelay);	break;
		}
	}
	*/

	/*
	static bool step = false;
	if (ie.GetKeyboardEvent() == KeyDown && ie.GetKeyboardKey() == KEY_SPACE && !step)
	{
		m_pBot->GetPlanner().Step();
		step = true;
	}
	else if (ie.GetKeyboardEvent() == KeyUp && ie.GetKeyboardKey() == KEY_SPACE && step)
	{
		step = false;
	}
	*/
}


void BLWorld::Draw() const
{
	m_oCanva.DrawRect(0, 0, m_iWidth, m_iHeight, 0, 0, 255);


	for (uint i=0 ; i<m_oGrid.GetWidth() ; ++i)
	{
		for (uint j=0 ; j<m_oGrid.GetHeight() ; ++j)
		{
			if (m_oGrid[i][j].GetType() == 1)
			{
				m_oCanva.DrawFillRect(i*m_iGrid, j*m_iGrid, m_iGrid, m_iGrid, 18, 18, 18);
			}
			
			if (m_oGrid[i][j].GetProp() != NULL)
				m_oGrid[i][j].GetProp()->Draw();
		}
	}

	for (uint i=1 ; i<m_iWidth/m_iGrid ; ++i)
	{
		m_oCanva.DrawLine(i*m_iGrid, 0, i*m_iGrid, m_iHeight, 0, 0, 255);
	}

	for (uint i=1 ; i<m_iHeight/m_iGrid ; ++i)
	{
		m_oCanva.DrawLine(0, i*m_iGrid, m_iWidth, i*m_iGrid, 0, 0, 255);
	}

	//m_pProp->Draw();

	m_pBot->Draw(m_oCanva);
}
