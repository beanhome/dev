#include "IBGActionBox.h"
#include "CanvasBase.h"
#include "Action/IBAction.h"
#include "Action/IBActionDef.h"
#include "IBGPlanner.h"
#include "World/IBObject.h"

IBGActionBox::IBGActionBox(Canvas& parent, IBAction* pAction)
	: IBGBoxBase(parent)
	, m_pAction(pAction)
{
}

void IBGActionBox::Resize()
{
	int lh = IBGPlanner::s_iActionLinkSpace * m_pAction->GetPreCond().size();
	int lv = (IBGPlanner::s_iActionVarHeight + IBGPlanner::s_iActionVarSpace) * m_pAction->GetVariables().size();

	SetH(IBGPlanner::s_iActionTitleHeight + max(lh, lv));
	SetW(IBGPlanner::s_iActionWidth);
}


void IBGActionBox::Draw() const
{
	Color oLineColor = (m_pAction->GetState() == IBAction::IBA_Execute && (m_pAction->GetExecCounter() / 4) % 2 == 0 ? IBGPlanner::s_oActionWorkColor : IBGPlanner::s_oActionColor);

	IBGBoxBase::DrawFrame(oLineColor);

	sint16 x = 0;
	sint16 y = 0;
	uint16 w = GetW();
	uint16 h = GetH();

	m_oCanvas.CanvasBase::DrawLine(x, y+IBGPlanner::s_iActionTitleHeight, x+w-1, y+IBGPlanner::s_iActionTitleHeight, oLineColor);
	m_oCanvas.CanvasBase::Print(x+w/2, y+IBGPlanner::s_iActionTitleHeight/2, m_oCanvas.GetPrintFont(), IBGPlanner::s_iActionTitleHeight-4, Center, IBGPlanner::s_oActionColor, "%s", m_pAction->GetDef()->GetName().c_str());

	if (m_pAction->GetState() == IBAction::IBA_Execute)
		m_oCanvas.CanvasBase::Print(w, 0, m_oCanvas.GetPrintFont(), 10, RightBottom, IBGPlanner::s_oActionColor, "%d", m_pAction->GetExecCounter());


	int k=0;
	for (IBAction::VarMap::const_iterator it = m_pAction->GetVariables().begin() ; it != m_pAction->GetVariables().end() ; ++it, ++k)
	{
		const string& sName = it->first;

		const IBObject* pObject = ((const IBObject*)it->second);
		m_oCanvas.CanvasBase::Print(x+w/2,
			y+IBGPlanner::s_iActionTitleHeight+(IBGPlanner::s_iActionVarHeight+IBGPlanner::s_iActionVarSpace)/2 + (IBGPlanner::s_iActionVarHeight+IBGPlanner::s_iActionVarSpace)*(k),
			m_oCanvas.GetPrintFont(), IBGPlanner::s_iActionVarHeight, RightCenter, IBGPlanner::s_oActionColor, "%s:", sName.c_str());

		m_oCanvas.CanvasBase::Print(x+w/2,
			y+IBGPlanner::s_iActionTitleHeight+(IBGPlanner::s_iActionVarHeight+IBGPlanner::s_iActionVarSpace)/2 + (IBGPlanner::s_iActionVarHeight+IBGPlanner::s_iActionVarSpace)*(k),
			m_oCanvas.GetPrintFont(), IBGPlanner::s_iActionVarHeight, LeftCenter, IBGPlanner::s_oActionColor, " %s", (pObject != NULL ? pObject->GetName().c_str() : "NULL"));
	}
}

