#include "IBGFact.h"
#include "IBGActionBox.h"
#include "Action\IBAction.h"
#include "Fact\IBFact.h"
#include "CanvasBase.h"
#include "Canvas.h"
#include "IBGAction.h"
#include "IBGPlanner.h"

IBGFact::IBGFact(IBFactDef* pDef, const vector<IBObject*>& aUserData, CanvasBase& oParentCanvas)
	: IBFact(pDef, aUserData)
	, IBGBoxBase(oParentCanvas)
	, m_pFactBox(NULL)
{
	m_pFactBox = new IBGFactBox(m_oCanvas, this);
}

IBGFact::~IBGFact()
{
	if (m_pFactBox != NULL)
		delete m_pFactBox;
}

void IBGFact::Resize()
{
	ASSERT(m_pFactBox != NULL);

	int w = 0;
	int h = 0;

	m_pFactBox->Resize();

	w = m_pFactBox->GetW();
	h = m_pFactBox->GetH();

	if (m_pCauseAction != NULL)
	{
		IBGAction* pCauseAction = static_cast<IBGAction*>(m_pCauseAction);
		pCauseAction->Resize();

		w += IBGPlanner::s_iLinkWidth + pCauseAction->GetW();
		h = max(h, pCauseAction->GetH());
	}
	
	SetW(w);
	SetH(h);
}


void IBGFact::Draw() const
{
	ASSERT(m_pFactBox != NULL);

	//IBGBoxBase::DrawFrame(IBGPlanner::s_oBoxColor);

	int x = 0;
	int y = 0;

	x = GetW() - m_pFactBox->GetW();
	y = GetH()/2 - m_pFactBox->GetH()/2;
	m_pFactBox->SetX(x);
	m_pFactBox->SetY(y);
	m_pFactBox->Draw();

	if (m_pCauseAction != NULL)
	{
		IBGAction* pCauseAction = static_cast<IBGAction*>(m_pCauseAction);

		y = GetH()/2 - pCauseAction->GetH()/2;
		x -= IBGPlanner::s_iLinkWidth;
		x -= pCauseAction->GetW();
		pCauseAction->SetX(x);
		pCauseAction->SetY(y);
		pCauseAction->Draw();

		m_oCanvas.CanvasBase::DrawLine(pCauseAction->GetRight(), pCauseAction->GetMidH(), m_pFactBox->GetLeft()-1, m_pFactBox->GetMidH(), IBGPlanner::s_oLinkColor);
	}
}
