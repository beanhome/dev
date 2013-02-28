#include "BLGoalMenu.h"
#include "Map\BLSquare.h"
#include "World\IBVector2.h"
#include "World\BLProp.h"
#include "World\IBInt.h"
#include "BLBot.h"


BLGoalMenu::BLGoalMenu(CanvasBase& oParent, BLBot& oBot)
	: m_oCanva(oParent)
	, m_oBot(oBot)
	, m_bVisible(false)
{

}

BLGoalMenu::~BLGoalMenu()
{
	for (uint i=0 ; i<m_aTempObject.size() ; ++i)
	{
		delete m_aTempObject[i];
	}
}


void BLGoalMenu::ConstructFromCase(const BLSquare& oSquare, int I, int J)
{
	m_aGoals.clear();
	//for (uint i=0 ; i<m_aTempObject.size() ; ++i)
	//{
	//	delete m_aTempObject[i];
	//}
	//m_aTempObject.clear();

	m_iI = I;
	m_iJ = J;

	if (!oSquare.IsBlock())
	{
		IBVector2* pos = new IBVector2(FormatString("pos %d %d", m_iI, m_iJ), m_iI, m_iJ);
		m_aTempObject.push_back(pos);
		IBInt* dist = new IBInt("Dist_0", 0);
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
}

void BLGoalMenu::SetPos(sint32 x, sint32 y)
{
	m_oCanva.SetPosX(x);
	m_oCanva.SetPosY(y);
	m_oCanva.SetWidth(128);
	m_oCanva.SetHeight(min(m_aGoals.size() * 14 + 4, 32));

}

void BLGoalMenu::Click()
{
	int yl = 14;

	if (m_oCanva.IsMouseInside())
	{
		int i = m_oCanva.GetMouseY() / yl;

		if (i>=0 && i<m_aGoals.size())
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
	m_oCanva.DrawFillRect(0, 0, m_oCanva.GetWidth()-1, m_oCanva.GetHeight()-1, 128, 128, 128);
	m_oCanva.DrawRect(0, 0, m_oCanva.GetWidth()-1, m_oCanva.GetHeight()-1, 255, 255, 255);

	Color cNormal(0, 0, 0);
	Color cMouse(192, 192, 192);

	int x=2, y=2;
	int yl = 14;
	for (uint i=0 ; i<m_aGoals.size() ; ++i)
	{
		Color& c = ((m_oCanva.IsMouseInside() && m_oCanva.GetMouseY()>y && m_oCanva.GetMouseY()<y+yl) ? cMouse : cNormal);

		if (m_aGoals[i].GetUserData().size() > 0)
			m_oCanva.Print(x, y, m_oCanva.GetPrintFont(), yl-2, LeftTop, c, "%s %s", m_aGoals[i].GetName().c_str()+10, m_aGoals[i].GetUserData()[0]->GetName().c_str());
		else
			m_oCanva.Print(x, y, m_oCanva.GetPrintFont(), yl-2, LeftTop, c, "%s", m_aGoals[i].GetName().c_str()+10);

		y += yl;
	}
}