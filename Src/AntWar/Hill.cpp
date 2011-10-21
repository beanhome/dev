#include "Hill.h"

#include "Utils.h"

#ifdef MYDEBUG
#include "Graphic.h"
#endif

Hill::Hill(const Vector2& loc, int iPlayer, const Grid& oGrid)
	: m_vLoc(loc)
	, m_iPlayer(iPlayer)
	, m_bUpdated(true)
	, m_bVisible(true)
	, m_oGrid(oGrid)
{
	m_oDefense.Create(m_oGrid, true);
}

void Hill::Init(int iTurn)
{
	vector<Vector2> pos(1, GetLocation());
	m_oDefense.Explore(pos, NavDijkstra::Undiscovered, iTurn);

	m_aDefenseCount.clear();
	m_aDefenseCount.reserve(m_oDefense.GetGrid().GetWidth() + m_oDefense.GetGrid().GetHeight());
	for (uint x=0 ; x<m_oDefense.GetGrid().GetWidth() ; ++x)
	{
		for (uint y=0 ; y<m_oDefense.GetGrid().GetHeight() ; ++y)
		{
			int iCount = m_oDefense.GetGrid()[x][y].iCount;
			if (iCount >= 0)
			{
				if (iCount >= (int)m_aDefenseCount.size())
					m_aDefenseCount.resize(iCount+1);

				m_aDefenseCount[iCount].push_back(Vector2(x,y));
			}
		}
	}

	uint iMinDistCount = (uint)-1;
	for (uint i=3 ; i<m_aDefenseCount.size() ; ++i)
	{
		if (iMinDistCount == (uint)-1 || iMinDistCount > m_aDefenseCount[i].size())
		{
			m_iBestDistDefense = i;
			iMinDistCount = m_aDefenseCount[m_iBestDistDefense].size();
		}
	}

	m_oDefense.PrintDebug();

	LOG("Best Dist Defense : %d", m_iBestDistDefense);
}


#ifdef MYDEBUG
void Hill::Draw(uint x, uint y, uint w, uint h, int iTurn, bool bSelect) const
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
		case 0:	r = 0;		g = 192,	b = 0;		break;
		case 1:	r = 0;		g = 0,		b = 192;	break;
		case 2:	r = 192;	g = 0,		b = 0;		break;
		case 3:	r = 192;	g = 192,	b = 0;		break;
		case 4:	r = 0;		g = 192,	b = 192;	break;
		case 5:	r = 192;	g = 0,		b = 192;	break;
	}

	gf_pw.DrawFillCircle(xmin+cw/2, ymin+ch/2, cw/2+1, r, g, b);
}

void Hill::PrintInfo(sint16& x, sint16& y, sint16 yl) const
{

}

#endif




