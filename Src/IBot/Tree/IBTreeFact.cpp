#include "IBTreeFact.h"

#include "IBPlanner.h"
#include "GEngine.h"
#include "Canvas.h"
#include "Color.h"
#include "Utils.h"
#include "Fact/IBFactDef.h"

uint16 FactTitleTextSize = 14;
uint16 FactVarTextSize = 12;
sint32 FactTitleLeftMarging = 3;
sint32 FactVarLeftMarging = 8;
sint32 FactRightMarging = 3;

IBTreeFact::IBTreeFact(const class IBFact* m_pFact)
	: m_pFact(m_pFact)
{
}

IBTreeFact::~IBTreeFact()
{
}

void IBTreeFact::Size(Canvas& oCanvas, sint32& Width, sint32& Height)
{
	Width = 0;
	Height = 0;

	if (m_pFact == nullptr)
		return;

	sint32 w, h;

	const string& FactTitle = m_pFact->GetFactDef()->GetName();
	oCanvas.TextSize(w, h, oCanvas.GetPrintFont(), FactTitleTextSize, FactTitle.c_str());

	Width = w + FactTitleLeftMarging + FactRightMarging;
	Height = FactTitleTextSize;

	for (VarMap::const_iterator it = m_pFact->GetVariables().begin(); it != m_pFact->GetVariables().end(); ++it)
	{
		const string& var_name = it->first;
		const IBObject& var_obj = it->second;

		oCanvas.TextSize(w, h, oCanvas.GetPrintFont(), FactVarTextSize, "%s: %s", var_name.c_str(), var_obj.GetName().c_str());

		Width = std::max(Width, w + FactVarLeftMarging + FactRightMarging);
		Height += FactVarTextSize;
	}
}


void IBTreeFact::Draw(Canvas& oCanvas, sint32 x, sint32 y)
{
	//oCanvas.DrawRect(x, y, w, h, FrameColor);
	oCanvas.Print(x + FactTitleLeftMarging, y + FactTitleTextSize / 2, oCanvas.GetPrintFont(), FactTitleTextSize, ETextAlign::LeftCenter, Color::Black, m_pFact->GetFactDef()->GetName().c_str());
	y += FactTitleTextSize;

	for (VarMap::const_iterator it = m_pFact->GetVariables().begin(); it != m_pFact->GetVariables().end(); ++it)
	{
		const string& var_name = it->first;
		const IBObject& var_obj = it->second;

		oCanvas.Print(x + FactVarLeftMarging, y + FactVarTextSize / 2, oCanvas.GetPrintFont(), FactVarTextSize, ETextAlign::LeftCenter, Color::Black, "%s: %s", var_name.c_str(), var_obj.GetName().c_str());
		y += FactVarTextSize;
	}
}
