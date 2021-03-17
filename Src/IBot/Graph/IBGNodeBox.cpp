#include "IBGNodeBox.h"

#include "CanvasBase.h"
#include "IBGFactBox.h"
#include "Fact/IBFact.h"
#include "Fact/IBNode.h"

#include "Action/IBAction.h"
#include "IBPlanner.h"

#include "IBGraphPlannerDisplay.h"

#define DEBUG_POINTER 1

IBGNodeBox::IBGNodeBox(Canvas& parent, const class IBNode* pNode)
	: IBGBoxBase(parent)
	, m_pNode(pNode)
{
	Init();
}

IBGNodeBox::~IBGNodeBox()
{
	for (uint i=0; i < m_aFactBox.size(); ++i)
	{
		delete m_aFactBox[i];
	}
}

void	 IBGNodeBox::Init()
{
	for (uint i = 0; i < m_aFactBox.size(); ++i)
	{
		delete m_aFactBox[i];
	}

	m_aFactBox.resize(m_pNode->Size());

	uint i = 0;
	for (FactSet::iterator it = m_pNode->GetFacts().begin(); it != m_pNode->GetFacts().end(); ++it, ++i)
	{
		IBFact* pFact = *it;
		m_aFactBox[i] = new IBGFactBox(m_oCanvas, pFact);
	}
}

void IBGNodeBox::Resize()
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


void IBGNodeBox::Draw() const
{
	Color oColor = Color(128, 255, 255);

	if (m_pNode->GetAction() != nullptr)
	{
		IBPlanner* pPlanner = m_pNode->GetAction()->GetPlanner();
		if (pPlanner->GetBestNode() == m_pNode)
			oColor = Color(64, 255, 64);
	}

	m_oCanvas.CanvasBase::DrawRect(0, IBGraphPlannerDisplay::s_iFactEvalHeight, m_oCanvas.GetWidth(), m_oCanvas.GetHeight() - IBGraphPlannerDisplay::s_iFactEvalHeight, oColor);

#if DEBUG_POINTER
	m_oCanvas.CanvasBase::Print(m_oCanvas.GetWidth()-2, 2, m_oCanvas.GetPrintFont(), 10, RightTop, Color(125, 240, 195), "0x%x", m_pNode);
#endif

	sint16 x = IBGraphPlannerDisplay::s_iMargin;
	sint16 y = IBGraphPlannerDisplay::s_iMargin;
	uint16 w = GetW() - IBGraphPlannerDisplay::s_iMargin * 2;

	IBCost oCost = m_pNode->GetCost();
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

const IBGFactBox* IBGNodeBox::GetFactBox(const IBFact* pFact) const
{
	for (uint i = 0; i < m_aFactBox.size(); ++i)
	{
		if (m_aFactBox[i]->GetFact() == pFact)
			return m_aFactBox[i];
	}

	return nullptr;
}