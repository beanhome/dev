#include "IBLogPlannerDisplay.h"

#include "CanvasBase.h"
#include "IBPlanner.h"
#include "GEngine.h"

/*
const uint	IBLogPlannerDisplay::s_iMargin = 12;
const uint	IBLogPlannerDisplay::s_iFactMinWidth = 92;
const uint	IBLogPlannerDisplay::s_iFactTitleHeight = 18;
const uint	IBLogPlannerDisplay::s_iFactTitleSize = 14;
const uint	IBLogPlannerDisplay::s_iFactEvalHeight = 16;
const uint	IBLogPlannerDisplay::s_iFactEvalSize = 12;
const uint	IBLogPlannerDisplay::s_iFactVarHeight = 12;
const uint	IBLogPlannerDisplay::s_iFactVarSpace = 1;
const uint	IBLogPlannerDisplay::s_iFactMinHeight = 20;
const uint	IBLogPlannerDisplay::s_iFactMinSpace = 10;
const uint	IBLogPlannerDisplay::s_iLinkWidth = 48;
const uint	IBLogPlannerDisplay::s_iActionMinWidth = 128;
const uint	IBLogPlannerDisplay::s_iActionMinHeight = 64;
const uint	IBLogPlannerDisplay::s_iActionTitleHeight = 18;
const uint	IBLogPlannerDisplay::s_iActionTitleSize = 14;
const uint	IBLogPlannerDisplay::s_iActionEvalHeight = 16;
const uint	IBLogPlannerDisplay::s_iActionEvalSize = 12;
const uint	IBLogPlannerDisplay::s_iActionVarHeight = 12;
const uint	IBLogPlannerDisplay::s_iActionVarSpace = 2;
const uint  IBLogPlannerDisplay::s_iActionLinkSpace = 16;
const uint  IBLogPlannerDisplay::s_iActionMinSpace = 10;
const Color	IBLogPlannerDisplay::s_oActionColor = Color(64, 192, 255);
const Color	IBLogPlannerDisplay::s_oActionWorkColor = Color(192, 64, 128);
const Color	IBLogPlannerDisplay::s_oMarkToDelActionColor = Color(128, 92, 92);
const Color	IBLogPlannerDisplay::s_oReadyToDelActionColor = Color(92, 92, 92);
const Color	IBLogPlannerDisplay::s_oFactColor = Color(128, 255, 128);
const Color	IBLogPlannerDisplay::s_oFalseFactColor = Color(255, 64, 64);
const Color	IBLogPlannerDisplay::s_oMarkToDelFactColor = Color(128, 92, 92);
const Color	IBLogPlannerDisplay::s_oReadyToDelFactColor = Color(92, 92, 92);
const Color	IBLogPlannerDisplay::s_oLinkColor = Color(128, 255, 255);
const Color	IBLogPlannerDisplay::s_oBoxColor = Color(256, 128, 128);
*/


IBLogPlannerDisplay::IBLogPlannerDisplay(CanvasBase& oGraphCanva, const class IBPlanner& oPlanner)
	: IBPlannerDisplay(oPlanner)
	, m_oCanvas(oGraphCanva)
	, m_iMaxWidth(0)
	, m_iMaxHeight(0)
	, m_bDraging(false)
	, m_iStartDragX(0)
	, m_iStartDragY(0)
{
	//m_pPlan = new IBGPlanBox(m_oCanvas, &m_oPlanner.GetGoals());

	m_oCanvas.SetOrigX(-10);
	m_oCanvas.SetOrigY(-10);
}

IBLogPlannerDisplay::~IBLogPlannerDisplay()
{
	//delete m_pPlan;
}

void IBLogPlannerDisplay::DrawGraph()
{
	/*
	m_pPlan->Init();

	m_pPlan->Resize();

	m_pPlan->SetX(0);
	m_pPlan->SetY(0);

	m_oCanvas.DrawRect(m_pPlan->GetX(), m_pPlan->GetY(), m_pPlan->GetW(), m_pPlan->GetH(), 246, 229, 153);

	m_pPlan->Draw();
	*/
}

void IBLogPlannerDisplay::StartDrag()
{
	m_bDraging = true;
	m_iStartDragX = m_oCanvas.GetGEngine()->GetMouseX() + m_oCanvas.GetOrigX();
	m_iStartDragY = m_oCanvas.GetGEngine()->GetMouseY() + m_oCanvas.GetOrigY();
}


void IBLogPlannerDisplay::UpdateDrag()
{
	if (m_bDraging)
	{
		/*
		sint32 x = m_iStartDragX - (sint16)m_oCanvas.GetGEngine()->GetMouseX();
		sint32 dx = m_pPlan->GetW() - m_oCanvas.GetWidth();
		x = Clamp<sint32>(x, min<sint32>(dx, 0), max<sint32>(dx, 0));
		m_oCanvas.SetOrigX(x);

		sint32 y = m_iStartDragY - (sint16)m_oCanvas.GetGEngine()->GetMouseY();
		sint32 dy = m_pPlan->GetH() - m_oCanvas.GetHeight();
		y = Clamp<sint32>(y, std::min<sint32>(dy, 0), std::max<sint32>(dy, 0));
		m_oCanvas.SetOrigY(y);
		*/
	}
}

void IBLogPlannerDisplay::StopDrag()
{
	m_bDraging = false;
}