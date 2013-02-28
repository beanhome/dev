#include "IBGPlanner.h"

#include "CanvasBase.h"
#include "IBGFactBox.h"
#include "IBGActionBox.h"
#include "Action\IBAction.h"
#include "Fact\IBFactDef.h"
#include "IBGFact.h"
#include "IBGAction.h"

const uint	IBGPlanner::s_iMargin = 12;
const uint	IBGPlanner::s_iFactWidth = 90;
const uint	IBGPlanner::s_iFactTitleHeight = 18;
const uint	IBGPlanner::s_iFactVarHeight = 12;
const uint	IBGPlanner::s_iFactVarSpace = 2;
const uint	IBGPlanner::s_iFactHeight = 20;
const uint	IBGPlanner::s_iFactMinSpace = 16;
const uint	IBGPlanner::s_iLinkWidth = 48;
const uint	IBGPlanner::s_iActionWidth = 128;
const uint	IBGPlanner::s_iActionMinHeight = 64;
const uint	IBGPlanner::s_iActionTitleHeight = 18;
const uint	IBGPlanner::s_iActionAnchorHeight = 20;
const uint	IBGPlanner::s_iActionVarHeight = 12;
const uint	IBGPlanner::s_iActionVarSpace = 4;
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
{
	IBGPlanner::s_iBoxWidth = IBGPlanner::s_iFactWidth + IBGPlanner::s_iLinkWidth + IBGPlanner::s_iActionWidth;
	IBGPlanner::s_iBoxMinHeight = IBGPlanner::s_iActionMinHeight;
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
	
	int h = 0;

	for (FactSet::iterator it = m_aGoals.begin() ; it != m_aGoals.end() ; ++it)
	{
		IBGFact* pFact = static_cast<IBGFact*>(*it);
		pFact->Resize();
		h += pFact->GetH();
	}

	int x = m_oCanvas.GetWidth();
	if (m_aGoals.size() > 0)
		x = max(x, static_cast<IBGFact*>(*m_aGoals.begin())->GetW());
	int w = IBGPlanner::s_iFactWidth+IBGPlanner::s_iMargin;
	x -= (w/2 + IBGPlanner::s_iMargin/2);
	m_oCanvas.CanvasBase::DrawRect(x-w/2, IBGPlanner::s_iMargin, w, (h > m_oCanvas.GetHeight() ? m_oCanvas.GetHeight() : m_oCanvas.GetHeight()-IBGPlanner::s_iMargin*2), Color(255, 255, 0));
	m_oCanvas.CanvasBase::Print(x, IBGPlanner::s_iMargin+10, m_oCanvas.GetPrintFont(), 16, CenterTop, 255, 255, 255, "Goals");

	int s = 0;
	int y = 0;

	if (h < m_oCanvas.GetHeight())
	{
		s = (m_oCanvas.GetHeight() - h) / (m_aGoals.size() + 1);
		y = m_oCanvas.GetPosY() + s;
	}

	y = max(y, m_oCanvas.GetPosY() + (sint16)IBGPlanner::s_iMargin);
	s = max(s, (sint16)IBGPlanner::s_iMargin);

	for (FactSet::iterator it = m_aGoals.begin() ; it != m_aGoals.end() ; ++it)
	{
		IBGFact* pFact = static_cast<IBGFact*>(*it);
		pFact->SetX(std::max<sint16>(IBGPlanner::s_iMargin, m_oCanvas.GetWidth() - (pFact->GetW() + IBGPlanner::s_iMargin)));
		pFact->SetY(y);
		pFact->Draw();
		y += pFact->GetH() + s;
	}
}

