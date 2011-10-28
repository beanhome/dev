#include "Square.h"

#include "Utils.h"

#ifdef MYDEBUG
#include "Graphic.h"
#endif

Square::Square()
	: m_bIsVisible(false)
	, m_iDiscoveredTurn(-1)
	, m_bIsWater(false)
	, m_bIsFood(false)
	, m_iAntPlayer(-1)
	, m_iHillPlayer(-1)
{}

void Square::Init(const char* line, const char* sNext, int iTurn)
{
	switch (line[0])
	{
		case 'w': // water
			m_bIsWater = true;
			break;

		case 'f': // food
			m_bIsFood = true;
			break;

		case 'h': // hill
			ASSERT(sNext != NULL);
			m_iHillPlayer = atoi(sNext);
			break;

		case 'a': // live ant
			ASSERT(sNext != NULL);
			m_iAntPlayer = atoi(sNext);
			break;

		case 'd': // dead ant
			ASSERT(sNext != NULL);
			if (m_aDeadAnts.size() == 0 || m_aDeadAnts[m_aDeadAnts.size()-1].m_iTurn < iTurn)
				m_aDeadAnts.push_back(DeadAnt(iTurn, atoi(sNext)));
			break;
	}
}

void Square::NewTurn()
{
	m_bIsFood = false;
	m_iHillPlayer = -1;
	m_iAntPlayer = -1;
	m_bIsVisible = false;
	m_iAntInfluence = s_iNoInfluence;
}

void Square::AddInfluence(int iVal)
{
	if (m_iAntInfluence == s_iNoInfluence)
	{
		m_iAntInfluence = iVal;
	}
	else
	{
		m_iAntInfluence += iVal;
	}
}

int Square::GetBadInfluenceFor(int iPlayer) // TODO -> const
{
	int iInfluence = 0;
	for (map<int, int>::iterator it = m_aBadInfluence.begin() ; it != m_aBadInfluence.end() ; ++it)
	{
		if (iPlayer != it->first)
			iInfluence += it->second;
	}

	return iInfluence;
}


#ifdef MYDEBUG
void Square::Draw(uint x, uint y, uint w, uint h, int iTurn, bool bSelect, DrawMode mode) const
{
	sint16 xmin = x * gf_pw.GetWidth() / w;
	sint16 ymin = y * gf_pw.GetHeight() / h;
	sint16 width = gf_pw.GetWidth() / w;
	sint16 height = gf_pw.GetHeight() / h;
	sint16 xmax = xmin + width;
	sint16 ymax = ymin + height;

	Color oUndiscoverd(50, 50, 50);
	Color oGroundVisible(200, 200, 200);
	Color oGroundUnvisible(100, 100, 100);
	Color oWaterVisible(50, 50, 200);
	Color oWaterUnvisible(25, 25, 100);
	Color oFood(255, 255, 64);

	if (mode == EDM_Influence && m_iAntInfluence != s_iNoInfluence)
	{
		int offset = (abs(m_iAntInfluence)+1) * 30;

		oGroundVisible.r = (m_iAntInfluence >= 0 ? oGroundVisible.r - offset : oGroundVisible.r);
		oGroundVisible.g = (m_iAntInfluence <= 0 ? oGroundVisible.g - offset : oGroundVisible.g);
		oGroundVisible.b = oGroundVisible.b - offset;
	}

	Color oColor(255, 255, 255);
	if (IsDiscovered(iTurn))
	{
		if (IsWater())
		{
			oColor = (IsVisible() ? oWaterVisible : oWaterUnvisible);
		}
		else
		{
			oColor = (IsVisible() ? oGroundVisible : oGroundUnvisible);
		}
	}
	else
	{
		oColor = oUndiscoverd;
	}

	gf_pw.DrawFillRect(xmin, ymin, width +1, height +1, oColor);
	if (bSelect)
		gf_pw.DrawRect(xmin, ymin, width, height, 0, 0, 0);

	if (IsDiscovered(iTurn) && m_bIsFood)
	{
		gf_pw.DrawFillRect(xmin+1, ymin+1, width-2, height-2, oFood);
	}

	if (m_aDeadAnts.size() > 0)
	{
		for (uint i=0 ; i<m_aDeadAnts.size() ; ++i)
		{
			if (m_aDeadAnts[i].m_iTurn == iTurn)
			{
				gf_pw.DrawLine(xmin+1, ymin+1, xmax-1, ymax-1, 50, 50, 50);
				gf_pw.DrawLine(xmin+1, ymax-1, xmax-1, ymin+1, 50, 50, 50);
			}
		}
	}
}

void Square::PrintInfo(sint16& x, sint16& y, sint16 yl, int iTurn) const
{
	if (m_iDiscoveredTurn > -1)
		gf_dbg.Print(x, y, yl, LeftTop, 0, 0, 0, "Discovered turn %d", m_iDiscoveredTurn);
	else
		gf_dbg.Print(x, y, yl, LeftTop, 0, 0, 0, "Not discovered");
	y += yl;

	gf_dbg.Print(x, y, yl, LeftTop, 0, 0, 0, (m_bIsVisible ? "Visible" : "Not visible"));
	y += yl;

	if (m_bIsWater)
	{
		gf_dbg.Print(x, y, yl, LeftTop, 0, 0, 0, "Water");
		y += yl;
	}

	if (m_bIsFood)
	{
		gf_dbg.Print(x, y, yl, LeftTop, 0, 0, 0, "Food");
		y += yl;
	}

	if (m_iAntInfluence != s_iNoInfluence)
	{
		gf_dbg.Print(x, y, yl, LeftTop, 0, 0, 0, "Influence of %d", m_iAntInfluence);
		y += yl;
	}

	if (m_iAntPlayer > -1)
	{
		gf_dbg.Print(x, y, yl, LeftTop, 0, 0, 0, "Ant of %d", m_iAntPlayer);
		y += yl;
	}

	if (m_iHillPlayer > -1)
	{
		gf_dbg.Print(x, y, yl, LeftTop, 0, 0, 0, "Hill of %d", m_iHillPlayer);
		y += yl;
	}

	if (m_aDeadAnts.size() > 0)
	{
		for (uint i=0 ; i<m_aDeadAnts.size() ; ++i)
		{
			if (m_aDeadAnts[i].m_iTurn <= iTurn)
			{
				gf_dbg.Print(x, y, yl, LeftTop, 0, 0, 0, "Dead Ant of %d (%d)", m_aDeadAnts[i].m_iPlayer, m_aDeadAnts[i].m_iTurn);
				y += yl;
			}
		}
	}
}


#endif




