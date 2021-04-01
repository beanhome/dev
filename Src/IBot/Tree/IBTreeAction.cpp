#include "IBTreeAction.h"

#include "IBPlanner.h"
#include "GEngine.h"
#include "Canvas.h"
#include "Color.h"
#include "Utils.h"
#include "Action/IBAction.h"
#include "Action/IBActionDef.h"
#include "IBTreeBox_Image.h"
#include "IBTreeBox_String.h"
#include "IBTreeBox_Verti.h"

sint32 ActionTitleMarging = 3;
sint32 ActionVarLeftMarging = 8;

sint32 ActionTitleTextSize = 14;
sint32 ActionVarTextSize = 12;

IBTreeAction::IBTreeAction(Canvas& oCanvas, IBTreeBox* pParent, const class IBAction* pAction)
	: IBTreeBox_Horiz(oCanvas, pParent)
	, m_pAction(pAction)
	, m_bExtended(false)
{
	m_pActionTitleFont = m_oCanvas.GetGEngine()->GetFontResource(m_oCanvas.GetPrintFont(), ActionTitleTextSize);
	m_pActionVarFont = m_oCanvas.GetGEngine()->GetFontResource(m_oCanvas.GetPrintFont(), ActionVarTextSize);
	ASSERT(m_pActionTitleFont != nullptr);
	ASSERT(m_pActionVarFont != nullptr);

	m_pRightArrowImage = m_oCanvas.GetGEngine()->GetImageResource(DATA_DIR "/BotLife/Arrow_Right.png");
	m_pDownArrowImage = m_oCanvas.GetGEngine()->GetImageResource(DATA_DIR "/BotLife/Arrow_Down.png");
}

IBTreeAction::~IBTreeAction()
{
}

void IBTreeAction::RefreshTree()
{
	Construct();
}


string IBTreeAction::GetFullName() const
{
	const string& ActionName = (m_pAction != nullptr ? m_pAction->GetDef()->GetName() : "none");

	string sFullFactName = ActionName + "(";

	for (uint i = 0; i < m_pAction->GetDef()->GetVarNames().size(); ++i)
	{
		if (i != 0)
			sFullFactName += ",";

		const string& var_name = m_pAction->GetDef()->GetVarNames()[i];
		const IBObject* obj = m_pAction->GetVariable(var_name);
		sFullFactName += (obj != nullptr ? obj->GetName() : "none");
	}

	sFullFactName += ")";

	return sFullFactName;
}


void IBTreeAction::Construct()
{
	for (IBTreeBox*& pTreeBox : m_aChildren)
	{
		if (pTreeBox != nullptr)
			delete pTreeBox;
		pTreeBox = nullptr;
	}

	m_aChildren.clear();
	m_pExtendArrow = nullptr;

	if (!m_bExtended)
	{
		m_pExtendArrow = new IBTreeBox_Image(m_oCanvas, this);
		m_pExtendArrow->SetImage(m_pRightArrowImage);

		IBTreeBox_String* FullName = new IBTreeBox_String(m_oCanvas, this);
		FullName->SetString(GetFullName());
		FullName->SetFont(m_pActionTitleFont);
		FullName->SetColor(Color::Black);

		m_aChildren.push_back(m_pExtendArrow);
		m_aChildren.push_back(FullName);
	}
	else
	{
		IBTreeBox_Verti* pVerti = new IBTreeBox_Verti(m_oCanvas, this);

		IBTreeBox_String* ActionName = new IBTreeBox_String(m_oCanvas, this);
		ActionName->SetString(m_pAction->GetDef()->GetName());
		ActionName->SetFont(m_pActionTitleFont);
		ActionName->SetColor(Color::Black);

		pVerti->AddChild(ActionName);

		for (uint i = 0; i < m_pAction->GetDef()->GetVarNames().size(); ++i)
		{
			const string& var_name = m_pAction->GetDef()->GetVarNames()[i];
			const IBObject* var_obj = m_pAction->GetVariable(var_name);
			const string& obj_name = (var_obj != nullptr ? var_obj->GetName() : "none");

			IBTreeBox_String* VarName = new IBTreeBox_String(m_oCanvas, this);
			VarName->SetString(FormatString("  %s: %s", var_name.c_str(), obj_name.c_str()));
			VarName->SetFont(m_pActionVarFont);
			VarName->SetColor(Color::Black);

			pVerti->AddChild(VarName);
		}

		m_pExtendArrow = new IBTreeBox_Image(m_oCanvas, this);
		m_pExtendArrow->SetImage(m_pDownArrowImage);

		m_aChildren.push_back(m_pExtendArrow);
		m_aChildren.push_back(pVerti);
	}

	UpdateSize();
}

void IBTreeAction::OnMouseClick(sint32 iMouseX, sint32 iMouseY)
{
	IBTreeBox_Horiz::OnMouseClick(iMouseX, iMouseY);

	if (m_pExtendArrow != nullptr && m_pExtendArrow->IsMouseOver())
	{
		m_bExtended = !m_bExtended;

		Construct();
	}
}


void IBTreeAction::Draw() const
{
	m_oCanvas.DrawFillRect(m_iPosX, m_iPosY, m_iWidth, m_iHeight, Color::Magenta);

	IBTreeBox_Horiz::Draw();

	if (m_bExtended && m_pExtendArrow != nullptr && m_pAction != nullptr)
	{
		sint32 x = (m_pExtendArrow->GetPosX() + m_pExtendArrow->GetWidth() / 2);
		sint32 y = m_pExtendArrow->GetPosY() + m_pExtendArrow->GetHeight();

		uint nb = m_pAction->GetDef()->GetVarNames().size();

		for (uint i = 0; i < nb; ++i)
		{
			sint32 h = m_pActionVarFont->GetSize();

			m_oCanvas.DrawLine(x, y, x, y + (i < nb - 1 ? h : h / 2), Color::White);
			m_oCanvas.DrawLine(x, y + h / 2, x + m_pExtendArrow->GetWidth() / 2, y + h / 2, Color::White);

			y += h;
		}
	}

	m_oCanvas.DrawRect(m_iPosX, m_iPosY, m_iWidth, m_iHeight, Color::Red);
}
