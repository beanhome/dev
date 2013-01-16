#include "IBGActionBox.h"
#include "CanvasBase.h"
#include "Action/IBAction.h"
#include "Action/IBActionDef.h"
#include "IBPlannerGraph.h"
#include "World/IBObject.h"

IBGActionBox::IBGActionBox(Canvas& parent, IBAction* pAction)
	: IBGBoxBase(parent)
	, m_pAction(pAction)
{
}

void IBGActionBox::Resize()
{
	int lh = IBPlannerGraph::s_iActionLinkSpace * m_pAction->GetPreCond().size();
	int lv = IBPlannerGraph::s_iActionVarHeight * m_pAction->GetVariables().size();

	SetH(IBPlannerGraph::s_iActionTitleHeight + max(lh, lv));
	SetW(IBPlannerGraph::s_iActionWidth);
}


void IBGActionBox::Draw() const
{
	Color oLineColor = (m_pAction->GetState() == IBAction::IBA_Execute && (m_pAction->GetExecCounter() / 4) % 2 == 0 ? IBPlannerGraph::s_oActionWorkColor : IBPlannerGraph::s_oActionColor);

	IBGBoxBase::DrawFrame(oLineColor);

	sint16 x = 0;
	sint16 y = 0;
	uint16 w = GetW();
	uint16 h = GetH();

	m_oCanvas.CanvasBase::DrawLine(x, y+IBPlannerGraph::s_iActionTitleHeight, x+w-1, y+IBPlannerGraph::s_iActionTitleHeight, oLineColor);
	m_oCanvas.CanvasBase::Print(x+w/2, y+IBPlannerGraph::s_iActionTitleHeight/2, m_oCanvas.GetPrintFont(), IBPlannerGraph::s_iActionTitleHeight-6, Center, IBPlannerGraph::s_oActionColor, "%s", m_pAction->GetDef()->GetName().c_str());

	if (m_pAction->GetState() == IBAction::IBA_Execute)
		m_oCanvas.CanvasBase::Print(w, 0, m_oCanvas.GetPrintFont(), 10, RightBottom, IBPlannerGraph::s_oActionColor, "%d", m_pAction->GetExecCounter());


	int k=0;
	for (IBAction::VarMap::const_iterator it = m_pAction->GetVariables().begin() ; it != m_pAction->GetVariables().end() ; ++it, ++k)
	{
		const string& sName = it->first;

		const IBObject* pObject = ((const IBObject*)it->second);
		m_oCanvas.CanvasBase::Print(x+w/2, y+IBPlannerGraph::s_iActionTitleHeight+IBPlannerGraph::s_iActionVarHeight/2 + IBPlannerGraph::s_iActionVarHeight*(k), m_oCanvas.GetPrintFont(), IBPlannerGraph::s_iActionVarHeight-6, Center, IBPlannerGraph::s_oActionColor, "%s %s", sName.c_str(), (pObject != NULL ? pObject->GetName().c_str() : "NULL"));
	}
}

