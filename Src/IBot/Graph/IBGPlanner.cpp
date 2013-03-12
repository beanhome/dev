#include "IBGPlanner.h"

#include "CanvasBase.h"
#include "IBGFactBox.h"
#include "IBGActionBox.h"
#include "Action\IBAction.h"
#include "Fact\IBFactDef.h"
#include "IBGFact.h"
#include "IBGAction.h"
#include "GEngine.h"

const uint	IBGPlanner::s_iMargin = 12;
const uint	IBGPlanner::s_iFactWidth = 92;
const uint	IBGPlanner::s_iFactTitleHeight = 18;
const uint	IBGPlanner::s_iFactVarHeight = 12;
const uint	IBGPlanner::s_iFactVarSpace = 1;
const uint	IBGPlanner::s_iFactHeight = 20;
const uint	IBGPlanner::s_iFactMinSpace = 10;
const uint	IBGPlanner::s_iLinkWidth = 48;
const uint	IBGPlanner::s_iActionWidth = 128;
const uint	IBGPlanner::s_iActionMinHeight = 64;
const uint	IBGPlanner::s_iActionTitleHeight = 18;
const uint	IBGPlanner::s_iActionAnchorHeight = 20;
const uint	IBGPlanner::s_iActionVarHeight = 12;
const uint	IBGPlanner::s_iActionVarSpace = 2;
const uint  IBGPlanner::s_iActionLinkSpace = 16;
      uint	IBGPlanner::s_iBoxWidth = 0;
      uint	IBGPlanner::s_iBoxMinHeight = 0;
const uint	IBGPlanner::s_iBoxSpace = 32;
const Color	IBGPlanner::s_oActionColor = Color(64, 192, 255);
const Color	IBGPlanner::s_oActionWorkColor = Color(192, 64, 128);
const Color	IBGPlanner::s_oMarkToDelActionColor = Color(128, 92, 92);
const Color	IBGPlanner::s_oReadyToDelActionColor = Color(92, 92, 92);
const Color	IBGPlanner::s_oFactColor = Color(128, 255, 128);
const Color	IBGPlanner::s_oFalseFactColor = Color(255, 64, 64);
const Color	IBGPlanner::s_oMarkToDelFactColor = Color(128, 92, 92);
const Color	IBGPlanner::s_oReadyToDelFactColor = Color(92, 92, 92);
const Color	IBGPlanner::s_oLinkColor = Color(128, 255, 255);
const Color	IBGPlanner::s_oBoxColor = Color(256, 128, 128);



IBGPlanner::IBGPlanner(void* pOwner, CanvasBase& oGraphCanva)
	: IBPlanner(pOwner)
	, m_oCanvas(oGraphCanva)
	, m_iMaxWidth(0)
	, m_iMaxHeight(0)
	, m_bDraging(false)
	, m_iStartDragX(0)
	, m_iStartDragY(0)
{
	s_iBoxWidth = s_iFactWidth + s_iLinkWidth + s_iActionWidth;
	s_iBoxMinHeight = s_iActionMinHeight;
}

IBGPlanner::~IBGPlanner()
{
}


IBAction* IBGPlanner::InstanciateAction(IBActionDef* pDef, IBFact* pPostCond1)
{
	return new IBGAction(pDef, pPostCond1);
}

IBFact* IBGPlanner::InstanciateFact(IBFactDef* pDef, const vector<IBObject*>& aUserData, IBAction* pEffectAction)
{
	return new IBGFact(pDef, aUserData, (pEffectAction != NULL ? static_cast<IBGAction*>(pEffectAction)->GetCanvas() : m_oCanvas));
}

