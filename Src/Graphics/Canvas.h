#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "CanvasBase.h"


class Canvas : public CanvasBase
{
	public:
		Canvas(CanvasBase& oParent, sint16 x, sint16 y, uint16 w, uint16 h);
		Canvas(CanvasBase& oParent);
		~Canvas();

		sint16							GetPosX() const { return m_iPosX; }
		sint16							GetPosY() const { return m_iPosY; }
		sint16							GetScreenPosX() const { return m_oParent.GetScreenPosX() - m_iOrigX + m_iPosX; }
		sint16							GetScreenPosY() const { return m_oParent.GetScreenPosY() - m_iOrigY + m_iPosY; }

		const CanvasBase&				GetParent() const { return m_oParent; }

		void							SetPosX(sint16 x) { m_iPosX = x; }
		void							SetPosY(sint16 y) { m_iPosY = y; }

		GEngine*						GetGEngine() { return m_oParent.GetGEngine(); }
		const GEngine*					GetGEngine() const { return m_oParent.GetGEngine(); }

		virtual void					DrawImage(const ImageResource& image, sint16 x, sint16 y) const;
		virtual void 					DrawImage(const ImageResource& image, sint16 x, sint16 y, float fAngle, float fZoom) const;
		virtual void 					DrawImage(const ImageResource& image, sint16 x, sint16 y, uint16 w, uint16 h, sint16 sx, sint16 sy, uint16 sw, uint16 sh) const;
		virtual void 					SetPixel(sint16 x, sint16 y, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawFillCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b) const;
		virtual void					TextSizeArgs(int& w, int& h, const char* sFontPath, uint size, const char* format, va_list oArgs) const;
		virtual void 					PrintArgs(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs) const;

		virtual const char*				GetPrintFont() const;
		//bool IsMouseOverlapping(sint16 x, sint16 y, uint16 radius);

		sint32							GetMouseX() const;
		sint32							GetMouseY() const;

	protected:
		//void ConvertFrameToGraphic(sint16& x, sint16& y) const;
		//void ConvertFrameToGraphic(sint16& x, sint16& y, uint16& xl, uint16& yl) const;
		//void ConvertGraphicToFrame(sint16& x, sint16& y) const;
		//void ConvertGraphicToFrame(sint16& x, sint16& y, uint16& xl, uint16& yl) const;

	private:
		CanvasBase&						m_oParent;
		sint16							m_iPosX; // position dans le parent
		sint16							m_iPosY; // position dans le parent

};

#endif // __CANVAS_H__

