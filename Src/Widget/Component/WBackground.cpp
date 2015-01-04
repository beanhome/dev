// WBackground.cpp

#include "WBackground.h"
#include "GEngine.h"

WBackground::WBackground(CanvasBase& oParent, const Desc& oDesc, sint32 id, const string& sName)
: Widget(oParent, id, sName)
, m_oDesc(oDesc)
{
	Init();
}

WBackground::WBackground(Widget& oParent, const Desc& oDesc, sint32 id, const string& sName)
: Widget(oParent, id, sName)
, m_oDesc(oDesc)
{
	Init();
}

void WBackground::Init()
{
	string sPath= FormatString("%s%s", DATA_DIR, m_oDesc.sPath);
	m_pImageResource = GetGEngine()->GetImageResource(sPath.c_str());
}

WBackground::~WBackground()
{
}

void WBackground::Draw() const
{
	uint16 w = m_pImageResource->GetWidth();
	uint16 h = m_pImageResource->GetHeight();

	for (uint16 i=0 ; i<GetWidth()/w+2 ; ++i)
	{
		for (uint16 j=0 ; j<GetHeight()/h+2 ; ++j)
		{
			DrawImage(*m_pImageResource, i*w + w/2, j*h + h/2, w, h, 0, 0, w, h);
		}
	}

	Widget::Draw();
}
