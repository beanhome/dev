#include "Utils.h"

#include "CanvasBase.h"
#include "GUtils.h"


CanvasBase::CanvasBase(uint16 width, uint16 height)
	: m_iWidth(width)
	, m_iHeight(height)
{
}

CanvasBase::~CanvasBase()
{
}


void CanvasBase::Print(sint16 x, sint16 y, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, ... )
{
	va_list oArgs;
	va_start(oArgs, format);

	PrintArgs(x, y, size, eAlign, r, g, b, format, oArgs);

	va_end(oArgs);
}

void CanvasBase::Print(sint16 x, sint16 y, uint size, ETextAlign eAlign, const Color& oColor, const char* format, ... )
{
	va_list oArgs;
	va_start(oArgs, format);

	PrintArgs(x, y, size, eAlign, oColor.r, oColor.g, oColor.b, format, oArgs);

	va_end(oArgs);
}

/*
bool GCanvasBase::IsMouseOverlapping(sint16 x, sint16 y, uint16 radius)
{
	 //return (m_iMouseX - x) * (m_iMouseX - x) + (m_iMouseY - y) * (m_iMouseY - y) < radius*radius;
}
*/
