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
	m_pFont = GetGEngine()->GetFontResource(FontResource::Desc(m_oDesc.sFontPath, m_oDesc.size));
}


WText::~WText()
{
}


void WText::Draw() const
{
	sint32 x = 0;
	sint32 y = 0;
	sint32 yo = 0;
	uint16 w = GetWidth();
	uint16 h = GetHeight();
	uint16 lh = m_pFont->GetSize();
	uint16 th = m_pFont->GetLineSkip()*(m_aDrawLine.size()-1) + m_pFont->GetSize();

	//GetParent().DrawRect(GetPosX(), GetPosY(), m_iWidth-1, m_iHeight-1, 192, 128, 128);

	ETextAlign eAlign;

	switch (m_oDesc.eAlign)
	{
		case LeftTop:		x = 0;		y = 0;			yo = 0;		eAlign = LeftTop;	break;
		case LeftCenter:	x = 0;		y = (h-th)/2;	yo = -lh/2;	eAlign = LeftTop;	break;
		case LeftBottom:	x = 0;		y = h - th;		yo = -lh;	eAlign = LeftTop;	break;
		case CenterTop:		x = w/2;	y = 0;			yo = 0;		eAlign = CenterTop;	break;
		case Center:		x = w/2;	y = (h-th)/2;	yo = -lh/2;	eAlign = CenterTop;	break;
		case CenterBottom:	x = w/2;	y = h - th;		yo = -lh;	eAlign = CenterTop;	break;
		case RightTop:		x = w;		y = 0;			yo = 0;		eAlign = RightTop;	break;
		case RightCenter:	x = w;		y = (h-th)/2;	yo = -lh/2;	eAlign = RightTop;	break;
		case RightBottom:	x = w;		y = h - th;		yo = -lh;	eAlign = RightTop;	break;
	}

	for (uint32 i=0 ; i<m_aDrawLine.size() ; ++i)
	{
		sint32 ly = y+(i*m_pFont->GetLineSkip());
		Print(x, ly, m_oDesc.sFontPath, m_oDesc.size, eAlign, m_oDesc.r, m_oDesc.g, m_oDesc.b, m_aDrawLine[i].c_str());
	}

	//Print(x, y, m_oDesc.sFontPath, m_oDesc.size, m_oDesc.eAlign, m_oDesc.r, m_oDesc.g, m_oDesc.b, m_oDesc.sText.c_str());

	Widget::Draw();
}

void WText::OnDimensionChanged(SideEnum::Type eSide)
{
	if (eSide == SideEnum::Left || eSide == SideEnum::Right)
		SliceText();
}


void WText::OnTextChanged()
{
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

	if (c == 0)
	{
		m_aLine.push_back("");
		return;
	}

	while(c != 0)
	{
		i = m_oDesc.sText.find_first_of(" \t\n\0", iLineEnd);
		if (i == -1)
		{
			c = 0;
			i = m_oDesc.sText.length();
		}
		else
		{
			c = m_oDesc.sText[i];
		}
		
		line = "";
		line = m_oDesc.sText.substr(iLineStart, i-iLineStart - (c==0?1:0));
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
		}

		if (c == 0 || c == '\n')
		{
			m_aLine.push_back(m_oDesc.sText.substr(iLineStart, i-iLineStart - (c==0?1:0)));
			iLineStart = iLineEnd;
			iLineEnd = i;
		}
	}

	m_aDrawLine.resize(m_aLine.size());
	for (uint32 i=0 ; i<m_aLine.size() ; ++i)
	{
		m_aDrawLine[i] = m_aLine[i];
		while (m_aDrawLine[i].length() > 0 && m_aDrawLine[i][m_aDrawLine[i].length()-1] == '\n')
			m_aDrawLine[i].erase(m_aDrawLine[i].length()-1, 1);
	}
}

sint32 WText::GetAutoWidth()
{
	sint32 width = 0;

	for (uint32 i=0 ; i<m_aDrawLine.size() ; ++i)
	{
		sint32 w, h;
		TextSize(w, h, m_oDesc.sFontPath, m_oDesc.size, m_aDrawLine[i].c_str());
		width = std::max<sint32>(width, w);

	}
	return width;
}

sint32 WText::GetAutoHeight()
{
	sint32 height = 0;

	for (uint32 i=0 ; i<m_aDrawLine.size() ; ++i)
	{
		sint32 w, h;
		TextSize(w, h, m_oDesc.sFontPath, m_oDesc.size, m_aDrawLine[i].c_str());
		height += h;

	}
	return height;
}
