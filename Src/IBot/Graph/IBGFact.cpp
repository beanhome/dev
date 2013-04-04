#include "IBGFact.h"
#include "IBGActionBox.h"
#include "Action/IBAction.h"
#include "Fact/IBFact.h"
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

	int wa = 0;
	int ha = 0;
	for (ActionSet::iterator it = m_aCauseAction.begin() ; it != m_aCauseAction.end() ; ++it)
	{
		IBGAction* pAction = static_cast<IBGAction*>(*it);
		pAction->Resize();

		wa = std::max<int>(pAction->GetW(), wa);
		ha += pAction->GetH() + IBGPlanner::s_iActionMinSpace;
	}
	if (ha > (int)IBGPlanner::s_iActionMinSpace)
		ha -= IBGPlanner::s_iActionMinSpace;

	w += IBGPlanner::s_iLinkWidth + wa;
	h = std::max<int>(h, ha);
	
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

	y = 0;
	x -= IBGPlanner::s_iLinkWidth;
	for (ActionSet::const_iterator it = m_aCauseAction.begin() ; it != m_aCauseAction.end() ; ++it)
	{
		IBGAction* pAction = static_cast<IBGAction*>(*it);

		pAction->SetX(x - pAction->GetW());
		pAction->SetY(y);
		pAction->Draw();

		m_oCanvas.CanvasBase::DrawLine(pAction->GetRight(), pAction->GetMidH(), m_pFactBox->GetLeft()-1, m_pFactBox->GetMidH(), IBGPlanner::s_oLinkColor);

		y+= pAction->GetH() + IBGPlanner::s_iActionMinSpace;
	}
}
