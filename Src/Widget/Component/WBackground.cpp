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
	m_pImageResource = GetGEngine()->GetImageResource(m_oDesc.sPath);
}

WBackground::~WBackground()
{
}

void WBackground::Draw() const
{
	uint16 w = m_pImageResource->GetWidth();
	uint16 h = m_pImageResource->GetHeight();

	if (w>0 && h>0)
	{
		for (uint16 i=0 ; i<GetWidth()/w+2 ; ++i)
		{
			for (uint16 j=0 ; j<GetHeight()/h+2 ; ++j)
			{
				DrawImage(*m_pImageResource, i*w, j*h, w, h, 0, 0, w, h);
			}
		}
	}

	Widget::Draw();
}
