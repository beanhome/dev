#include "IBGFactBox.h"

#include "IBPlanner.h"
#include "CanvasBase.h"
#include "Fact/IBFact.h"
#include "Fact/IBFactDef.h"
#include "IBGraphPlannerDisplay.h"
#include "World/IBObject.h"

#define DEBUG_POINTER 0
#define DISPLAY_HEADER 0

IBGFactBox::IBGFactBox(Canvas& parent, IBFact* pFact)
	: IBGBoxBase(parent)
	, m_pFact(pFact)
{
}

IBGFactBox::~IBGFactBox()
{
}


string IBGFactBox::GetVarText(const string& name, const IBObject& obj) const
{
	return FormatString("%s %s", name.c_str(), (obj.GetUserData() != nullptr ? obj.GetName().c_str() : "?"));
}


void IBGFactBox::Resize()
{
	int width = IBGraphPlannerDisplay::s_iFactMinWidth;

	sint32 w, h;
#if DEBUG_POINTER
	m_oCanvas.CanvasBase::TextSize(w, h, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iFactTitleSize, "%s %s 0x%x", (m_pFact->IsInverted() ? "!" : ""), m_pFact->GetFactDef()->GetName().c_str(), m_pFact);
#else
	m_oCanvas.CanvasBase::TextSize(w, h, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iFactTitleSize, "%s %s", (m_pFact->IsInverted() ? "!" : ""), m_pFact->GetFactDef()->GetName().c_str());
#endif

	width = std::max<int>(width, w+4);

	for (VarMap::const_reverse_iterator it = m_pFact->GetVariables().rbegin(); it != m_pFact->GetVariables().rend(); ++it)
	{
		m_oCanvas.CanvasBase::TextSize(w, h, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iFactVarHeight, GetVarText(it->first, it->second).c_str());
		width = std::max<int>(width, w + 4);
	}

	int body = m_pFact->GetVariables().size()*IBGraphPlannerDisplay::s_iFactVarHeight + (m_pFact->GetVariables().size() + 1)*IBGraphPlannerDisplay::s_iFactVarSpace;
#if DISPLAY_HEADER
	SetH(IBGraphPlannerDisplay::s_iFactEvalHeight + IBGraphPlannerDisplay::s_iFactTitleHeight + std::max<uint>(IBGraphPlannerDisplay::s_iFactMinHeight, body));
#else
	SetH(IBGraphPlannerDisplay::s_iFactTitleHeight + std::max<uint>(IBGraphPlannerDisplay::s_iFactMinHeight, body));
#endif
	SetW(width);
}


void IBGFactBox::Draw() const
{
	Color oColor = (m_pFact->IsTrue() ? IBGraphPlannerDisplay::s_oFactColor : IBGraphPlannerDisplay::s_oFalseFactColor);

	sint16 x = 0;
	sint16 y = 0;
	uint16 w = GetW();
	uint16 h = GetH();

#if DISPLAY_HEADER
	y += IBGraphPlannerDisplay::s_iFactEvalHeight;
#endif

	// Frame
	m_oCanvas.CanvasBase::DrawRect(0, y, w, h-y, oColor);
	
#if DISPLAY_HEADER
	// Top left Eval
	int iCost = m_pFact->GetCost();
	m_oCanvas.Print(x, IBGraphPlannerDisplay::s_iFactEvalHeight/2, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iFactEvalSize, LeftCenter, 42, 255, 255, (iCost >= INT32_MAX ? "inf" : "%d"), iCost);
	// Top right result
	IBF_Result res = (m_pFact->IsTrue() ? IBF_OK : /*m_pFact->IsResolved() ? IBF_RESOLVED :*/ IBF_FAIL);
	m_oCanvas.Print(w, IBGraphPlannerDisplay::s_iFactEvalHeight/2, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iFactEvalSize, RightCenter, 42, 255, 255, IBF_ResultString[res]);
#endif

#if DEBUG_POINTER
	m_oCanvas.CanvasBase::Print(x+w/2, y+IBGraphPlannerDisplay::s_iFactTitleHeight/2, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iFactTitleSize, Center, IBGraphPlannerDisplay::s_oFactColor, "%s %s 0x%x", (m_pFact->IsInverted() ? "!" : ""), m_pFact->GetFactDef()->GetName().c_str(), m_pFact);
#else
	m_oCanvas.CanvasBase::Print(x+w/2, y+IBGraphPlannerDisplay::s_iFactTitleHeight/2, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iFactTitleSize, Center, IBGraphPlannerDisplay::s_oFactColor, "%s %s", (m_pFact->IsInverted() ? "!" : ""), m_pFact->GetFactDef()->GetName().c_str());
#endif

	y += IBGraphPlannerDisplay::s_iFactTitleHeight;

	// Title separator
	m_oCanvas.CanvasBase::DrawLine(x, y, x + w, y, oColor);

	// Variables
	for (uint i = 0; i < m_pFact->GetFactDef()->GetDegree(); ++i)
	{
		const string& var_name = m_pFact->GetFactDef()->GetVariableName(i);
		const IBObject* pObj = m_pFact->GetVariable(var_name);
		ASSERT(pObj != nullptr);
		Color c = IBGraphPlannerDisplay::s_oFactColor;
		m_oCanvas.CanvasBase::Print(x + w / 2, y + IBGraphPlannerDisplay::s_iFactVarSpace + IBGraphPlannerDisplay::s_iFactVarHeight / 2, m_oCanvas.GetPrintFont(), IBGraphPlannerDisplay::s_iFactVarHeight, Center, c, GetVarText(var_name, *pObj).c_str());
		y += IBGraphPlannerDisplay::s_iFactVarHeight + IBGraphPlannerDisplay::s_iFactVarSpace;
	}
}
