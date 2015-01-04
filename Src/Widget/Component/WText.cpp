// WText.cpp


#include "GEngine.h"
#include "WText.h"
#include "Image.h"

WText::WText(CanvasBase& oParent, WText::Desc oDesc, sint32 id, const string& sName)
	: Widget(oParent, id, sName)
	, m_oDesc(oDesc)
{
	Init();
}

WText::WText(Widget& oParent, WText::Desc oDesc, sint32 id, const string& sName)
	: Widget(oParent, id, sName)
	, m_oDesc(oDesc)
{
	Init();
}

void WText::Init()
{
}


WText::~WText()
{
}


void WText::Draw() const
{
	sint32 x = 0;
	sint32 y = 0;
	uint16 w = GetWidth();
	uint16 h = GetHeight();

	switch (m_oDesc.eAlign)
	{
		case LeftTop:		x = 0;		y = 0;		break;
		case LeftCenter:	x = 0;		y = h/2;	break;
		case LeftBottom:	x = 0;		y = h;		break;
		case CenterTop:		x = w/2;	y = 0;		break;
		case Center:		x = w/2;	y = h/2;	break;
		case CenterBottom:	x = w/2;	y = h;		break;
		case RightTop:		x = w;		y = 0;		break;
		case RightCenter:	x = w;		y = h/2;	break;
		case RightBottom:	x = w;		y = h;		break;
	}

	for (uint32 i=0 ; i<m_aLine.size() ; ++i)
	{
		Print(x, y+(i*m_oDesc.size), m_oDesc.sFontPath, m_oDesc.size, m_oDesc.eAlign, m_oDesc.r, m_oDesc.g, m_oDesc.b, m_aLine[i].c_str());
	}

	//Print(x, y, m_oDesc.sFontPath, m_oDesc.size, m_oDesc.eAlign, m_oDesc.r, m_oDesc.g, m_oDesc.b, m_oDesc.sText.c_str());

	Widget::Draw();
}

void WText::OnDimensionChanged(SideEnum::Type eSide)
{
	if (eSide == SideEnum::Left || eSide == SideEnum::Right)
		SliceText();
}

void WText::SliceText()
{
	string line;
	sint32 w, h;

	sint32 iLineStart = 0;
	sint32 iLineEnd = 0;
	sint32 i = 0;
	uint16 iWidgetWidth = 0;

	m_aLine.clear();

	if (m_oSide[SideEnum::Left].IsValid() && m_oSide[SideEnum::Right].IsValid())
	{
		ASSERT(m_oSide[SideEnum::Right].GetDimension() - m_oSide[SideEnum::Left].GetDimension() > 0);
		iWidgetWidth = (uint16)(m_oSide[SideEnum::Right].GetDimension() - m_oSide[SideEnum::Left].GetDimension());
	}
	else
	{
		m_aLine.push_back(m_oDesc.sText);
		return;
	}

	char c = m_oDesc.sText[0];

	while(c != 0)
	{
		i = m_oDesc.sText.find_first_of(" \t\n\0", iLineEnd);
		c = (i==-1 ? 0 : m_oDesc.sText[i]);

		line = "";
		line = m_oDesc.sText.substr(iLineStart, i-iLineStart);
		TextSize(w, h, m_oDesc.sFontPath, m_oDesc.size, line.c_str());
		if (w < iWidgetWidth)
		{
			i++;
			iLineEnd = i;
		}
		else
		{
			m_aLine.push_back(m_oDesc.sText.substr(iLineStart, iLineEnd-iLineStart));
			iLineStart = iLineEnd;
			i++;
			iLineEnd = i;
		}

		if (c == 0 || c == '\n')
		{
			m_aLine.push_back(m_oDesc.sText.substr(iLineStart, i-iLineStart-1));
			iLineStart = iLineEnd;
			i++;
			iLineEnd = i;
		}
	}
}

sint32 WText::GetAutoWidth()
{
	sint32 width = 0;

	for (uint32 i=0 ; i<m_aLine.size() ; ++i)
	{
		sint32 w, h;
		TextSize(w, h, m_oDesc.sFontPath, m_oDesc.size, m_aLine[i].c_str());
		width += w;

	}
	return width;
}

sint32 WText::GetAutoHeight()
{
	sint32 height = 0;

	for (uint32 i=0 ; i<m_aLine.size() ; ++i)
	{
		sint32 w, h;
		TextSize(w, h, m_oDesc.sFontPath, m_oDesc.size, m_aLine[i].c_str());
		height += h;

	}
	return height;
}
