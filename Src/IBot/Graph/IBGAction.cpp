#include "IBGAction.h"
#include "IBGActionBox.h"
#include "Action/IBAction.h"
#include "Action/IBActionDef.h"
#include "Fact/IBFact.h"
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

	// Pre Cond Size
	m_iPreCondHeight = 0;
	m_iPreCondWidth = 0;
	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		IBGFact* pFact = static_cast<IBGFact*>(m_aPreCond[i]);

		pFact->Resize();
		m_iPreCondWidth = std::max<int>(m_iPreCondWidth, pFact->GetW());
		m_iPreCondHeight += pFact->GetH();
		if (i<m_aPreCond.size()-1)
			m_iPreCondHeight += IBGPlanner::s_iFactMinSpace;
	}
	for (uint i=0 ; i<m_aPreCond.size() ; ++i)
	{
		IBGFact* pFact = static_cast<IBGFact*>(m_aPreCond[i]);
		pFact->SetW(m_iPreCondWidth);
	}

	if (m_aPreCond.size() > 0)
		m_iPreCondWidth += IBGPlanner::s_iLinkWidth;

	int w = m_iPreCondWidth + std::max<int>(m_pActionBox->GetW(), m_iCounterWidth);
	int h = std::max<int>(m_iPreCondHeight, m_pActionBox->GetH() + m_iCounterHeight);
	
	SetW(w);
	SetH(h);
}


void IBGAction::Draw() const
{
	ASSERT(m_pActionBox != NULL);

	//IBGBoxBase::DrawFrame(IBGPlanner::s_oBoxColor);

	int x = 0;
	int y = 0;

	// Action Box
	x = m_iPreCondWidth;
	y = GetH()/2 - (m_pActionBox->GetH() + m_iCounterHeight)/2;
	m_pActionBox->SetX(x);
	m_pActionBox->SetY(y);
	m_pActionBox->Draw();

	// Counter
	if (m_eState == IBAction::IBA_Counter)
	{
		y += m_pActionBox->GetH();
		for (uint i=0 ; i<GetCounterPostCond().size() ; ++i)
		{
			IBGFact* pFact = static_cast<IBGFact*>(GetCounterPostCond()[i]);
			pFact->GetFactBox()->SetX(x);
			pFact->GetFactBox()->SetY(y);
			pFact->GetFactBox()->Draw();
			y += pFact->GetFactBox()->GetH();
		}
	}

	// PreCond
	if (m_aPreCond.size())
	{
		x = 0;
		y = 0;
		int w = 0;
		int as = (m_pActionBox->GetH() - IBGPlanner::s_iActionTitleHeight - IBGPlanner::s_iActionEvalHeight) / m_aPreCond.size();
		for (uint i=0 ; i<m_aPreCond.size() ; ++i)
		{
			IBGFact* pFact = static_cast<IBGFact*>(m_aPreCond[i]);
			w = std::max<int>(w, pFact->GetW());
			pFact->SetX(x);
			pFact->SetY(y);
			pFact->Draw();
			m_oCanvas.CanvasBase::DrawLine(pFact->GetRight(), pFact->GetMidH(), m_pActionBox->GetLeft()-1, m_pActionBox->GetTop()+IBGPlanner::s_iActionTitleHeight+IBGPlanner::s_iActionEvalHeight+i*as+as/2, IBGPlanner::s_oLinkColor);

			y += pFact->GetH() + IBGPlanner::s_iFactMinSpace;
		}
	}

	if (m_eState == IBA_Impossible)
	{
		for (uint i=0 ; i<m_aCounterFact.size() ; ++i)
		{
			IBFact* pCounterFact = m_aCounterFact[i];
			if (pCounterFact != NULL)
			{
				IBGFact* pFact = static_cast<IBGFact*>(pCounterFact);
				m_oCanvas.CanvasBase::DrawLine(pFact->GetMidW(), pFact->GetMidH(), m_pActionBox->GetMidW(), m_pActionBox->GetMidH(), IBGPlanner::s_oFalseFactColor);
			}
		}
	}
}
