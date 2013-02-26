#include "BLWorld.h"
#include "CanvasBase.h"
#include "Canvas.h"
#include "BLBot.h"
#include "InputEvent.h"
#include "GEngine.h"
#include "World\BLProp.h"
#include "Path.h"
#include "World\BLProp_SI.h"
#include "World\BLDoor.h"
#include "Map\BLMap.h"
#include "Map\BLTiles.h"


BLWorld::BLWorld(BLApp& oBLApp, Canvas& canva, int w, int h, const char* tilesname)
	: m_oBLApp(oBLApp)
	, m_oCanva(canva)
	, m_iGrid(0)
{
	m_pTiles = new BLTiles(*canva.GetGEngine(), tilesname);
	m_iGrid = m_pTiles->GetTilesWidth();
	ASSERT(m_pTiles->GetTilesWidth() == m_pTiles->GetTilesHeight());

	m_pMap = new BLMap(w, h, *m_pTiles);
	m_pMap->Generate();
	int i, j;
	m_pMap->RandomFullGroundLoc(i, j);

	m_pBot = new BLBot(*canva.GetGEngine(), *this);
	m_pBot->SetLoc((float)i*m_iGrid + m_iGrid/2, (float)j*m_iGrid + m_iGrid/2);
	m_pBot->SetPos(i, j);
	m_pBot->SetState(BLBot::Idle);
	CenterMap((int)m_pBot->GetLocX(), (int)m_pBot->GetLocY());

	m_pMap->RandomFullGroundLoc(i, j);
	m_pProp = new BLProp_SI(*this, "Mine", DATA_DIR "/Test/Mine.png", Vector2(i,j));

	//BLDoor* pDoor = new BLDoor(*this, "Door", BLDoor::Verti, Vector2(3, 6));
	//pDoor->Close();

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
		const BLSquare& sq = m_pMap->GetGrid()[oPath[i]];
		if (sq.GetProp() != NULL && sq.IsTempBlock())
			return false;
	}

	return true;
}


void BLWorld::CenterMap(int x, int y)
{
	x -= (m_oCanva.GetWidth() / 2);
	y -= (m_oCanva.GetHeight() / 2);

	x = max(0, x);
	y = max(0, y);
	x = min(x, (int)(GetWidth() * GetGridSize() - m_oCanva.GetWidth()));
	y = min(y, (int)(GetHeight() * GetGridSize() - m_oCanva.GetHeight()));

	m_oCanva.SetOrigX(x);
	m_oCanva.SetOrigY(y);
}



void BLWorld::Update(float dt)
{
	m_pBot->Update(dt);

	float x, y;
	m_pBot->GetLoc(x, y);

	//x = (x + (float)m_pProp->GetPos().x * (float)GetGridSize()) / 2.f;
	//y = (y + (float)m_pProp->GetPos().y * (float)GetGridSize()) / 2.f;

	CenterMap((int)x, (int)y);
}


void BLWorld::Draw() const
{
	m_oCanva.DrawRect(0, 0, m_oCanva.GetWidth()-1, m_oCanva.GetHeight()-1, 0, 0, 255);

	m_pMap->Display(m_oCanva);

	m_pBot->Draw();
}
