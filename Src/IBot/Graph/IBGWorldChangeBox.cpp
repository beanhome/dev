#include "IBGWorldChangeBox.h"

#include "CanvasBase.h"
#include "IBGFactBox.h"
#include "Fact/IBFact.h"
#include "Fact/IBWorldChange.h"

#include "Action/IBAction.h"
#include "IBPlanner.h"

#include "IBGraphPlannerDisplay.h"

#define DEBUG_POINTER 1

IBGWorldChangeBox::IBGWorldChangeBox(Canvas& parent, const class IBWorldChange* pWorldChange)
	: IBGBoxBase(parent)
	, m_pWorldChange(pWorldChange)
{
	Init();
}

IBGWorldChangeBox::~IBGWorldChangeBox()
{
	for (uint i=0; i < m_aFactBox.size(); ++i)
	{
		delete m_aFactBox[i];
	}
}

void	 IBGWorldChangeBox::Init()
{
	for (uint i = 0; i < m_aFactBox.size(); ++i)
	{
		delete m_aFactBox[i];
	}

	m_aFactBox.resize(m_pWorldChange->Size());

	uint i = 0;
	for (FactSet::iterator it = m_pWorldChange->GetFacts().begin(); it != m_pWorldChange->GetFacts().end(); ++it, ++i)
	{
		IBFact* pFact = *it;
		m_aFactBox[i] = new IBGFactBox(m_oCanvas, pFact);
	}
}

void IBGWorldChangeBox::Resize()
{
	sint16 pw = IBGraphPlannerDisplay::s_iFactMinWidth;
	sint16 ph = IBGraphPlannerDisplay::s_iMargin;

	for (uint i = 0; i < m_aFactBox.size(); ++i)
	{
		m_aFactBox[i]->Resize();
		pw = std::max<int>(m_aFactBox[i]->GetW(), pw);
		ph += m_aFactBox[i]->GetH();
		ph += IBGraphPlannerDisplay::s_iMargin;
	}

	pw += IBGraphPlannerDisplay::s_iMargin * 2;

	ph += IBGraphPlannerDisplay::s_iFactEvalHeight;

	SetH(ph);
	SetW(pw);
}


void IBGWorldChangeBox::Draw() const
{
	Color oColor = Color(128, 255, 255);

	if (m_pWorldChange->GetAction() != nullptr)
	{
		IBPlanner* pPlanner = m_pWorldChange->GetAction()->GetPlanner();
		if (pPlanner->GetBestNode() == m_pWorldChange)
			oColor = Color(64, 255, 64);
	}

	m_oCanvas.CanvasBase::DrawRect(0, IBGraphPlannerDisplay::s_iFactEvalHeight, m_oCanvas.GetWidth(), m_oCanvas.GetHeight() - IBGraphPlannerDisplay::s_iFactEvalHeight, oColor);

#if DEBUG_POINTER
	m_oCanvas.CanvasBase::Print(m_oCanvas.GetWidth()-2, 2, m_oCanvas.GetPrintFont(), 10, RightTop, Color(125, 240, 195), "0x%x", m_pWorldChange);
#endif

	sint16 x = IBGraphPlannerDisplay::s_iMargin;
	sint16 y = IBGraphPlannerDisplay::s_iMargin;
	uint16 w = GetW() - IBGraphPlannerDisplay::s_iMargin * 2;

	IBCost oCost = m_pWorldChange->GetCost();
	m_oCanvas.Print(x, IBGraphPlannerDisplay::s_iFactEvalHeight / 2, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iFactEvalSize, LeftCenter, 42, 255, 255, "%s", oCost.GetText().c_str());

	y += IBGraphPlannerDisplay::s_iFactEvalHeight;

	for (uint i = 0; i < m_aFactBox.size(); ++i)
	{
		m_aFactBox[i]->SetX(x);
		m_aFactBox[i]->SetY(y);
		m_aFactBox[i]->SetW(w);
		m_aFactBox[i]->Draw();

		y += m_aFactBox[i]->GetH() + IBGraphPlannerDisplay::s_iMargin;
	}
}

const IBGFactBox* IBGWorldChangeBox::GetFactBox(const IBFact* pFact) const
{
	for (uint i = 0; i < m_aFactBox.size(); ++i)
	{
		if (m_aFactBox[i]->GetFact() == pFact)
			return m_aFactBox[i];
	}

	return nullptr;
}