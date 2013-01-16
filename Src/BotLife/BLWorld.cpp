#include "BLWorld.h"
#include "CanvasBase.h"
#include "Canvas.h"
#include "BLBot.h"
#include "InputEvent.h"
#include "GEngine.h"
#include "IBPlanner.h" // To Del

int _map_[16][16] = {
	{ 1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1 },
	{ 1, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1 },
	{ 1, 0, 0, 1,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1 },
	{ 1, 0, 0, 1,  1, 1, 0, 0,  1, 1, 1, 1,  0, 0, 0, 1 },

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
	m_pBot->SetLoc(30, 30);
	m_pBot->SetPos(1, 1);

	//m_pBot->SetState(BLBot::Walk, BLBot::Down, 1.f);
	m_pBot->SetState(BLBot::Idle, BLBot::Down, 1.f);
}

BLWorld::~BLWorld()
{
	delete m_pBot;
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

	m_pBot->Draw(m_oCanva);
}
