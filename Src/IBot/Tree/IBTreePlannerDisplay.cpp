#include "IBTreePlannerDisplay.h"

#include "CanvasBase.h"
#include "IBPlanner.h"
#include "GEngine.h"
#include "IBTreeNode.h"
#include "EventManager.h"

/*
const uint	IBTreePlannerDisplay::s_iMargin = 12;
const uint	IBTreePlannerDisplay::s_iFactMinWidth = 92;
const uint	IBTreePlannerDisplay::s_iFactTitleHeight = 18;
const uint	IBTreePlannerDisplay::s_iFactTitleSize = 14;
const uint	IBTreePlannerDisplay::s_iFactEvalHeight = 16;
const uint	IBTreePlannerDisplay::s_iFactEvalSize = 12;
const uint	IBTreePlannerDisplay::s_iFactVarHeight = 12;
const uint	IBTreePlannerDisplay::s_iFactVarSpace = 1;
const uint	IBTreePlannerDisplay::s_iFactMinHeight = 20;
const uint	IBTreePlannerDisplay::s_iFactMinSpace = 10;
const uint	IBTreePlannerDisplay::s_iLinkWidth = 48;
const uint	IBTreePlannerDisplay::s_iActionMinWidth = 128;
const uint	IBTreePlannerDisplay::s_iActionMinHeight = 64;
const uint	IBTreePlannerDisplay::s_iActionTitleHeight = 18;
const uint	IBTreePlannerDisplay::s_iActionTitleSize = 14;
const uint	IBTreePlannerDisplay::s_iActionEvalHeight = 16;
const uint	IBTreePlannerDisplay::s_iActionEvalSize = 12;
const uint	IBTreePlannerDisplay::s_iActionVarHeight = 12;
const uint	IBTreePlannerDisplay::s_iActionVarSpace = 2;
const uint  IBTreePlannerDisplay::s_iActionLinkSpace = 16;
const uint  IBTreePlannerDisplay::s_iActionMinSpace = 10;
const Color	IBTreePlannerDisplay::s_oActionColor = Color(64, 192, 255);
const Color	IBTreePlannerDisplay::s_oActionWorkColor = Color(192, 64, 128);
const Color	IBTreePlannerDisplay::s_oMarkToDelActionColor = Color(128, 92, 92);
const Color	IBTreePlannerDisplay::s_oReadyToDelActionColor = Color(92, 92, 92);
const Color	IBTreePlannerDisplay::s_oFactColor = Color(128, 255, 128);
const Color	IBTreePlannerDisplay::s_oFalseFactColor = Color(255, 64, 64);
const Color	IBTreePlannerDisplay::s_oMarkToDelFactColor = Color(128, 92, 92);
const Color	IBTreePlannerDisplay::s_oReadyToDelFactColor = Color(92, 92, 92);
const Color	IBTreePlannerDisplay::s_oLinkColor = Color(128, 255, 255);
const Color	IBTreePlannerDisplay::s_oBoxColor = Color(256, 128, 128);
*/


IBTreePlannerDisplay::IBTreePlannerDisplay(Canvas& oGraphCanva, const class IBPlanner& oPlanner)
	: IBPlannerDisplay(oPlanner)
	, m_oCanvas(oGraphCanva)
	, m_iMaxWidth(0)
	, m_iMaxHeight(0)
	, m_bDraging(false)
	, m_iStartDragX(0)
	, m_iStartDragY(0)
{
	m_pStartNode = new IBTreeNode(m_oCanvas, nullptr, &m_oPlanner.GetGoals());

	m_oCanvas.SetOrigX(-10);
	m_oCanvas.SetOrigY(-10);
}

IBTreePlannerDisplay::~IBTreePlannerDisplay()
{
	delete m_pStartNode;
}

void IBTreePlannerDisplay::RefreshTree()
{
	m_pStartNode->RefreshTree();
}

void IBTreePlannerDisplay::Update(float dt)
{
	sint32 iMouseX = m_oCanvas.GetMouseX();
	sint32 iMouseY = m_oCanvas.GetMouseY();

	m_pStartNode->SetPos(0, 0);
	m_pStartNode->Update(dt, iMouseX, iMouseY);

	if (m_oCanvas.GetGEngine()->GetEventManager()->GetVirtualKey(MOUSE_LEFT) == KeyPressed)
	{
		StartDrag();
	}
	else if (m_oCanvas.GetGEngine()->GetEventManager()->GetVirtualKey(MOUSE_LEFT) == KeyDown
		|| m_oCanvas.GetGEngine()->GetEventManager()->GetVirtualKey(MOUSE_LEFT) == KeyRepeat)
	{
		UpdateDrag();
	}
	else
	{
		StopDrag();
	}

	if (m_oCanvas.GetGEngine()->GetEventManager()->GetVirtualKey(MOUSE_WHEELUP) == KeyPressed)
	{
		m_oCanvas.SetOrigY(m_oCanvas.GetOrigY() - 25.f);
	}
	else if (m_oCanvas.GetGEngine()->GetEventManager()->GetVirtualKey(MOUSE_WHEELDOWN) == KeyPressed)
	{
		m_oCanvas.SetOrigY(m_oCanvas.GetOrigY() + 25.f);
	}
}

void IBTreePlannerDisplay::OnClick()
{
	sint32 iMouseX = m_oCanvas.GetMouseX();
	sint32 iMouseY = m_oCanvas.GetMouseY();

	m_pStartNode->MouseClick(iMouseX, iMouseY);
}


void IBTreePlannerDisplay::DrawGraph()
{
	m_pStartNode->Draw();
}

void IBTreePlannerDisplay::StartDrag()
{
	m_bDraging = true;
	m_iStartDragX = m_oCanvas.GetGEngine()->GetMouseX() + m_oCanvas.GetOrigX();
	m_iStartDragY = m_oCanvas.GetGEngine()->GetMouseY() + m_oCanvas.GetOrigY();
}


void IBTreePlannerDisplay::UpdateDrag()
{
	if (m_bDraging)
	{
		sint32 x = m_iStartDragX - (sint16)m_oCanvas.GetGEngine()->GetMouseX();
		sint32 dx = m_pStartNode->GetWidth() - m_oCanvas.GetWidth();
		x = Clamp<sint32>(x, min<sint32>(dx, 0), max<sint32>(dx, 0));
		m_oCanvas.SetOrigX(x);

		sint32 y = m_iStartDragY - (sint16)m_oCanvas.GetGEngine()->GetMouseY();
		sint32 dy = m_pStartNode->GetHeight() - m_oCanvas.GetHeight();
		y = Clamp<sint32>(y, std::min<sint32>(dy, 0), std::max<sint32>(dy, 0));
		m_oCanvas.SetOrigY(y);
	}
}

void IBTreePlannerDisplay::StopDrag()
{
	m_bDraging = false;
}
