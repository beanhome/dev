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


void BLGoalMenu::ConstructFromCase(const BLSquare* pSquare, const BLSquare* pSelectSquare)
{
	m_aGoals.clear();

	m_iI = pSquare->GetPos().x;
	m_iJ = pSquare->GetPos().y;

	if (pSelectSquare != NULL && pSelectSquare->GetPos() == m_oBot.GetPos())
	{
		if (pSquare->IsFree())
		{
			//IBVector2* pos = new IBVector2("tgt", m_iI, m_iJ, true);
			IBInt* dist = new IBInt("CloseDist", 0, true);
			m_aGoals.push_back(IBGoal("IBFactDef_BotNearPos", (IBObject*)&pSquare->GetPos(), dist));
		}

		if (pSquare->GetProp() != NULL && pSquare->IsTempBlock())
		{
			m_aGoals.push_back(IBGoal("IBFactDef_PropIsUnblock", (IBObject*)pSquare->GetProp()));
		}

		if (pSquare->GetProp() != NULL && pSquare->GetProp()->IsPickable())
		{
			m_aGoals.push_back(IBGoal("IBFactDef_BotHasObject", (IBObject*)pSquare->GetProp()));
		}

		if (pSquare->IsFree() && m_oBot.GetFirstObject() != NULL)
		{
			m_aGoals.push_back(IBGoal("IBFactDef_ObjectAtPos", m_oBot.GetFirstObject(), (IBObject*)&pSquare->GetPos()));
		}

		if (pSelectSquare == pSquare && m_oBot.GetFirstObject() != NULL)
		{
			m_aGoals.push_back(IBGoal("IBFactDef_BotIsEmpty"));
		}
	}

	if (pSelectSquare != NULL && pSelectSquare == pSquare && pSquare->GetProp() != NULL && pSquare->GetProp()->IsPickable())
	{
		m_aGoals.push_back(IBGoal("IBFactDef_BotHasObject", (IBObject*)pSquare->GetProp()));
	}

	if (pSelectSquare != NULL && pSelectSquare->GetProp() != NULL && !pSquare->IsPermBlock())
	{
		m_aGoals.push_back(IBGoal("IBFactDef_ObjectAtPos", (IBObject*)pSelectSquare->GetProp(), (IBObject*)&pSquare->GetPos()));
	}
}

void BLGoalMenu::UpdatePos()
{
	sint32 x, y;
	int s = m_oBot.GetWorld().GetGridSize();
	int _x = m_oBot.GetWorld().GetCanvas().GetScreenPosX()+m_iI*s;
	int _y = m_oBot.GetWorld().GetCanvas().GetScreenPosY()+m_iJ*s;

	int width = 0;
	int height = 0;
	for (uint i=0 ; i<m_aGoals.size() ; ++i)
	{
		int w, h;
		m_oCanva.TextSize(w, h, m_oCanva.GetPrintFont(), s_iTextHeight, "%s %s", m_aGoals[i].GetName().c_str()+10, m_aGoals[i].GetData().c_str());

		height += s_iYL;
		width = std::max<int>(width, w);
	}
	height = std::max<int>(height+4, 32);
	width += 4;

	x = (_x+s+width > m_oBot.GetWorld().GetCanvas().GetWidth() ? _x-width : _x+s);
	y = (_y+height > m_oBot.GetWorld().GetCanvas().GetHeight() ? _y-height : (_y<0 ? _y+s : _y));

	m_oCanva.SetPosX((sint16)x);
	m_oCanva.SetPosY((sint16)y);
	m_oCanva.SetWidth(width);
	m_oCanva.SetHeight(height);
}

bool BLGoalMenu::Click()
{
	if (m_oCanva.IsMouseInside())
	{
		int i = m_oCanva.GetMouseY() / s_iYL;

		if (i>=0 && i<(int)m_aGoals.size())
		{
			m_oBot.AddGoal(m_aGoals[i]);
			return true;
		}
	}

	return false;
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
	int s = m_oBot.GetWorld().GetGridSize();
	m_oBot.GetWorld().GetCanvas().DrawRect(m_iI*s, m_iJ*s, s-1, s-1, 192, 192, 192);

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
