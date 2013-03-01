#include "BLGoalMenu.h"
#include "Map\BLSquare.h"
#include "World\IBVector2.h"
#include "World\BLProp.h"
#include "World\IBInt.h"
#include "BLBot.h"

int BLGoalMenu::s_iYL = 18;
int BLGoalMenu::s_iTextHeight = 14;
Color BLGoalMenu::s_cBackGroundColor = Color(128, 128, 128);
Color BLGoalMenu::s_cForeGroundColor = Color(255, 255, 255);
Color BLGoalMenu::s_cNormalTextColor = Color(0, 0, 0);
Color BLGoalMenu::s_cMouseTextColor = Color(192, 192, 192);


BLGoalMenu::BLGoalMenu(CanvasBase& oParent, BLBot& oBot)
	: m_oCanva(oParent)
	, m_oBot(oBot)
	, m_bVisible(false)
{

}

BLGoalMenu::~BLGoalMenu()
{
}


void BLGoalMenu::ConstructFromCase(const BLSquare& oSquare, int I, int J)
{
	m_aGoals.clear();

	m_iI = I;
	m_iJ = J;

	if (!oSquare.IsBlock())
	{
		IBVector2* pos = new IBVector2("tgt", m_iI, m_iJ, true);
		IBInt* dist = new IBInt("CloseDist", 0, true);
		m_aGoals.push_back(IBGoal("IBFactDef_BotNearPos", pos, dist));
	}

	if (oSquare.GetProp() != NULL && oSquare.IsTempBlock())
	{
		m_aGoals.push_back(IBGoal("IBFactDef_PropIsUnblock", (IBObject*)oSquare.GetProp()));
	}

	if (oSquare.GetProp() != NULL && oSquare.GetProp()->IsPickable())
	{
		m_aGoals.push_back(IBGoal("IBFactDef_BotHasObject", (IBObject*)oSquare.GetProp()));
	}

	if (oSquare.GetProp() == NULL && m_oBot.GetFirstObject() != NULL)
	{
		IBVector2* pPos = new IBVector2("drop pos", m_iI, m_iJ, true);
		m_aGoals.push_back(IBGoal("IBFactDef_ObjectAtPos", m_oBot.GetFirstObject(), pPos));
	}

	if (m_oBot.GetPos() == Vector2(m_iI, m_iJ) && m_oBot.GetFirstObject() != NULL)
	{
		m_aGoals.push_back(IBGoal("IBFactDef_BotIsEmpty"));
	}
}

void BLGoalMenu::SetPos(sint32 x, sint32 y)
{
	int width = 0;
	int height = 0;
	for (uint i=0 ; i<m_aGoals.size() ; ++i)
	{
		int w, h;
		m_oCanva.TextSize(w, h, m_oCanva.GetPrintFont(), s_iTextHeight, "%s %s", m_aGoals[i].GetName().c_str()+10, m_aGoals[i].GetData().c_str());

		height += s_iYL;
		width = max(width, w);
	}
	height = max(height+4, 32);

	m_oCanva.SetPosX((sint16)x);
	m_oCanva.SetPosY((sint16)y);
	m_oCanva.SetWidth(width+4);
	m_oCanva.SetHeight(height);

}

void BLGoalMenu::Click()
{
	if (m_oCanva.IsMouseInside())
	{
		int i = m_oCanva.GetMouseY() / s_iYL;

		if (i>=0 && i<(int)m_aGoals.size())
			m_oBot.AddGoal(m_aGoals[i]);
	}
}


void BLGoalMenu::Update()
{
	/*
	// test
	if (IsVisible())
	{
		m_oBot.AddGoal(GetGoals()[0]);
	}
	*/

}

void BLGoalMenu::Draw() const
{
	m_oCanva.CanvasBase::DrawFillRect(0, 0, m_oCanva.GetWidth()-1, m_oCanva.GetHeight()-1, s_cBackGroundColor);
	m_oCanva.CanvasBase::DrawRect(0, 0, m_oCanva.GetWidth()-1, m_oCanva.GetHeight()-1, s_cForeGroundColor);

	int x=2, y=2;
	for (uint i=0 ; i<m_aGoals.size() ; ++i)
	{
		Color& c = ((m_oCanva.IsMouseInside() && m_oCanva.GetMouseY()>y && m_oCanva.GetMouseY()<y+s_iYL) ? s_cMouseTextColor : s_cNormalTextColor);

		m_oCanva.Print(x, y, m_oCanva.GetPrintFont(), s_iTextHeight, LeftTop, c, "%s %s", m_aGoals[i].GetName().c_str()+10, m_aGoals[i].GetData().c_str());

		y += s_iYL;
	}
}