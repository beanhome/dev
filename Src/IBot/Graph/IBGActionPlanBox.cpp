#include "IBGActionPlanBox.h"

#include "CanvasBase.h"
#include "IBGNodeBox.h"
#include "IBGPlanBox.h"
#include "IBGActionBox.h"
#include "Action/IBAction.h"
#include "Fact/IBFact.h"
#include "Fact/IBNode.h"
#include "IBGraphPlannerDisplay.h"

IBGActionPlanBox::IBGActionPlanBox(Canvas& parent, const class IBAction* pAction)
	: IBGBoxBase(parent)
	, m_pAction(pAction)
	, m_pActionBox(nullptr)
	, m_pPreCondBox(nullptr)
{
	m_pActionBox = new IBGActionBox(m_oCanvas, m_pAction);
	if (m_pAction->GetPreNode() != nullptr)
		m_pPreCondBox = new IBGPlanBox(m_oCanvas, m_pAction->GetPreNode());
}

IBGActionPlanBox::~IBGActionPlanBox()
{
	delete m_pActionBox;
	if (m_pPreCondBox != nullptr)
		delete m_pPreCondBox;
}

void IBGActionPlanBox::Resize()
{
	m_pActionBox->Resize();

	sint16 pcw = 0;
	sint16 pch = 0;
	if (m_pPreCondBox != nullptr && m_pAction->GetState() != IBA_State::IBA_Impossible && m_pPreCondBox->GetNode()->GetFacts().size() > 0)
	{
		m_pPreCondBox->Resize();
		pcw = m_pPreCondBox->GetW();
		pch = m_pPreCondBox->GetH();
	}

	sint16 w = m_pActionBox->GetW() + IBGraphPlannerDisplay::s_iActionLinkSpace + pcw;
	sint16 h = std::max<int>(m_pActionBox->GetH(), pch);

	SetH(h);
	SetW(w);
}

void IBGActionPlanBox::Draw() const
{
	//m_oCanvas.DrawRect(0, 0, GetW(), GetH(), 255, 0, 255);

	sint16 x = GetW() - m_pActionBox->GetW();
	sint16 y = (GetH() - m_pActionBox->GetH()) / 2;

	m_pActionBox->SetX(x);
	m_pActionBox->SetY(y);
	m_pActionBox->Draw();

	//m_oCanvas.DrawRect(m_pActionBox->GetX(), m_pActionBox->GetY(), m_pActionBox->GetW(), m_pActionBox->GetH(), 255, 255, 0);

	if (m_pPreCondBox != nullptr && m_pAction->GetState() != IBA_State::IBA_Impossible && m_pPreCondBox->GetNode()->GetFacts().size() > 0)
	{
		x -= IBGraphPlannerDisplay::s_iActionLinkSpace;
		x -= m_pPreCondBox->GetW();
		y = (GetH() - m_pPreCondBox->GetH()) / 2;

		m_pPreCondBox->SetX(x);
		m_pPreCondBox->SetY(y);
		m_pPreCondBox->Draw();

		m_oCanvas.DrawLine(m_pPreCondBox->GetRight(), m_pPreCondBox->GetMidH(), m_pActionBox->GetLeft(), m_pActionBox->GetActionMidHeight(), 100, 100, 100);
	}
}
