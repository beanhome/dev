#include "IBGraphPlannerDisplay.h"

#include "CanvasBase.h"
#include "IBPlanner.h"
#include "IBGFactBox.h"
#include "IBGActionBox.h"
#include "IBGPlanBox.h"
#include "IBGNodeBox.h"
#include "IBGFact.h"
#include "IBGAction.h"
#include "GEngine.h"

const uint	IBGraphPlannerDisplay::s_iMargin = 12;
const uint	IBGraphPlannerDisplay::s_iFactMinWidth = 92;
const uint	IBGraphPlannerDisplay::s_iFactTitleHeight = 18;
const uint	IBGraphPlannerDisplay::s_iFactTitleSize = 14;
const uint	IBGraphPlannerDisplay::s_iFactEvalHeight = 16;
const uint	IBGraphPlannerDisplay::s_iFactEvalSize = 12;
const uint	IBGraphPlannerDisplay::s_iFactVarHeight = 12;
const uint	IBGraphPlannerDisplay::s_iFactVarSpace = 1;
const uint	IBGraphPlannerDisplay::s_iFactMinHeight = 20;
const uint	IBGraphPlannerDisplay::s_iFactMinSpace = 10;
const uint	IBGraphPlannerDisplay::s_iLinkWidth = 48;
const uint	IBGraphPlannerDisplay::s_iActionMinWidth = 128;
const uint	IBGraphPlannerDisplay::s_iActionMinHeight = 64;
const uint	IBGraphPlannerDisplay::s_iActionTitleHeight = 18;
const uint	IBGraphPlannerDisplay::s_iActionTitleSize = 14;
const uint	IBGraphPlannerDisplay::s_iActionEvalHeight = 16;
const uint	IBGraphPlannerDisplay::s_iActionEvalSize = 12;
const uint	IBGraphPlannerDisplay::s_iActionVarHeight = 12;
const uint	IBGraphPlannerDisplay::s_iActionVarSpace = 2;
const uint  IBGraphPlannerDisplay::s_iActionLinkSpace = 16;
const uint  IBGraphPlannerDisplay::s_iActionMinSpace = 10;
const Color	IBGraphPlannerDisplay::s_oActionColor = Color(64, 192, 255);
const Color	IBGraphPlannerDisplay::s_oActionWorkColor = Color(192, 64, 128);
const Color	IBGraphPlannerDisplay::s_oMarkToDelActionColor = Color(128, 92, 92);
const Color	IBGraphPlannerDisplay::s_oReadyToDelActionColor = Color(92, 92, 92);
const Color	IBGraphPlannerDisplay::s_oFactColor = Color(128, 255, 128);
const Color	IBGraphPlannerDisplay::s_oFalseFactColor = Color(255, 64, 64);
const Color	IBGraphPlannerDisplay::s_oMarkToDelFactColor = Color(128, 92, 92);
const Color	IBGraphPlannerDisplay::s_oReadyToDelFactColor = Color(92, 92, 92);
const Color	IBGraphPlannerDisplay::s_oLinkColor = Color(128, 255, 255);
const Color	IBGraphPlannerDisplay::s_oBoxColor = Color(256, 128, 128);



IBGraphPlannerDisplay::IBGraphPlannerDisplay(CanvasBase& oGraphCanva, const class IBPlanner& oPlanner)
	: IBPlannerDisplay(oPlanner)
	, m_oCanvas(oGraphCanva)
	, m_iMaxWidth(0)
	, m_iMaxHeight(0)
	, m_bDraging(false)
	, m_iStartDragX(0)
	, m_iStartDragY(0)
	, m_bSnaping(false)
	, m_iSnapX(0)
	, m_iSnapY(0)
	, m_fFloatOrigX(0.f)
	, m_fFloatOrigY(0.f)
{
	m_pPlan = new IBGPlanBox(m_oCanvas, &m_oPlanner.GetGoals());

	m_oCanvas.SetOrigX(-10);
	m_oCanvas.SetOrigY(-10);
}

IBGraphPlannerDisplay::~IBGraphPlannerDisplay()
{
	delete m_pPlan;
}

