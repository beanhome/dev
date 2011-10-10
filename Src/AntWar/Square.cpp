#include "Square.h"

#include "Utils.h"

#ifdef MYDEBUG
#include "Graphic.h"
#endif

Square::Square()
	: m_bIsVisible(false)
	, m_bIsWater(false)
	, m_bIsFood(false)
	, m_iAntPlayer(-1)
	, m_iHillPlayer(-1)
{}

void Square::Init(const char* line, const char* sNext)
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
		m_aDeadAnts.push_back(atoi(sNext));
		break;
	}
}

void Square::NewTurn()
{
	m_bIsFood = false;
	m_iHillPlayer = -1;
	m_iAntPlayer = -1;
}

#ifdef MYDEBUG
void Square::Draw(uint x, uint y, uint w, uint h) const
{
	sint16 xmin = x * gf_pw.GetWidth() / w;
	sint16 ymin = y * gf_pw.GetHeight() / h;
	sint16 width = gf_pw.GetWidth() / w;
	sint16 height = gf_pw.GetHeight() / h;
	sint16 xmax = xmin + width;
	sint16 ymax = ymin + height;

	uint8 r, g, b;

	if (m_bIsWater)
		r = g = b = 10;
	else
		r = g = b = 200;

	if (!m_bIsVisible)
	{
		r /= 2;
		g /= 2;
		b /= 2;
	}

	gf_pw.DrawFillRect(xmin, ymin, width, height, r, g, b);

	if (m_bIsFood)
	{
		r = g = 64;
		b = 255;
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

	if (m_iAntPlayer > -1)
	{
		switch (m_iAntPlayer)
		{
			case 0:	r = 0;		g = 128,	b = 0;		break;
			case 1:	r = 0;		g = 0,		b = 128;	break;
			case 2:	r = 128;	g = 0,		b = 0;		break;
			case 3:	r = 128;	g = 128,	b = 0;		break;
		}

		gf_pw.DrawFillCircle(xmin+width/2, ymin+height/2, width/2-2, r, g, b);
	}

}
#endif




