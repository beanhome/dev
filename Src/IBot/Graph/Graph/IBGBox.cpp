#include "IBGBox.h"
#include "IBGActionBox.h"
#include "Action\IBAction.h"
#include "Fact\IBFact.h"
#include "IBPlannerGraph.h"
#include "CanvasBase.h"
#include "Canvas.h"

IBGBox::IBGBox(CanvasBase& parent, IBFact* pFact)
	: IBGBoxBase(parent)
	, m_pFactBox(NULL)
	, m_pActionBox(NULL)
{
	m_pFactBox = new IBGFactBox(m_oCanvas, pFact);

	IBAction* pAction = pFact->GetCauseAction();
	if (pAction != NULL)
	{
		m_pActionBox = new IBGActionBox(m_oCanvas, pAction);

		for (uint i=0 ; i<pAction->GetPreCond().size() ; ++i)
		{
			IBFact* pPreFact = pAction->GetPreCond()[i];

			IBGBox* pPreBox = new IBGBox(m_oCanvas, pPreFact);
			m_aPreBox.push_back(pPreBox);
		}
	}
}

IBGBox::~IBGBox()
{
	if (m_pFactBox != NULL)
		delete m_pFactBox;

	if (m_pActionBox != NULL)
		delete m_pActionBox;

	for (uint i=0 ; i<m_aPreBox.size() ; ++i)
	{
		delete m_aPreBox[i];
	}
}

void IBGBox::Resize()
{
	ASSERT(m_pFactBox != NULL);

	m_pFactBox->Resize();

	if (m_pActionBox != NULL)
		m_pActionBox->Resize();

	int w = 0;
	int h = 0;
	for (uint i=0 ; i<m_aPreBox.size() ; ++i)
	{
		m_aPreBox[i]->Resize();
		w = max(w, m_aPreBox[i]->GetW());
		h += m_aPreBox[i]->GetH();
		if (i<m_aPreBox.size()-1)
			h += IBPlannerGraph::s_iFactMinSpace;
	}
	for (uint i=0 ; i<m_aPreBox.size() ; ++i)
	{
		m_aPreBox[i]->SetW(w);
	}

	if (m_aPreBox.size() > 0)
		w += IBPlannerGraph::s_iLinkWidth;

	if (m_pActionBox != NULL)
	{
		w += IBPlannerGraph::s_iLinkWidth + m_pActionBox->GetW();
		h = max(h, m_pActionBox->GetH());
	}

	w += m_pFactBox->GetW();
	h = max(h, m_pFactBox->GetH());
	
	SetW(w);
	SetH(h);
}


void IBGBox::Draw() const
{
	ASSERT(m_pFactBox != NULL);
	ASSERT(m_aPreBox.size() == 0 || m_pActionBox != NULL);

	//IBGBoxBase::DrawFrame(IBPlannerGraph::s_oBoxColor);

	int x = 0;
	int y = 0;

	x = GetW() - m_pFactBox->GetW();
	y = GetH()/2 - m_pFactBox->GetH()/2;
	m_pFactBox->SetX(x);
	m_pFactBox->SetY(y);
	m_pFactBox->Draw();

	if (m_pActionBox != NULL)
	{
		y = GetH()/2 - m_pActionBox->GetH()/2;
		x -= IBPlannerGraph::s_iLinkWidth;
		x -= m_pActionBox->GetW();
		m_pActionBox->SetX(x);
		m_pActionBox->SetY(y);
		m_pActionBox->Draw();

		m_oCanvas.CanvasBase::DrawLine(m_pActionBox->GetRight(), m_pActionBox->GetMidH(), m_pFactBox->GetLeft(), m_pFactBox->GetMidH(), IBPlannerGraph::s_oLinkColor);
	}

	if (m_aPreBox.size())
	{
		x = 0;
		y = 0;
		int w = 0;
		int as = m_pActionBox->GetH() / m_aPreBox.size();
		for (uint i=0 ; i<m_aPreBox.size() ; ++i)
		{
			w = max(w, m_aPreBox[i]->GetW());
			m_aPreBox[i]->SetX(x);
			m_aPreBox[i]->SetY(y);
			m_aPreBox[i]->Draw();
			m_oCanvas.CanvasBase::DrawLine(m_aPreBox[i]->GetRight(), m_aPreBox[i]->GetMidH(), m_pActionBox->GetLeft(), m_pActionBox->GetTop()+i*as+as/2, IBPlannerGraph::s_oLinkColor);

			y += m_aPreBox[i]->GetH() + IBPlannerGraph::s_iFactMinSpace;
		}
	}
}
