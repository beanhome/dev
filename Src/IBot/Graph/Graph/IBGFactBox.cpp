#include "IBGFactBox.h"

#include "CanvasBase.h"
#include "Fact\IBFact.h"
#include "IBPlannerGraph.h"
#include "World\IBObject.h"

IBGFactBox::IBGFactBox(Canvas& parent, IBFact* pFact)
	: IBGBoxBase(parent)
	, m_pFact(pFact)
{
}

void IBGFactBox::Resize()
{
	SetH(IBPlannerGraph::s_iFactTitleHeight + max(IBPlannerGraph::s_iFactHeight, m_pFact->GetVariables().size()*IBPlannerGraph::s_iFactVarHeight));
	SetW(IBPlannerGraph::s_iFactWidth);
}


void IBGFactBox::Draw() const
{
	Color oColor = (m_pFact->IsTrue() ? IBPlannerGraph::s_oFactColor : IBPlannerGraph::s_oFalseFactColor);

	DrawFrame(oColor);

	sint16 x = 0;
	sint16 y = 0;
	uint16 w = GetW();
	uint16 h = GetH();

	m_oCanvas.CanvasBase::DrawLine(x, y+IBPlannerGraph::s_iFactTitleHeight, x+w-1, y+IBPlannerGraph::s_iFactTitleHeight, oColor);
	m_oCanvas.CanvasBase::Print(x+w/2, y+IBPlannerGraph::s_iFactTitleHeight/2, m_oCanvas.GetPrintFont(), IBPlannerGraph::s_iFactTitleHeight-6, Center, IBPlannerGraph::s_oFactColor, "%s", m_pFact->GetFactDef()->GetName().c_str());

	for (uint i=0 ; i<m_pFact->GetVariables().size() ; ++i)
	{
		IBObject* pObject = m_pFact->GetVariable(i);
		m_oCanvas.CanvasBase::Print(x+w/2, y+IBPlannerGraph::s_iFactTitleHeight + IBPlannerGraph::s_iFactVarHeight/2 + i*IBPlannerGraph::s_iFactVarHeight, m_oCanvas.GetPrintFont(), IBPlannerGraph::s_iFactTitleHeight-6, Center, IBPlannerGraph::s_oFactColor, "%s", (pObject != NULL ? pObject->GetName().c_str() : "NULL"));
	}
}
