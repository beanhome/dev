#include "Hill.h"

#include "Utils.h"

#ifdef MYDEBUG
#include "Graphic.h"
#endif

Hill::Hill(int x, int y, int iPlayer)
	: m_vLoc(x, y)
	, m_iPlayer(iPlayer)
	, m_bUpdated(true)
	, m_bVisible(true)
{}

Hill::Hill(Vector2 loc, int iPlayer)
	: m_vLoc(loc)
	, m_iPlayer(iPlayer)
	, m_bUpdated(true)
	, m_bVisible(true)
{}



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
		case 0:	r = 0;		g = 128,	b = 0;		break;
		case 1:	r = 0;		g = 0,		b = 128;	break;
		case 2:	r = 128;	g = 0,		b = 0;		break;
		case 3:	r = 128;	g = 128,	b = 0;		break;
		case 4:	r = 0;		g = 128,	b = 128;	break;
		case 5:	r = 128;	g = 0,		b = 128;	break;
	}

	gf_pw.DrawFillCircle(xmin+cw/2, ymin+ch/2, cw/2+1, r, g, b);
}

void Hill::PrintInfo(sint16& x, sint16& y, sint16 yl) const
{

}

#endif




