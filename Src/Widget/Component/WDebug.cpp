// WDebug.cpp

#include "WDebug.h"

Color WDebug::s_oStateColor[] =
{
	Color(128, 128, 128), // Unknown
	Color(0,   0,   255), // Process
	Color(255, 255, 255), // Valid
	Color(255, 0,   0)    // Invalid
};

WDebug::WDebug(CanvasBase& oParent, const Desc& , sint32 id, const string& sName)
: Widget(oParent, id, sName)
{
}

WDebug::WDebug(Widget& oParent, const Desc& , sint32 id, const string& sName)
: Widget(oParent, id, sName)
{
}

WDebug::~WDebug()
{
}

void WDebug::Draw() const
{
	Widget::Draw();

	GetParent().DrawRect(GetPosX(), GetPosY(), m_iWidth-1, m_iHeight-1, s_oStateColor[m_eDimState].r, s_oStateColor[m_eDimState].g, s_oStateColor[m_eDimState].b);
	GetParent().Print(GetPosX()+2, GetPosY()+2, GetPrintFont(), 15, LeftTop, 196, 128, 128, m_sName.c_str());

	//DrawRect(0, 0, m_iWidth-1, m_iHeight-1, s_oStateColor[m_eDimState].r, s_oStateColor[m_eDimState].g, s_oStateColor[m_eDimState].b);
	//Print(2, 2, GetPrintFont(), 15, LeftTop, 0, 0, 0, m_sName.c_str());
}