void IBGPlanner::Draw()
{
	m_oCanvas.GetParent().CanvasBase::DrawRect(0, 0, m_oCanvas.GetWidth()-1, m_oCanvas.GetHeight()-1, Color(0, 255, 0));
	
	m_iMaxHeight = 0;
	m_iMaxWidth = 0;
	int w = s_iFactWidth;

	for (FactSet::iterator it = m_aGoals.begin() ; it != m_aGoals.end() ; ++it)
	{
		IBGFact* pFact = static_cast<IBGFact*>(*it);
		pFact->Resize();
		m_iMaxHeight += pFact->GetH();
		m_iMaxWidth = std::max<uint16>(pFact->GetW(), m_iMaxWidth);
		w = std::max<int>(pFact->GetFactBox()->GetW(), w);
	}

	m_iMaxWidth = std::max<uint16>(m_iMaxWidth + s_iMargin * 2, m_oCanvas.GetWidth());
	m_iMaxHeight = std::max<uint16>(m_iMaxHeight + s_iMargin * 2, m_oCanvas.GetHeight());

	if (m_iMaxWidth <= m_oCanvas.GetWidth())
		m_oCanvas.SetOrigX(0);

	if (m_iMaxHeight <= m_oCanvas.GetHeight())
		m_oCanvas.SetOrigY(0);

	for (FactSet::iterator it = m_aGoals.begin() ; it != m_aGoals.end() ; ++it)
	{
		IBGFact* pFact = static_cast<IBGFact*>(*it);
		pFact->SetW(m_iMaxWidth - s_iMargin*2);
	}

	/*
	if (!IsDraging() && m_pCurrentAction != NULL)
	{
		const IBGAction* pAction = static_cast<const IBGAction*>(m_pCurrentAction);
		int x = pAction->GetActionBox()->GetScreenX() + pAction->GetActionBox()->GetW()/2 - m_oCanvas.GetScreenPosX();
		int y = pAction->GetActionBox()->GetScreenY() + pAction->GetActionBox()->GetH()/2 - m_oCanvas.GetScreenPosY();
		m_oCanvas.SetOrigX(Clamp<int>(x - (m_oCanvas.GetWidth() / 2), 0, max(0, m_iMaxWidth-m_oCanvas.GetWidth())));
		m_oCanvas.SetOrigY(Clamp<int>(y - (m_oCanvas.GetHeight() / 2), 0, max(0, m_iMaxHeight-m_oCanvas.GetHeight())));
	}
	*/

	{
		w += s_iMargin;
		int x = m_iMaxWidth - ((w+s_iMargin)/2);
		m_oCanvas.CanvasBase::DrawRect(x-w/2, s_iMargin/2, w-1, m_iMaxHeight-s_iMargin-1, Color(255, 255, 0));
		m_oCanvas.CanvasBase::Print(x, s_iMargin+10, m_oCanvas.GetPrintFont(), 16, CenterTop, 255, 255, 255, "Goals");
	}

	{
		int s = 0;
		int y = 0;

		if (m_iMaxHeight < m_oCanvas.GetHeight())
		{
			s = (m_oCanvas.GetHeight() - m_iMaxHeight) / (m_aGoals.size() + 1);
			y = m_oCanvas.GetPosY() + s;
		}

		y = std::max<int>(y, m_oCanvas.GetPosY() + (sint16)s_iMargin);
		s = std::max<int>(s, (int)s_iMargin);

		for (FactSet::iterator it = m_aGoals.begin() ; it != m_aGoals.end() ; ++it)
		{
			IBGFact* pFact = static_cast<IBGFact*>(*it);
			//pFact->SetX(std::max<sint16>(s_iMargin, m_oCanvas.GetWidth() - (pFact->GetW() + s_iMargin)));
			pFact->SetX(s_iMargin);
			pFact->SetY(y);
			pFact->Draw();
			y += pFact->GetH() + s;
		}
	}
}

void IBGPlanner::StartDrag()
{
	m_bDraging = true;
	m_iStartDragX = m_oCanvas.GetGEngine()->GetMouseX() + m_oCanvas.GetOrigX();
	m_iStartDragY = m_oCanvas.GetGEngine()->GetMouseY() + m_oCanvas.GetOrigY();
}

void IBGPlanner::UpdateDrag()
{
	sint16 x = Clamp<sint16>(m_iStartDragX - (sint16)m_oCanvas.GetGEngine()->GetMouseX(), 0, std::max<sint16>(m_iMaxWidth - m_oCanvas.GetWidth(), 0));
	sint16 y = Clamp<sint16>(m_iStartDragY - (sint16)m_oCanvas.GetGEngine()->GetMouseY(), 0, std::max<sint16>(m_iMaxHeight - m_oCanvas.GetHeight(), 0));
	m_oCanvas.SetOrigX(x);
	m_oCanvas.SetOrigY(y);
}

void IBGPlanner::StopDrag()
{
	m_bDraging = false;
}

