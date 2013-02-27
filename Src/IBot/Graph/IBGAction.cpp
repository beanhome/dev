#include "IBGAction.h"
#include "IBGActionBox.h"
#include "Action\IBAction.h"
#include "Fact\IBFact.h"
#include "CanvasBase.h"
#include "Canvas.h"
#include "IBGFact.h"
#include "IBGPlanner.h"

IBGAction::IBGAction(IBActionDef* pDef, IBFact* pPostCond1)
	: IBAction(pDef, pPostCond1)
	, IBGBoxBase(static_cast<IBGFact*>(pPostCond1)->GetCanvas())
	, m_pActionBox(NULL)
{
	m_pActionBox = new IBGActionBox(m_oCanvas, this);
}

IBGAction::~IBGAction()
{
	if (m_pActionBox != NULL)
		delete m_pActionBox;
}

void IBGAction::Resize()
{
	ASSERT(m_pActionBox != NULL);

	m_pActionBox->Resize();

	int w = 0;
	int h = 0;

	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		IBGFact* pFact = static_cast<IBGFact*>(m_aPreCond[i]);

		pFact->Resize();
		w = max(w, pFact->GetW());
		h += pFact->GetH();
		if (i<m_aPreCond.size()-1)
			h += IBGPlanner::s_iFactMinSpace;
	}
	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		IBGFact* pFact = static_cast<IBGFact*>(m_aPreCond[i]);
		pFact->SetW(w);
	}

	if (m_aPreCond.size() > 0)
		w += IBGPlanner::s_iLinkWidth;

	w += m_pActionBox->GetW();
	h = max(h, m_pActionBox->GetH());
	
	SetW(w);
	SetH(h);
}


void IBGAction::Draw() const
{
	ASSERT(m_pActionBox != NULL);

	//IBGBoxBase::DrawFrame(IBGPlanner::s_oBoxColor);

	int x = 0;
	int y = 0;

	x = GetW() - m_pActionBox->GetW();
	y = GetH()/2 - m_pActionBox->GetH()/2;
	m_pActionBox->SetX(x);
	m_pActionBox->SetY(y);
	m_pActionBox->Draw();

	if (m_aPreCond.size())
	{
		x = 0;
		y = 0;
		int w = 0;
		int as = m_pActionBox->GetH() / m_aPreCond.size();
		for (uint i=0 ; i<m_aPreCond.size() ; ++i)
		{
			IBGFact* pFact = static_cast<IBGFact*>(m_aPreCond[i]);
			w = max(w, pFact->GetW());
			pFact->SetX(x);
			pFact->SetY(y);
			pFact->Draw();
			m_oCanvas.CanvasBase::DrawLine(pFact->GetRight(), pFact->GetMidH(), m_pActionBox->GetLeft()-1, m_pActionBox->GetTop()+i*as+as/2, IBGPlanner::s_oLinkColor);

			y += pFact->GetH() + IBGPlanner::s_iFactMinSpace;
		}
	}
}
