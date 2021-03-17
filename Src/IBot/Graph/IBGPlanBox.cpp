#include "IBGPlanBox.h"

#include "CanvasBase.h"
#include "IBGFactBox.h"
#include "IBGNodeBox.h"
#include "IBGActionPlanBox.h"
#include "IBGActionBox.h"
#include "Action/IBAction.h"
#include "Fact/IBFact.h"
#include "Fact/IBNode.h"
#include "IBGraphPlannerDisplay.h"

IBGPlanBox::IBGPlanBox(Canvas& parent, const class IBNode* pNode)
	: IBGBoxBase(parent)
	, m_pNode(pNode)
	, m_pNodeBox(nullptr)
{
	ASSERT(m_pNode != nullptr);

	m_pNodeBox = new IBGNodeBox(m_oCanvas, m_pNode);

	for (FactSet::const_iterator fact_it = m_pNode->GetFacts().begin(); fact_it != m_pNode->GetFacts().end(); ++fact_it)
	{
		const IBFact* pFact = *fact_it;

		for (ActionSet::const_iterator it = pFact->GetCauseAction().begin(); it != pFact->GetCauseAction().end(); ++it)
		{
			IBAction* pAction = *it;
			m_aActionPlanBox.push_back(new IBGActionPlanBox(m_oCanvas, pAction));
		}
	}
}

IBGPlanBox::~IBGPlanBox()
{
	for (uint i = 0; i < m_aActionPlanBox.size(); ++i)
		delete m_aActionPlanBox[i];

	if (m_pNodeBox != nullptr)
		delete m_pNodeBox;
}

const class IBGNodeBox* IBGPlanBox::GetNodeBox(const class IBNode* pNode) const
{
	if (m_pNode == pNode)
		return m_pNodeBox;

	for (uint i = 0; i < m_aActionPlanBox.size(); ++i)
	{
		ASSERT(m_aActionPlanBox[i] != nullptr);
		
		const IBGPlanBox* pPreCondBox = m_aActionPlanBox[i]->GetGPreCondBox();
		if (pPreCondBox == nullptr)
			continue;

		const IBGNodeBox* pFound = pPreCondBox->GetNodeBox(pNode);
		if (pFound != nullptr)
			return pFound;
	}

	return nullptr;
}

void IBGPlanBox::Init()
{
	if (m_pNodeBox != nullptr)
		m_pNodeBox->Init();

	for (uint i = 0; i < m_aActionPlanBox.size(); ++i)
		delete m_aActionPlanBox[i];

	m_aActionPlanBox.clear();

	for (FactSet::const_iterator fact_it = m_pNode->GetFacts().begin(); fact_it != m_pNode->GetFacts().end(); ++fact_it)
	{
		const IBFact* pFact = *fact_it;

		for (ActionSet::const_iterator it = pFact->GetCauseAction().begin(); it != pFact->GetCauseAction().end(); ++it)
		{
			IBAction* pAction = *it;
			m_aActionPlanBox.push_back(new IBGActionPlanBox(m_oCanvas, pAction));
		}
	}
}


void IBGPlanBox::Resize()
{
	sint16 pw = 0, ph = 0;
	if (m_pNodeBox != nullptr)
	{
		m_pNodeBox->Resize();
		pw = m_pNodeBox->GetW();
		ph = m_pNodeBox->GetH();
	}

	sint16 aw = 0;
	sint16 ah = IBGraphPlannerDisplay::s_iActionMinSpace;

	for (uint i = 0; i < m_aActionPlanBox.size(); ++i)
	{
		m_aActionPlanBox[i]->Resize();
		sint16 w = m_aActionPlanBox[i]->GetW();
		sint16 h = m_aActionPlanBox[i]->GetH();

		aw = std::max<int>(w, aw);
		ah += h;
		ah += IBGraphPlannerDisplay::s_iActionMinSpace;
	}

	SetH(std::max<int>(ph, ah));
	SetW(pw + (aw > 0 ? IBGraphPlannerDisplay::s_iActionLinkSpace + aw : 0));
}

void IBGPlanBox::Draw() const
{
	sint16 x = GetW() - m_pNodeBox->GetW();
	sint16 y = (GetH() - m_pNodeBox->GetH()) / 2;

	m_pNodeBox->SetX(x);
	m_pNodeBox->SetY(y);
	m_pNodeBox->Draw();

	x -= IBGraphPlannerDisplay::s_iActionLinkSpace;
	y = IBGraphPlannerDisplay::s_iActionMinSpace;

	for (uint i = 0; i < m_aActionPlanBox.size(); ++i)
	{
		m_aActionPlanBox[i]->SetX(x - m_aActionPlanBox[i]->GetW());
		m_aActionPlanBox[i]->SetY(y);
		m_aActionPlanBox[i]->Draw();


		for (uint j = 0; j < m_aActionPlanBox[i]->GetAction()->GetPostCond().size(); ++j)
		{
			const IBFact* pPostCond = m_aActionPlanBox[i]->GetAction()->GetPostCond()[j];

			const IBGFactBox* pFactBox = m_pNodeBox->GetFactBox(pPostCond);

			// TODO: Get pin out of action and pin in of fact
			m_oCanvas.DrawLine(m_aActionPlanBox[i]->GetRight() + 1, m_aActionPlanBox[i]->GetY() + m_aActionPlanBox[i]->GetGActionBox()->GetActionMidHeight(), m_pNodeBox->GetX() + pFactBox->GetLeft() - 1, m_pNodeBox->GetY() + pFactBox->GetMidH(), 100, 100, 100);

			// TODO: if action IBA_Impossible -> for each add post cond, find invalid and print line

		}

		y += m_aActionPlanBox[i]->GetH();
		y += IBGraphPlannerDisplay::s_iActionMinSpace;
	}
}
