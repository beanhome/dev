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

#include "Fact\IBFactVisitor.h"
#include "Action\IBAction.h"
#include "Action\IBActionDef.h"
#include "World\IBPath.h"
#include "BLApp.h"


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

	m_pBot = new BLBot(*canva.GetGEngine(), *this, oBLApp.GetPlannerCanvas());
	m_pBot->SetLoc((float)i*m_iGrid + m_iGrid/2, (float)j*m_iGrid + m_iGrid/2);
	m_pBot->SetPos(i, j);
	m_pBot->SetState(BLBot::Idle);
	CenterMap((int)m_pBot->GetLocX(), (int)m_pBot->GetLocY());

	m_pMap->RandomFullGroundLoc(i, j);
	m_pProp = new BLProp_SI(*this, "Mine", DATA_DIR "/Test/Mine.png", Vector2(i,j));

	//BLDoor* pDoor = new BLDoor(*this, "Door", BLDoor::Verti, Vector2(3, 6));
	//pDoor->Close();

	//m_pBot->AddGoal("IBFactDef_BotAtPos", new IBVector2("Dest", 14, 14));
	//m_pBot->AddGoal("IBFactDef_BotHasObject", m_pProp);
}

BLWorld::~BLWorld()
{
	delete m_pTiles;
	delete m_pMap;
	delete m_pBot;
	delete m_pProp;
}

bool BLWorld::GetMouseCase(const BLSquare** pSquare, int& i, int& j)
{
	//i = m_oCanva.GetMouseX();
	//j = m_oCanva.GetMouseY();
	i = (m_oCanva.GetMouseX()/* + m_oCanva.GetOrigX()*/) / m_iGrid;
	j = (m_oCanva.GetMouseY()/* + m_oCanva.GetOrigY()*/) / m_iGrid;

	if (m_oCanva.GetMouseX() < m_oCanva.GetOrigX() || m_oCanva.GetMouseX()-m_oCanva.GetOrigX() > m_oCanva.GetWidth() || m_oCanva.GetMouseY()-m_oCanva.GetOrigY() > m_oCanva.GetHeight())
		return false;

	if (i<0 || i>= (int)m_pMap->GetWidth() || j<0 || j>= (int)m_pMap->GetHeight())
		return false;
	
	*pSquare = &m_pMap->GetGrid().GetCase(i, j);
	return true;
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
	m_oCanva.SetOrigX(Clamp<int>(x - (m_oCanva.GetWidth() / 2), 0, (GetWidth() * GetGridSize() - m_oCanva.GetWidth())));
	m_oCanva.SetOrigY(Clamp<int>(y - (m_oCanva.GetHeight() / 2), 0, (GetHeight() * GetGridSize() - m_oCanva.GetHeight())));
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
	m_pMap->Display(m_oCanva);

	m_pBot->Draw();

	m_oCanva.GetParent().DrawRect(0, 0, m_oCanva.GetWidth()-1, m_oCanva.GetHeight()-1, 255, 0, 0);

	DrawDebug();
}

void BLWorld::DrawDebug() const
{
	IBFactVisitor FactVisitor(m_pBot->GetPlanner());

	for (const IBFact* fact = FactVisitor.Begin() ; fact != NULL ; fact = FactVisitor.Next())
	{
		//m_oCanva.GetGEngine()->Print("Fact %s", fact->GetFactDef()->GetName().c_str());

		if (fact->GetCauseAction() != NULL && fact->GetCauseAction()->GetDef()->GetName() == "FollowPath")
		{
			IBPath* pPath = static_cast<IBPath*>(fact->GetCauseAction()->FindVariables("Path"));
			if (pPath != NULL)
				DrawDebugPath(*pPath);

			IBVector2* pPos = static_cast<IBVector2*>(fact->GetCauseAction()->FindVariables("Target"));
			if (pPos != NULL)
				DrawDebugPos(*pPos);
		}
	}
}

void BLWorld::DrawDebugPath(const IBPath& oPath) const
{
	if (oPath.GetLength() > 0)
	{
		int x1 = oPath.GetList()[0].x * GetGridSize() + GetGridSize()/2;
		int y1 = oPath.GetList()[0].y * GetGridSize() + GetGridSize()/2;
		//int x2 = m_pBot->GetPos().x * GetGridSize() + GetGridSize()/2;
		//int y2 = m_pBot->GetPos().y * GetGridSize() + GetGridSize()/2;
		//GetCanvas().CanvasBase::DrawLine(x1, y1, x2, y2, Color(0, 255, 0));
		GetCanvas().CanvasBase::DrawRect(x1-5, y1-5, 10, 10, Color(0, 255, 0));
	}

	for (uint i=1 ; i<oPath.GetLength() ; ++i)
	{
		int x1 = oPath.GetList()[i-1].x * GetGridSize() + GetGridSize()/2;
		int y1 = oPath.GetList()[i-1].y * GetGridSize() + GetGridSize()/2;
		int x2 = oPath.GetList()[i].x * GetGridSize() + GetGridSize()/2;
		int y2 = oPath.GetList()[i].y * GetGridSize() + GetGridSize()/2;

		GetCanvas().CanvasBase::DrawLine(x1, y1, x2, y2, Color(0, 255, 0));
	}
}

void BLWorld::DrawDebugPos(const IBVector2& oPos) const
{
	int x1 = oPos.x * GetGridSize();
	int y1 = oPos.y * GetGridSize();
	m_oCanva.DrawRect(x1, y1, GetGridSize()-1, GetGridSize()-1, 255, 0, 0);
	m_oCanva.Print(x1+2, y1+1, m_oCanva.GetPrintFont(), 10, LeftTop, 255, 0, 0, "%s", oPos.GetName().c_str());
}
