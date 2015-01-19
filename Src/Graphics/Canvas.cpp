#include "Utils.h"

#include "Canvas.h"
#include "CanvasBase.h"
#include "GEngine.h"

Canvas::Canvas(CanvasBase& oParent, sint32 x, sint32 y, uint16 w, uint16 h)
	: CanvasBase(w, h)
	, m_oParent(oParent)
	, m_iPosX(x)
	, m_iPosY(y)
{
}

Canvas::Canvas(CanvasBase& oParent)
	: CanvasBase(oParent.GetWidth(), oParent.GetHeight())
	, m_oParent(oParent)
	, m_iPosX(0)
	, m_iPosY(0)
{
}

Canvas::~Canvas()
{

}

void Canvas::DrawImage(const ImageResource& image, sint32 x, sint32 y) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawImage(image, GetScreenPosX() - GetOrigX() + x, GetScreenPosY() - GetOrigY() + y);
	GetGEngine()->ClampClear();
}

void Canvas::DrawImage(const ImageResource& image, sint32 x, sint32 y, float fAngle, float fZoom) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawImage(image, GetScreenPosX() - GetOrigX() + x, GetScreenPosY() - GetOrigY() + y, fAngle, fZoom);
	GetGEngine()->ClampClear();
}

void Canvas::DrawImage(const ImageResource& image, sint32 x, sint32 y, uint16 w, uint16 h, sint32 sx, sint32 sy, uint16 sw, uint16 sh) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawImage(image, GetScreenPosX() - GetOrigX() + x, GetScreenPosY() - GetOrigY() + y, w, h, sx, sy, sw, sh);
	GetGEngine()->ClampClear();
}


void Canvas::SetPixel(sint32 x, sint32 y, uint8 r, uint8 g, uint8 b) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->SetPixel(GetScreenPosX() - GetOrigX() + x, GetScreenPosY() - GetOrigY() + y, r, g, b);
	GetGEngine()->ClampClear();
}

void Canvas::DrawRect(sint32 x, sint32 y, sint32 width, sint32 height, uint8 r, uint8 g, uint8 b) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawRect(GetScreenPosX() - GetOrigX() + x, GetScreenPosY() - GetOrigY() + y, width, height, r, g, b);
	GetGEngine()->ClampClear();
}

void Canvas::DrawFillRect(sint32 x, sint32 y, sint32 width, sint32 height, uint8 r, uint8 g, uint8 b) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawFillRect(GetScreenPosX() - GetOrigX() + x, GetScreenPosY() - GetOrigY() + y, width, height, r, g, b);
	GetGEngine()->ClampClear();
}

void Canvas::DrawCircle(sint32 x, sint32 y, sint32 radius, uint8 r, uint8 g, uint8 b) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawCircle(GetScreenPosX() - GetOrigX() + x, GetScreenPosY() - GetOrigY() + y, radius, r, g, b);
	GetGEngine()->ClampClear();
}

void Canvas::DrawFillCircle(sint32 x, sint32 y, sint32 radius, uint8 r, uint8 g, uint8 b ) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawFillCircle(GetScreenPosX() - GetOrigX() + x, GetScreenPosY() - GetOrigY() + y, radius, r, g, b);
	GetGEngine()->ClampClear();
}

void Canvas::DrawLine(sint32 x1, sint32 y1, sint32 x2, sint32 y2, uint8 r, uint8 g, uint8 b ) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawLine(GetScreenPosX() - GetOrigX() + x1, GetScreenPosY() - GetOrigY() + y1, GetScreenPosX() - GetOrigX() + x2, GetScreenPosY() - GetOrigY() + y2, r, g, b);
	GetGEngine()->ClampClear();
}

void Canvas::TextSizeArgs(sint32& w, sint32& h, const char* sFontPath, uint16 size, const char* format, va_list oArgs) const
{
	GetGEngine()->TextSizeArgs(w, h, sFontPath, size, format, oArgs);
}

void Canvas::PrintArgs(sint32 x, sint32 y, const char* sFontPath, uint16 size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->PrintArgs(GetScreenPosX() - GetOrigX() + x, GetScreenPosY() - GetOrigY() + y, sFontPath, size, eAlign, r, g, b, format, oArgs);
	GetGEngine()->ClampClear();
}

sint32 Canvas::GetMouseX() const
{
	return GetGEngine()->GetMouseX() - GetScreenPosX() + m_iOrigX;
}

sint32 Canvas::GetMouseY() const
{
	return GetGEngine()->GetMouseY() - GetScreenPosY() + m_iOrigX;
}

const char* Canvas::GetPrintFont() const
{
	const char* sPrintFont = CanvasBase::GetPrintFont();
	return (sPrintFont != NULL ? sPrintFont : m_oParent.GetPrintFont());
}

ClampingRect Canvas::GetClampingRect() const
{
	ClampingRect parent = m_oParent.GetClampingRect();

	ClampingRect mine(GetScreenPosX(), GetScreenPosY(), GetWidth(), GetHeight());

	if (mine.x < parent.x)
	{
		mine.w -= (uint16)(parent.x-mine.x);
		mine.x = parent.x;
	}

	if (mine.x > parent.x+parent.w)
	{
		mine.w = 0;
	}

	else if (mine.x + mine.w > parent.x+parent.w)
	{
		mine.w = (uint16)(parent.x + parent.w - mine.x);
	}

	if (mine.y < parent.y)
	{
		mine.h -= (uint16)(parent.y-mine.y);
		mine.y = parent.y;
	}

	if (mine.y > parent.y+parent.h)
	{
		mine.h = 0;
	}

	else if (mine.y + mine.h > parent.y+parent.h)
	{
		mine.h = (uint16)(parent.y + parent.h - mine.y);
	}

	return mine;
}

