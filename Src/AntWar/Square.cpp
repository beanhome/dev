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
}

#ifdef MYDEBUG
void Square::Draw(uint x, uint y, uint w, uint h, int iTurn, bool bSelect) const
{
	sint16 xmin = x * gf_pw.GetWidth() / w;
	sint16 ymin = y * gf_pw.GetHeight() / h;
	sint16 width = gf_pw.GetWidth() / w;
	sint16 height = gf_pw.GetHeight() / h;
	sint16 xmax = xmin + width;
	sint16 ymax = ymin + height;

	uint8 r = 50;
	uint8 g = 50;
	uint8 b = 50;

	if (IsDiscovered(iTurn))
	{
		if (m_bIsWater)
			b = 200;
		else
			r = g = b = 200;

		if (!m_bIsVisible)
		{
			r /= 2;
			g /= 2;
			b /= 2;
		}
	}

	gf_pw.DrawFillRect(xmin, ymin, width +1, height +1, r, g, b);
	if (bSelect)
		gf_pw.DrawRect(xmin, ymin, width, height, 0, 0, 0);

	if (IsDiscovered(iTurn) && m_bIsFood)
	{
		r = g = 255;
		b = 64;
		gf_pw.DrawFillRect(xmin+1, ymin+1, width-2, height-2, r, g, b);
	}

	if (m_iHillPlayer > -1)
	{
		switch (m_iHillPlayer)
		{
			case 0:	r = 0;		g = 255,	b = 0;		break;
			case 1:	r = 0;		g = 0,		b = 255;	break;
			case 2:	r = 255;	g = 0,		b = 0;		break;
			case 3:	r = 255;	g = 255,	b = 0;		break;
		}

		gf_pw.DrawFillCircle(xmin+width/2, ymin+height/2, width/2+1, r, g, b);
	}

	// Ant Draw self
	/*
	if (IsDiscovered(iTurn) && m_iAntPlayer > -1)
	{
		switch (m_iAntPlayer)
		{
			case 0:	r = 0;		g = 128,	b = 0;		break;
			case 1:	r = 0;		g = 0,		b = 128;	break;
			case 2:	r = 128;	g = 0,		b = 0;		break;
			case 3:	r = 128;	g = 128,	b = 0;		break;
		}

		gf_pw.DrawFillCircle(xmin+width/2, ymin+height/2, width/2-1, r, g, b);
	}
	*/

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
				gf_dbg.Print(x, y+10, yl, LeftTop, 0, 0, 0, "Dead Ant of %d (%d)", m_aDeadAnts[i].m_iPlayer, m_aDeadAnts[i].m_iTurn);
				y += yl;
			}
		}
	}
}

#endif




