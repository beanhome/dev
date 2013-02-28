#include "IBGFactBox.h"

#include "CanvasBase.h"
#include "Fact\IBFact.h"
#include "IBGPlanner.h"
#include "World\IBObject.h"

IBGFactBox::IBGFactBox(Canvas& parent, IBFact* pFact)
	: IBGBoxBase(parent)
	, m_pFact(pFact)
{
}

void IBGFactBox::Resize()
{
	SetH(IBGPlanner::s_iFactTitleHeight + max(IBGPlanner::s_iFactHeight, m_pFact->GetVariables().size()*(IBGPlanner::s_iFactVarHeight+IBGPlanner::s_iFactVarSpace)));
	SetW(IBGPlanner::s_iFactWidth);
}


void IBGFactBox::Draw() const
{
	Color oColor = (m_pFact->IsTrue() ? IBGPlanner::s_oFactColor : IBGPlanner::s_oFalseFactColor);

	if (m_pFact->IsMarkToDelete())
		oColor = IBGPlanner::s_oMarkToDelFactColor;
	else if (m_pFact->IsReadyToDelete())
		oColor = IBGPlanner::s_oReadyToDelFactColor;

	DrawFrame(oColor);

	sint16 x = 0;
	sint16 y = 0;
	uint16 w = GetW();
	uint16 h = GetH();

	m_oCanvas.CanvasBase::DrawLine(x, y+IBGPlanner::s_iFactTitleHeight, x+w-1, y+IBGPlanner::s_iFactTitleHeight, oColor);
	m_oCanvas.CanvasBase::Print(x+w/2, y+IBGPlanner::s_iFactTitleHeight/2, m_oCanvas.GetPrintFont(), IBGPlanner::s_iFactTitleHeight-4, Center, IBGPlanner::s_oFactColor, "%s", m_pFact->GetFactDef()->GetName().c_str());

	for (uint i=0 ; i<m_pFact->GetVariables().size() ; ++i)
	{
		IBObject* pObject = m_pFact->GetVariable(i);
		m_oCanvas.CanvasBase::Print(x+w/2, y+IBGPlanner::s_iFactTitleHeight + (IBGPlanner::s_iFactVarHeight+IBGPlanner::s_iFactVarSpace)/2 + i*(IBGPlanner::s_iFactVarHeight+IBGPlanner::s_iFactVarSpace), m_oCanvas.GetPrintFont(), IBGPlanner::s_iFactVarHeight, Center, IBGPlanner::s_oFactColor, "%s %s", (pObject != NULL ? pObject->GetName().c_str() : "NULL"), (pObject != NULL ? pObject->GetData().c_str() : ""));
	}
}
