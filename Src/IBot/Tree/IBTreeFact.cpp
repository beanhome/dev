#include "IBTreeFact.h"

#include "IBPlanner.h"
#include "GEngine.h"
#include "Canvas.h"
#include "Color.h"
#include "Utils.h"
#include "Fact/IBFactDef.h"
#include "IBTreeAction.h"
#include "IBTreeBox_Image.h"
#include "IBTreeBox_String.h"
#include "IBTreeBox_Verti.h"
#include "IBTreeActionNode.h"

uint16 FactTitleTextSize = 14;
uint16 FactVarTextSize = 12;
sint32 FactTitleLeftMarging = 3;
sint32 FactVarLeftMarging = 8;
sint32 FactRightMarging = 3;

IBTreeFact::IBTreeFact(Canvas& oCanvas, IBTreeBox* pParent, const class IBFact* pFact)
	: IBTreeBox_Horiz(oCanvas, pParent)
	, m_pFact(pFact)
	, m_pExtendArrow(nullptr)
	, m_pFoldArrow(nullptr)
	, m_bExtended(false)
	, m_bFolded(false)
{
	m_pFactTitleFont = m_oCanvas.GetGEngine()->GetFontResource(m_oCanvas.GetPrintFont(), FactTitleTextSize);
	m_pFactVarFont = m_oCanvas.GetGEngine()->GetFontResource(m_oCanvas.GetPrintFont(), FactVarTextSize);
	ASSERT(m_pFactTitleFont != nullptr);
	ASSERT(m_pFactVarFont != nullptr);

	m_pRightArrowImage = m_oCanvas.GetGEngine()->GetImageResource(DATA_DIR "/BotLife/Arrow_Right.png");
	m_pDownArrowImage = m_oCanvas.GetGEngine()->GetImageResource(DATA_DIR "/BotLife/Arrow_Down.png");
}

IBTreeFact::~IBTreeFact()
{
	for (auto& pTreeAction : m_aTreeActionNodes)
	{
		delete pTreeAction;
		pTreeAction = nullptr;
	}
}

void IBTreeFact::RefreshTree()
{
	if (m_aTreeActionNodes.size() != m_pFact->GetCauseAction().size())
	{
		for (IBTreeActionNode*& pTreeAction : m_aTreeActionNodes)
		{
			if (pTreeAction == nullptr)
				continue;

			if (m_pFact->GetCauseAction().find(const_cast<IBAction*>(pTreeAction->m_pAction)) == m_pFact->GetCauseAction().cend())
			{
				delete pTreeAction;
				pTreeAction = nullptr;
			}
		}

		m_aTreeActionNodes.remove(nullptr);

		for (const IBAction* pAction : m_pFact->GetCauseAction())
		{
			if (std::find_if(m_aTreeActionNodes.begin(), m_aTreeActionNodes.end(), [pAction](class IBTreeActionNode* Entry) { return Entry->m_pAction == pAction; }) == m_aTreeActionNodes.cend())
			{
				m_aTreeActionNodes.push_back(new IBTreeActionNode(m_oCanvas, m_pParent, pAction));
			}
		}
	}

	for (IBTreeActionNode* pTreeActionNode : m_aTreeActionNodes)
	{
		pTreeActionNode->RefreshTree();
	}

	Construct();
}


string IBTreeFact::GetFullName() const
{
	string sFullFactName = m_pFact->GetFactDef()->GetName() + "(";

	for (uint i = 0; i < m_pFact->GetFactDef()->GetDegree(); ++i)
	{
		if (i != 0)
			sFullFactName += ",";

		const string& var_name = m_pFact->GetFactDef()->GetVariableName(i);
		const IBObject* obj = m_pFact->GetVariable(var_name);

		sFullFactName += obj->GetName();
	}

	sFullFactName += ")";

	return sFullFactName;
}

