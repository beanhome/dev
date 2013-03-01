#include "Utils.h"

#include "CanvasBase.h"
#include "GUtils.h"


CanvasBase::CanvasBase(uint16 width, uint16 height)
	: m_iOrigX(0)
	, m_iOrigY(0)
	, m_iWidth(width)
	, m_iHeight(height)
{
}

CanvasBase::CanvasBase(sint16 x, sint16 y, uint16 width, uint16 height)
	: m_iOrigX(x)
	, m_iOrigY(y)
	, m_iWidth(width)
	, m_iHeight(height)
{
}

CanvasBase::~CanvasBase()
{
}

void CanvasBase::TextSize(int& w, int& h, const char* sFontPath, uint size, const char* format, ...) const
{
	va_list oArgs;
	va_start(oArgs, format);

	TextSizeArgs(w, h, sFontPath, size, format, oArgs);

	va_end(oArgs);
}


void CanvasBase::Print(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, ... ) const
{
	va_list oArgs;
	va_start(oArgs, format);

	PrintArgs(x, y, sFontPath, size, eAlign, r, g, b, format, oArgs);

	va_end(oArgs);
}

void CanvasBase::Print(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, const Color& oColor, const char* format, ... ) const
{
	va_list oArgs;
	va_start(oArgs, format);

	PrintArgs(x, y, sFontPath, size, eAlign, oColor.r, oColor.g, oColor.b, format, oArgs);

	va_end(oArgs);
}

void CanvasBase::SetPrintParameter(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, const Color& oColor)
{
	m_oPrintParam.x = x;
	m_oPrintParam.y = y;
	m_oPrintParam.sFontPath = sFontPath;
	m_oPrintParam.size = size;
	m_oPrintParam.eAlign = eAlign;
	m_oPrintParam.oColor = oColor;
}

void CanvasBase::SetPrintParameter(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign)
{
	m_oPrintParam.x = x;
	m_oPrintParam.y = y;

	if (sFontPath != NULL)
		m_oPrintParam.sFontPath = sFontPath;

	if (size != 0)
		m_oPrintParam.size = size;

	if (eAlign != Undefined)
		m_oPrintParam.eAlign = eAlign;
}

void CanvasBase::SetPrintPos(sint16 x, sint16 y)
{
	m_oPrintParam.x = x;
	m_oPrintParam.y = y;
}

void CanvasBase::SetPrintFont(const char* sFontPath, uint size)
{
	m_oPrintParam.sFontPath = sFontPath;

	if (size != 0)
		m_oPrintParam.size = size;
}

const char* CanvasBase::GetPrintFont() const
{
	return m_oPrintParam.sFontPath;
}

void CanvasBase::SetPrintSize(uint size)
{
	m_oPrintParam.size = size;
}

void CanvasBase::Print(const char* format, ... ) const
{
	va_list oArgs;
	va_start(oArgs, format);

	PrintArgs(m_oPrintParam.x, m_oPrintParam.y, m_oPrintParam.sFontPath, m_oPrintParam.size, m_oPrintParam.eAlign, m_oPrintParam.oColor.r, m_oPrintParam.oColor.g, m_oPrintParam.oColor.b, format, oArgs);

	switch (m_oPrintParam.eAlign)
	{
		case LeftTop:
		case CenterTop:
		case RightTop:

		case LeftCenter:
		case Center:
		case RightCenter:
			m_oPrintParam.y += m_oPrintParam.size;
			break;

		case LeftBottom:
		case CenterBottom:
		case RightBottom:
			m_oPrintParam.y -= m_oPrintParam.size;
			break;
	}

	va_end(oArgs);
}



/*
bool GCanvasBase::IsMouseOverlapping(sint16 x, sint16 y, uint16 radius)
{
	 //return (m_iMouseX - x) * (m_iMouseX - x) + (m_iMouseY - y) * (m_iMouseY - y) < radius*radius;
}
*/
