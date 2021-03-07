
#include "IBGActionBox.h"
#include "IBPlanner.h"
#include "CanvasBase.h"
#include "Action/IBAction.h"
#include "Action/IBActionDef.h"
#include "IBGraphPlannerDisplay.h"
#include "World/IBObject.h"

IBGActionBox::IBGActionBox(Canvas& parent, const IBAction* pAction)
	: IBGBoxBase(parent)
	, m_pAction(pAction)
{
	m_aAdditionalPostCondBox.resize(m_pAction->GetAdditionnalPostCond().size());

	for (uint32 i = 0; i < m_pAction->GetAdditionnalPostCond().size(); ++i)
	{
		m_aAdditionalPostCondBox[i] = new IBGFactBox(m_oCanvas, m_pAction->GetAdditionnalPostCond()[i]);
	}
}

IBGActionBox::~IBGActionBox()
{
	for (uint32 i = 0; i < m_aAdditionalPostCondBox.size(); ++i)
		delete m_aAdditionalPostCondBox[i];
}


void IBGActionBox::Resize()
{
	sint32 he = IBGraphPlannerDisplay::s_iActionEvalHeight;

	sint32 wt, ht;
	m_oCanvas.CanvasBase::TextSize(wt, ht, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iActionTitleSize, m_pAction->GetDef()->GetName().c_str());
	ht = IBGraphPlannerDisplay::s_iActionTitleHeight;

	sint32 hv = (IBGraphPlannerDisplay::s_iActionVarHeight + IBGraphPlannerDisplay::s_iActionVarSpace) * m_pAction->GetVariables().size();

	sint32 wa = 0;
	sint32 ha = 0;

	for (uint32 i = 0; i < m_aAdditionalPostCondBox.size(); ++i)
		m_aAdditionalPostCondBox[i]->Resize();

	for (uint32 i = 0; i < m_aAdditionalPostCondBox.size(); ++i)
	{
		ha += m_aAdditionalPostCondBox[i]->GetH();
		wa = std::max<int>(m_aAdditionalPostCondBox[i]->GetW(), wa);
	}

	sint16 width = IBGraphPlannerDisplay::s_iActionMinWidth;
	width = std::max<int>(width, wt);
	width = std::max<int>(width, wa);

	sint16 height = he + ht + hv + ha;

	SetH(height);
	SetW(width);
}

sint16 IBGActionBox::GetActionMidHeight() const
{
	sint16 top = IBGraphPlannerDisplay::s_iActionEvalHeight;

	sint16 ha = 0;
	for (uint32 i = 0; i < m_aAdditionalPostCondBox.size(); ++i)
	{
		ha += m_aAdditionalPostCondBox[i]->GetH();
	}

	sint16 bot = GetH() - ha;

	return GetY() + (top + bot) / 2;
}

void IBGActionBox::Draw() const
{
	Color oColor = (m_pAction->GetState() == IBA_State::IBA_Active ? IBGraphPlannerDisplay::s_oActionWorkColor : IBGraphPlannerDisplay::s_oActionColor);

	sint32 ha = 0;
	for (uint32 i = 0; i < m_aAdditionalPostCondBox.size(); ++i)
		ha += m_aAdditionalPostCondBox[i]->GetH();

	m_oCanvas.CanvasBase::DrawRect(0, IBGraphPlannerDisplay::s_iActionEvalHeight, m_oCanvas.GetWidth(), m_oCanvas.GetHeight()-IBGraphPlannerDisplay::s_iActionEvalHeight-ha, oColor);

	float fVal = m_pAction->GetCost();
	m_oCanvas.Print(0, IBGraphPlannerDisplay::s_iActionEvalHeight/2, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iActionEvalSize, LeftCenter, 42, 255, 255, (fVal >= FLT_MAX ? "inf" : "%3.3f"), fVal);
	m_oCanvas.Print(GetW(), IBGraphPlannerDisplay::s_iActionEvalHeight/2, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iActionEvalSize, RightCenter, 42, 255, 255, "%s", IBA_StateString[m_pAction->GetState()]);

	sint16 x = 0;
	sint16 y = IBGraphPlannerDisplay::s_iActionEvalHeight;
	uint16 w = GetW();
	uint16 h = GetH();

	y += IBGraphPlannerDisplay::s_iActionTitleHeight;

	m_oCanvas.CanvasBase::DrawLine(x, y, x+w, y, oColor);
	m_oCanvas.CanvasBase::Print(x+w/2, y-IBGraphPlannerDisplay::s_iActionTitleHeight/2, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iActionTitleSize, Center, IBGraphPlannerDisplay::s_oActionColor, "%s", m_pAction->GetDef()->GetName().c_str());

	if (m_pAction->GetState() != IBA_State::IBA_Destroyed)
	{
		for (const string& sVarName : m_pAction->GetDef()->GetVarNames())
		{
			const IBObject* pObj = m_pAction->GetVariable(sVarName);
			string sVarData = pObj->GetName();

			if (pObj->GetUserData() == nullptr)
			{
				uint32 count = m_pAction->GetPotentialVariableCount(sVarName);
				sVarData = FormatString(" ? (%d)", count);
			}

			m_oCanvas.CanvasBase::Print(x+w/2, y + IBGraphPlannerDisplay::s_iActionVarHeight / 2,
				m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iActionVarHeight, RightCenter, IBGraphPlannerDisplay::s_oActionColor, "%s:", sVarName.c_str());

			m_oCanvas.CanvasBase::Print(x+w/2, y + IBGraphPlannerDisplay::s_iActionVarHeight / 2,
				m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iActionVarHeight, LeftCenter, IBGraphPlannerDisplay::s_oActionColor, " %s", sVarData.c_str());

			y += IBGraphPlannerDisplay::s_iActionVarHeight + IBGraphPlannerDisplay::s_iActionVarSpace;
		}

		for (uint32 i = 0; i < m_aAdditionalPostCondBox.size(); ++i)
		{
			x = GetW() - m_aAdditionalPostCondBox[i]->GetW();

			m_aAdditionalPostCondBox[i]->SetX(x);
			m_aAdditionalPostCondBox[i]->SetY(y);
			m_aAdditionalPostCondBox[i]->Draw();

			y += m_aAdditionalPostCondBox[i]->GetH();
		}

	}
}

