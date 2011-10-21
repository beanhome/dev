#include "Ant.h"

#include "Utils.h"
#include "World.h"

#ifdef MYDEBUG
#include "Graphic.h"
#endif


const char* Ant::s_Role[Role_MAX] = {"None", "Explore", "Guard", "Protect", "Loot", "Attack", "Flee" };

Ant::Ant(int x, int y, int iPlayer)
	: m_vLoc(x, y)
	, m_iPlayer(iPlayer)
	, m_eRole(None)
{}

Ant::Ant(Vector2 loc, int iPlayer)
	: m_vLoc(loc)
	, m_iPlayer(iPlayer)
	, m_eRole(None)
{}

void Ant::TestAnts(const World& oWorld)
{
	for (uint i=0 ; i<oWorld.GetAntCount() ; ++i)
	{
		const Ant& oAnt = oWorld.GetAnt(i);
		if (oWorld.DistanceSq(oAnt.GetLocation(), GetLocation()) < oWorld.GetViewRadiusSq())
		{
			if (oAnt.GetPlayer() > 0)
				m_aEnemyAnts.push_back(oAnt.GetLocation());
			else
				m_aAllieAnts.push_back(oAnt.GetLocation());
		}
	}

	if (m_aEnemyAnts.size() > 0)
	{
		m_eRole = (m_aEnemyAnts.size() > m_aAllieAnts.size() ? Flee : Attack);
	}
}




#ifdef MYDEBUG
void Ant::Draw(uint x, uint y, uint w, uint h, int iTurn, bool bSelect) const
{
	sint16 xmin = x * gf_pw.GetWidth() / w;
	sint16 ymin = y * gf_pw.GetHeight() / h;
	sint16 cw = gf_pw.GetWidth() / w;
	sint16 ch = gf_pw.GetHeight() / h;
	sint16 xmax = xmin + cw;
	sint16 ymax = ymin + ch;

	uint8 r = 50;
	uint8 g = 50;
	uint8 b = 50;

	switch (m_iPlayer)
	{
		case 0:	r = 0;		g = 128,	b = 0;		break;
		case 1:	r = 0;		g = 0,		b = 128;	break;
		case 2:	r = 128;	g = 0,		b = 0;		break;
		case 3:	r = 128;	g = 128,	b = 0;		break;
	}

	gf_pw.DrawFillCircle(xmin+cw/2, ymin+ch/2, cw/2-1, r, g, b);


	if (bSelect)
	{
		r = 255; g = 128; b = 50;
	}
	else
	{
		r = 25; g = 200; b = 128;
	}

	if (/*bSelect && */m_oPath.GetLength() > 0)
	{
		int i1 = x;
		int j1 = y;
		int i2 = m_oPath[0].x;
		int j2 = m_oPath[0].y;


		for (int i=0 ; i<m_oPath.GetLength() ; ++i)
		{
			if (i1 == 0 && i2 == w-1)
			{
				{
					sint16 x1 = i1 * gf_pw.GetWidth() / w + cw / 2;
					sint16 y1 = j1 * gf_pw.GetHeight() / h + ch / 2;
					sint16 x2 = 0;
					sint16 y2 = y1;
					gf_pw.DrawLine(x1, y1, x2, y2, r, g, b);
				}

				{
					sint16 x2 = i2 * gf_pw.GetWidth() / w + cw / 2;
					sint16 y2 = j2 * gf_pw.GetHeight() / h + ch / 2;
					sint16 x1 = gf_pw.GetWidth()-1;
					sint16 y1 = y2;
					gf_pw.DrawLine(x1, y1, x2, y2, r, g, b);
				}
			}
			else if (i2 == 0 && i1 == w-1)
			{
				{
					sint16 x1 = i1 * gf_pw.GetWidth() / w + cw / 2;
					sint16 y1 = j1 * gf_pw.GetHeight() / h + ch / 2;
					sint16 x2 = gf_pw.GetWidth()-1;
					sint16 y2 = y1;
					gf_pw.DrawLine(x1, y1, x2, y2, r, g, b);
				}

				{
					sint16 x2 = i2 * gf_pw.GetWidth() / w + cw / 2;
					sint16 y2 = j2 * gf_pw.GetHeight() / h + ch / 2;
					sint16 x1 = 0;
					sint16 y1 = y2;
					gf_pw.DrawLine(x1, y1, x2, y2, r, g, b);
				}
			}
			else if (j1 == 0 && j2 == h-1)
			{
				{
					sint16 x1 = i1 * gf_pw.GetWidth() / w + cw / 2;
					sint16 y1 = j1 * gf_pw.GetHeight() / h + ch / 2;
					sint16 x2 = x1;
					sint16 y2 = 0;
					gf_pw.DrawLine(x1, y1, x2, y2, r, g, b);
				}

				{
					sint16 x2 = i2 * gf_pw.GetWidth() / w + cw / 2;
					sint16 y2 = j2 * gf_pw.GetHeight() / h + ch / 2;
					sint16 x1 = x2;
					sint16 y1 = gf_pw.GetHeight()-1;
					gf_pw.DrawLine(x1, y1, x2, y2, r, g, b);
				}
			}
			else if (j2 == 0 && j1 == h-1)
			{
				{
					sint16 x1 = i1 * gf_pw.GetWidth() / w + cw / 2;
					sint16 y1 = j1 * gf_pw.GetHeight() / h + ch / 2;
					sint16 x2 = x1;
					sint16 y2 = gf_pw.GetHeight()-1;
					gf_pw.DrawLine(x1, y1, x2, y2, r, g, b);
				}

				{
					sint16 x2 = i2 * gf_pw.GetWidth() / w + cw / 2;
					sint16 y2 = j2 * gf_pw.GetHeight() / h + ch / 2;
					sint16 x1 = x2;
					sint16 y1 = 0;
					gf_pw.DrawLine(x1, y1, x2, y2, r, g, b);
				}
			}
			else
			{
				sint16 x1 = i1 * gf_pw.GetWidth() / w + cw / 2;
				sint16 y1 = j1 * gf_pw.GetHeight() / h + ch / 2;
				sint16 x2 = i2 * gf_pw.GetWidth() / w + cw / 2;
				sint16 y2 = j2 * gf_pw.GetHeight() / h + ch / 2;
				gf_pw.DrawLine(x1, y1, x2, y2, r, g, b);
			}

			if (i+1 == m_oPath.GetLength())
				break;

			i1 = i2;
			j1 = j2;
			i2 = m_oPath[i+1].x;
			j2 = m_oPath[i+1].y;
		}
	}
}

void Ant::PrintInfo(sint16& x, sint16& y, sint16 yl) const
{
	gf_dbg.Print(x, y, yl, LeftTop, 255, 255, 255, "Role : %s", s_Role[m_eRole]);
	y += yl;

	/*
	if (m_oPath.GetLength() > 0)
	{
		gf_dbg.Print(x, y, yl, LeftTop, 255, 255, 255, "Path : ");
		y += yl;

		for (int i=0 ; i<m_oPath.GetLength() ; ++i)
		{
			gf_dbg.Print(x, y, yl, LeftTop, 255, 255, 255, "%d %d", m_oPath[i].x, m_oPath[i].y);
			y += yl;
		}
	}
	*/
}

#endif




