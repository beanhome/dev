#include "Utils.h"

#include "Canvas.h"
#include "CanvasBase.h"
#include "GEngine.h"

Canvas::Canvas(CanvasBase& oParent, sint16 x, sint16 y, uint16 w, uint16 h)
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

void Canvas::DrawImage(const ImageResource& image, sint16 x, sint16 y) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawImage(image, GetScreenPosX() + x, GetScreenPosY() + y);
}

void Canvas::DrawImage(const ImageResource& image, sint16 x, sint16 y, float fAngle, float fZoom) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawImage(image, GetScreenPosX() + x, GetScreenPosY() + y, fAngle, fZoom);
}

void Canvas::DrawImage(const ImageResource& image, sint16 x, sint16 y, uint16 w, uint16 h, sint16 sx, sint16 sy, uint16 sw, uint16 sh) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawImage(image, GetScreenPosX() + x, GetScreenPosY() + y, w, h, sx, sy, sw, sh);
}


void Canvas::SetPixel(sint16 x, sint16 y, uint8 r, uint8 g, uint8 b) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->SetPixel(GetScreenPosX() + x, GetScreenPosY() + y, r, g, b);
}

void Canvas::DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawRect(GetScreenPosX() + x, GetScreenPosY() + y, width, height, r, g, b);
}

void Canvas::DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawFillRect(GetScreenPosX() + x, GetScreenPosY() + y, width, height, r, g, b);
}

void Canvas::DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawCircle(GetScreenPosX() + x, GetScreenPosY() + y, radius, r, g, b);
}

void Canvas::DrawFillCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b ) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawFillCircle(GetScreenPosX() + x, GetScreenPosY() + y, radius, r, g, b);
}

void Canvas::DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b ) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->DrawLine(GetScreenPosX() + x1, GetScreenPosY() + y1, GetScreenPosX() + x2, GetScreenPosY() + y2, r, g, b);
}

void Canvas::PrintArgs(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs) const
{
	GetGEngine()->ClampCanvas(*this);
	GetGEngine()->PrintArgs(GetScreenPosX() + x, GetScreenPosY() + y, sFontPath, size, eAlign, r, g, b, format, oArgs);
}

sint32 Canvas::GetMouseX() const
{
	return GetGEngine()->GetMouseX() - GetScreenPosX();
}

sint32 Canvas::GetMouseY() const
{
	return GetGEngine()->GetMouseY() - GetScreenPosY();
}

const char* Canvas::GetPrintFont() const
{
	const char* sPrintFont = CanvasBase::GetPrintFont();
	return (sPrintFont != NULL ? sPrintFont : m_oParent.GetPrintFont());
}



#if 0
bool Canvas::IsMouseOverlapping(sint16 x, sint16 y, uint16 radius)
{
	ConvertFrameToGraphic(x, y);
	return m_pCanvas->IsMouseOverlapping(x, y, radius);
}

void Canvas::ConvertFrameToGraphic(sint16& x, sint16& y) const
{
	x = m_iPosX + x;
	y = m_iPosY + y;
}

void Canvas::ConvertFrameToGraphic(sint16& x, sint16& y, uint16& /*xl*/, uint16& /*yl*/) const
{
	x = m_iPosX + x;
	y = m_iPosY + y;
}

void Canvas::ConvertGraphicToFrame(sint16& x, sint16& y) const
{
	x = x - m_iPosX;
	y = x - m_iPosY;
}

void Canvas::ConvertGraphicToFrame(sint16& x, sint16& y, uint16& /*xl*/, uint16& /*yl*/) const
{
	x = x - m_iPosX;
	y = x - m_iPosY;
}
#endif