void IBGraphPlannerDisplay::DrawGraph()
{
	m_pPlan->Init();

	m_pPlan->Resize();

	m_pPlan->SetX(0);
	m_pPlan->SetY(0);

	m_oCanvas.DrawRect(m_pPlan->GetX(), m_pPlan->GetY(), m_pPlan->GetW(), m_pPlan->GetH(), 246, 229, 153);

	m_pPlan->Draw();
}

void IBGraphPlannerDisplay::StartDrag()
{
	m_bDraging = true;
	m_iStartDragX = m_oCanvas.GetGEngine()->GetMouseX() + m_oCanvas.GetOrigX();
	m_iStartDragY = m_oCanvas.GetGEngine()->GetMouseY() + m_oCanvas.GetOrigY();
}


void IBGraphPlannerDisplay::UpdateDrag()
{
	if (m_bDraging)
	{
		sint32 x = m_iStartDragX - (sint16)m_oCanvas.GetGEngine()->GetMouseX();
		sint32 dx = m_pPlan->GetW() - m_oCanvas.GetWidth();
		x = Clamp<sint32>(x, min<sint32>(dx, 0), max<sint32>(dx, 0));
		m_oCanvas.SetOrigX(x);

		sint32 y = m_iStartDragY - (sint16)m_oCanvas.GetGEngine()->GetMouseY();
		sint32 dy = m_pPlan->GetH() - m_oCanvas.GetHeight();
		y = Clamp<sint32>(y, std::min<sint32>(dy, 0), std::max<sint32>(dy, 0));
		m_oCanvas.SetOrigY(y);
	}
}

void IBGraphPlannerDisplay::StopDrag()
{
	m_bDraging = false;
}



void	 IBGraphPlannerDisplay::StartSnap(int iSnapX, int iSnapY)
{
	m_bSnaping = true;

	m_iSnapX = iSnapX + m_oCanvas.GetOrigX();
	m_iSnapY = iSnapY + m_oCanvas.GetOrigY();

	m_fFloatOrigX = (float)m_oCanvas.GetOrigX();
	m_fFloatOrigY = (float)m_oCanvas.GetOrigY();
}

void	 IBGraphPlannerDisplay::UpdateSnap(float dt)
{
	sint32 iOrigTargetX = -m_oCanvas.GetWidth() / 2 + m_iSnapX;
	sint32 iOrigTargetY = -m_oCanvas.GetHeight() / 2 + m_iSnapY;

	ClampOrig(iOrigTargetX, iOrigTargetY);

	int iDeltaX = iOrigTargetX - m_oCanvas.GetOrigX();
	int iDeltaY = iOrigTargetY - m_oCanvas.GetOrigY();

	float Speed = 1000.f;

	float fMoveX = (float)iDeltaX;
	float fMoveY = (float)iDeltaY;
	float fSize = sqrt(fMoveX*fMoveX + fMoveY*fMoveY);
	if (fSize <= dt * Speed)
	{
		StopSnap();
		m_oCanvas.SetOrigX(iOrigTargetX);
		m_oCanvas.SetOrigY(iOrigTargetY);
	}
	else
	{
		fMoveX /= fSize;
		fMoveY /= fSize;


		m_fFloatOrigX += dt * Speed * fMoveX;
		m_fFloatOrigY += dt * Speed * fMoveY;

		m_oCanvas.SetOrigX((sint32)m_fFloatOrigX);
		m_oCanvas.SetOrigY((sint32)m_fFloatOrigY);
	}
}

void	 IBGraphPlannerDisplay::StopSnap()
{
	m_bSnaping = false;
}

void IBGraphPlannerDisplay::RePanPlan(IBPlanner* pPlanner)
{
	sint32 x = m_oCanvas.GetOrigX();
	sint32 y = m_oCanvas.GetOrigY();

	ClampOrig(x, y);

	m_oCanvas.SetOrigX(x);
	m_oCanvas.SetOrigY(y);
}

void	 IBGraphPlannerDisplay::ClampOrig(sint32& x, sint32& y)
{
	sint32 dx = m_pPlan->GetW() - m_oCanvas.GetWidth();
	sint32 dy = m_pPlan->GetH() - m_oCanvas.GetHeight();

	x = Clamp<sint32>(x, std::min<sint32>(dx, 0), std::max<sint32>(dx, 0));
	y = Clamp<sint32>(y, std::min<sint32>(dy, 0), std::max<sint32>(dy, 0));
}