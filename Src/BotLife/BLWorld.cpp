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
#include "Graph\IBGFact.h"
#include "Graph\IBGAction.h"
#include "Graph\IBGFactBox.h"
#include "Graph\IBGActionBox.h"
#include "World\BLLightProp.h"
#include "World\BLHeavyProp.h"


BLWorld::BLWorld(BLApp& oBLApp, Canvas& canva, int w, int h, const char* tilesname)
	: m_oBLApp(oBLApp)
	, m_oCanva(canva)
	, m_iGrid(0)
	, m_iStartDragX(0)
	, m_iStartDragY(0)
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
	new BLLightProp(*this, "Mine 1", DATA_DIR "/BotLife/Mine.png", Vector2(i,j));
	m_pMap->RandomFullGroundLoc(i, j);
	new BLLightProp(*this, "Mine 2", DATA_DIR "/BotLife/Mine.png", Vector2(i,j));
	m_pMap->RandomFullGroundLoc(i, j);
	new BLHeavyProp(*this, "Box", DATA_DIR "/BotLife/Box.png", Vector2(i,j));

	//BLDoor* pDoor = new BLDoor(*this, "Door", BLDoor::Verti, Vector2(3, 6));
	//pDoor->Close();

	//m_pBot->AddGoal("IBFactDef_BotAtPos", new IBVector2("Dest", 14, 14));
	//m_pBot->AddGoal("IBFactDef_BotHasObject", m_pProp);
}

BLWorld::~BLWorld()
{
	delete m_pBot;
	delete m_pMap;
	delete m_pTiles;
}

const BLSquare* BLWorld::GetMouseCase()
{
	int i = (m_oCanva.GetMouseX()/* + m_oCanva.GetOrigX()*/) / m_iGrid;
	int j = (m_oCanva.GetMouseY()/* + m_oCanva.GetOrigY()*/) / m_iGrid;

	if (m_oCanva.GetMouseX() < m_oCanva.GetOrigX() || m_oCanva.GetMouseX()-m_oCanva.GetOrigX() > m_oCanva.GetWidth() || m_oCanva.GetMouseY()-m_oCanva.GetOrigY() > m_oCanva.GetHeight())
		return NULL;

	if (i<0 || i>= (int)m_pMap->GetWidth() || j<0 || j>= (int)m_pMap->GetHeight())
		return NULL;
	
	return &m_pMap->GetGrid().GetCase(i, j);
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

void BLWorld::StartDrag()
{
	m_iStartDragX = m_oCanva.GetGEngine()->GetMouseX() + m_oCanva.GetOrigX();
	m_iStartDragY = m_oCanva.GetGEngine()->GetMouseY() + m_oCanva.GetOrigY();
}

void BLWorld::UpdateDrag()
{
	sint16 x = Clamp<sint16>(m_iStartDragX - (sint16)m_oCanva.GetGEngine()->GetMouseX(), 0, std::max<sint16>(m_pMap->GetWidth() * m_pTiles->GetTilesWidth() - m_oCanva.GetWidth(), 0));
	sint16 y = Clamp<sint16>(m_iStartDragY - (sint16)m_oCanva.GetGEngine()->GetMouseY(), 0, std::max<sint16>(m_pMap->GetHeight() * m_pTiles->GetTilesHeight() - m_oCanva.GetHeight(), 0));
	m_oCanva.SetOrigX(x);
	m_oCanva.SetOrigY(y);
}

void BLWorld::StopDrag()
{

}




void BLWorld::Update(float dt)
{
	m_pBot->Update(dt);

	//float x, y;
	//m_pBot->GetLoc(x, y);
	//CenterMap((int)x, (int)y);
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
		const IBGFact* pFact = static_cast<const IBGFact*>(fact);

		if (pFact->GetFactBox()->GetCanvas().IsMouseInside())
		{
			for (uint i=0 ; i<pFact->GetVariables().size() ; ++i)
			{
				IBObject* pObj = pFact->GetVariable(i);
				DrawDebugObject(pObj);
			}
		}
		else if (pFact->GetCauseAction() != NULL)
		{
			IBGAction* pAction = static_cast<IBGAction*>(pFact->GetCauseAction());
			if (pAction->GetActionBox()->GetCanvas().IsMouseInside())
			{
				for (IBAction::VarMap::const_iterator it = pAction->GetVariables().begin() ; it != pAction->GetVariables().end() ; ++it)
				{
					IBObject* pObj = it->second;
					DrawDebugObject(pObj);
				}
			}
		}
	}
}

void BLWorld::DrawDebugObject(IBObject* pObj) const
{
	IBPath* pPath = dynamic_cast<IBPath*>(pObj);
	if (pPath != NULL)
		DrawDebugPath(*pPath);

	IBVector2* pPos = dynamic_cast<IBVector2*>(pObj);
	if (pPos != NULL)
		DrawDebugPos(*pPos);
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
