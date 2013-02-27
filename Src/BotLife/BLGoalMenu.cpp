#include "BLGoalMenu.h"
#include "Map\BLSquare.h"
#include "World\IBVector2.h"
#include "World\BLProp.h"
#include "World\IBInt.h"


BLGoalMenu::BLGoalMenu(CanvasBase& oParent)
	: m_oCanva(oParent)
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
	static int c = 1;

	m_aGoals.clear();
	//for (uint i=0 ; i<m_aTempObject.size() ; ++i)
	//{
	//	delete m_aTempObject[i];
	//}
	//m_aTempObject.clear();

	if (!oSquare.IsBlock())
	{
		IBVector2* pos = new IBVector2(FormatString("pos %d", c++), I, J);
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
	m_oCanva.SetWidth(100);
	m_oCanva.SetHeight(100);

}

void BLGoalMenu::Update()
{
	m_oCanva.CanvasBase::SetPrintParameter(2, 2, m_oCanva.GetParent().GetPrintFont(), 12, LeftTop, Color(0, 0, 0));

}

void BLGoalMenu::Draw() const
{
	m_oCanva.DrawFillRect(0, 0, m_oCanva.GetWidth()-1, m_oCanva.GetHeight()-1, 128, 128, 128);
	m_oCanva.DrawRect(0, 0, m_oCanva.GetWidth()-1, m_oCanva.GetHeight()-1, 255, 255, 255);
	for (uint i=0 ; i<m_aGoals.size() ; ++i)
	{
		if (m_aGoals[i].GetUserData().size() > 0)
			m_oCanva.Print("%s %s", m_aGoals[i].GetName().c_str()+10, m_aGoals[i].GetUserData()[0]->GetName().c_str());
		else
			m_oCanva.Print("%s", m_aGoals[i].GetName().c_str()+10);
	}
}