void IBTreeFact::Construct()
{
	for (IBTreeBox*& pTreeBox : m_aChildren)
	{
		if (pTreeBox != nullptr)
			delete pTreeBox;
		pTreeBox = nullptr;
	}

	m_aChildren.clear();

	m_pFoldArrow = new IBTreeBox_Image(m_oCanvas, this);
	m_pFoldArrow->SetImage(m_bFolded ? m_pRightArrowImage : m_pDownArrowImage);

	m_pExtendArrow = new IBTreeBox_Image(m_oCanvas, this);
	m_pExtendArrow->SetImage(m_bExtended ? m_pDownArrowImage : m_pRightArrowImage);

	m_aChildren.push_back(m_pFoldArrow);
	m_aChildren.push_back(m_pExtendArrow);

	if (!m_bExtended)
	{
		IBTreeBox_String* FullName = new IBTreeBox_String(m_oCanvas, this);
		FullName->SetString(GetFullName());
		FullName->SetFont(m_pFactTitleFont);
		FullName->SetColor(Color::Black);

		m_aChildren.push_back(FullName);
	}
	else
	{
		IBTreeBox_Verti* pVerti = new IBTreeBox_Verti(m_oCanvas, this);

		IBTreeBox_String* FactName = new IBTreeBox_String(m_oCanvas, this);
		FactName->SetString(m_pFact->GetFactDef()->GetName());
		FactName->SetFont(m_pFactTitleFont);
		FactName->SetColor(Color::Black);

		pVerti->AddChild(FactName);

		for (uint i = 0; i < m_pFact->GetFactDef()->GetDegree(); ++i)
		{
			const string& var_name = m_pFact->GetFactDef()->GetVariableName(i);
			const IBObject* var_obj = m_pFact->GetVariable(var_name);
			const string& obj_name = (var_obj != nullptr ? var_obj->GetName() : "none");

			IBTreeBox_String* FactVar = new IBTreeBox_String(m_oCanvas, this);
			FactVar->SetString(FormatString("  %s: %s", var_name.c_str(), obj_name.c_str()));
			FactVar->SetFont(m_pFactVarFont);
			FactVar->SetColor(Color::Black);

			pVerti->AddChild(FactVar);
		}

		m_aChildren.push_back(pVerti);
	}

	UpdateSize();
}

void IBTreeFact::OnMouseClick(sint32 iMouseX, sint32 iMouseY)
{
	IBTreeBox_Horiz::OnMouseClick(iMouseX, iMouseY);

	if (m_pExtendArrow != nullptr && m_pExtendArrow->IsMouseOver())
	{
		m_bExtended = !m_bExtended;
		Construct();
	}

	if (m_pFoldArrow != nullptr && m_pFoldArrow->IsMouseOver())
	{
		m_bFolded = !m_bFolded;
		m_pFoldArrow->SetImage(m_bFolded ? m_pRightArrowImage : m_pDownArrowImage);
		m_pParent->UpdateSize();
	}
}

void IBTreeFact::Draw() const
{
	Color c = (m_pFact != nullptr && m_pFact->IsTrue() ? Color::Green : Color::Red);

	m_oCanvas.DrawFillRect(m_iPosX, m_iPosY, m_iWidth, m_iHeight, c);

	IBTreeBox_Horiz::Draw();

	if (m_bExtended && m_pExtendArrow != nullptr && m_pFact != nullptr)
	{
		sint32 x = (m_pExtendArrow->GetPosX() + m_pExtendArrow->GetWidth() / 2);
		sint32 y = m_pExtendArrow->GetPosY() + m_pExtendArrow->GetHeight();

		uint nb = m_pFact->GetFactDef()->GetDegree();

		for (uint i = 0; i < m_pFact->GetFactDef()->GetDegree(); ++i)
		{
			sint32 h = m_pFactVarFont->GetSize();

			m_oCanvas.DrawLine(x, y, x, y + (i<nb-1?h:h/2), Color::White);
			m_oCanvas.DrawLine(x, y + h/2, x + m_pExtendArrow->GetWidth()/2, y + h/2, Color::White);

			y += h;
		}
	}
}
