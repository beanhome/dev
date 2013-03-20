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
const uint	IBGPlanner::s_iFactMinWidth = 92;
const uint	IBGPlanner::s_iFactTitleHeight = 18;
const uint	IBGPlanner::s_iFactTitleSize = 14;
const uint	IBGPlanner::s_iFactEvalHeight = 16;
const uint	IBGPlanner::s_iFactEvalSize = 12;
const uint	IBGPlanner::s_iFactVarHeight = 12;
const uint	IBGPlanner::s_iFactVarSpace = 1;
const uint	IBGPlanner::s_iFactMinHeight = 20;
const uint	IBGPlanner::s_iFactMinSpace = 10;
const uint	IBGPlanner::s_iLinkWidth = 48;
const uint	IBGPlanner::s_iActionMinWidth = 128;
const uint	IBGPlanner::s_iActionMinHeight = 64;
const uint	IBGPlanner::s_iActionTitleHeight = 18;
const uint	IBGPlanner::s_iActionTitleSize = 14;
const uint	IBGPlanner::s_iActionEvalHeight = 16;
const uint	IBGPlanner::s_iActionEvalSize = 12;
const uint	IBGPlanner::s_iActionVarHeight = 12;
const uint	IBGPlanner::s_iActionVarSpace = 2;
const uint  IBGPlanner::s_iActionLinkSpace = 16;
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
	
	int width = 0;
	int height = 0;
	m_iMaxHeight = 0;
	m_iMaxWidth = 0;
	int fGoalsWidth = s_iFactMinWidth;

	for (FactSet::iterator it = m_aGoals.begin() ; it != m_aGoals.end() ; ++it)
	{
		IBGFact* pFact = static_cast<IBGFact*>(*it);
		pFact->Resize();
		height += pFact->GetH();
		width = std::max<uint16>(pFact->GetW(), m_iMaxWidth);
		fGoalsWidth = std::max<int>(pFact->GetFactBox()->GetW(), fGoalsWidth);
	}

	width += s_iMargin * 2;
	height += s_iMargin * 2;

	m_iMaxWidth = std::max<uint16>(width, m_oCanvas.GetWidth());
	m_iMaxHeight = std::max<uint16>(height, m_oCanvas.GetHeight());

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
		fGoalsWidth += s_iMargin;
		int x = m_iMaxWidth - ((fGoalsWidth+s_iMargin)/2);
		m_oCanvas.CanvasBase::DrawRect(x-fGoalsWidth/2, s_iMargin/2, fGoalsWidth-1, m_iMaxHeight-s_iMargin-1, Color(255, 255, 0));
		m_oCanvas.CanvasBase::Print(x, s_iMargin+10, m_oCanvas.GetPrintFont(), 16, CenterTop, 255, 255, 255, "Goals");
	}

	{
		int s = 0;
		int y = 0;

		if (height < m_oCanvas.GetHeight())
		{
			s = (m_oCanvas.GetHeight() - height) / (m_aGoals.size() + 1);
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

