#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "CanvasBase.h"


class Canvas : public CanvasBase
{
	public:
		Canvas(CanvasBase& oParent, sint32 x, sint32 y, uint16 w, uint16 h);
		Canvas(CanvasBase& oParent);
		virtual ~Canvas();

		sint32							GetPosX() const { return m_iPosX; }
		sint32							GetPosY() const { return m_iPosY; }
		sint32							GetScreenPosX() const { return m_oParent.GetScreenPosX() - m_oParent.GetOrigX() + m_iPosX; }
		sint32							GetScreenPosY() const { return m_oParent.GetScreenPosY() - m_oParent.GetOrigY() + m_iPosY; }

		const CanvasBase&				GetParent() const { return m_oParent; }

		void							SetPosX(sint32 x) { m_iPosX = x; }
		void							SetPosY(sint32 y) { m_iPosY = y; }

		virtual GEngine*				GetGEngine() { return m_oParent.GetGEngine(); }
		virtual const GEngine*			GetGEngine() const { return m_oParent.GetGEngine(); }

		virtual void					DrawImage(const ImageResource& image, sint32 x, sint32 y) const;
		virtual void 					DrawImage(const ImageResource& image, sint32 x, sint32 y, float fAngle, float fZoom) const;
		virtual void 					DrawImage(const ImageResource& image, sint32 x, sint32 y, uint16 w, uint16 h, sint32 sx, sint32 sy, uint16 sw, uint16 sh) const;
		virtual void 					SetPixel(sint32 x, sint32 y, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawRect(sint32 x, sint32 y, sint32 width, sint32 height, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawFillRect(sint32 x, sint32 y, sint32 width, sint32 height, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawCircle(sint32 x, sint32 y, sint32 radius, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawFillCircle(sint32 x, sint32 y, sint32 radius, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawLine(sint32 x1, sint32 y1, sint32 x2, sint32 y2, uint8 r, uint8 g, uint8 b) const;
		virtual void					TextSizeArgs(sint32& w, sint32& h, const char* sFontPath, uint16 size, const char* format, va_list oArgs) const;
		virtual void 					PrintArgs(sint32 x, sint32 y, const char* sFontPath, uint16 size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs) const;

		virtual const char*				GetPrintFont() const;

		virtual sint32					GetMouseX() const;
		virtual sint32					GetMouseY() const;

		virtual ClampingRect			GetClampingRect() const;

	private:
		CanvasBase&						m_oParent;
		sint32							m_iPosX; // position dans le parent
		sint32							m_iPosY; // position dans le parent

};

#endif // __CANVAS_H__

