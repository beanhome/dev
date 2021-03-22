#ifndef __CANVASBASE_H__
#define __CANVASBASE_H__

#include <map>
#include "Utils.h"
#include "Color.h"
#include "GUtils.h"

class ImageResource;
class GEngine;

struct ClampingRect
{
	sint32 x,y;
	uint16 w,h;

	ClampingRect(sint32 _x, sint32 _y, uint16 _w, uint16 _h) : x(_x), y(_y), w(_w), h(_h) {}
};

class CanvasBase
{
	public:
		CanvasBase(uint16 xl, uint16 yl);
		CanvasBase(sint32 x, sint32 y, uint16 xl, uint16 yl);
		virtual ~CanvasBase();

		virtual sint32					GetScreenPosX() const { assert(m_iOrigX == 0); return -m_iOrigX; }
		virtual sint32					GetScreenPosY() const { assert(m_iOrigY == 0); return -m_iOrigY; }

		sint32							GetOrigX() const { return m_iOrigX; }
		sint32							GetOrigY() const { return m_iOrigY; }

		uint16							GetWidth() const { return m_iWidth; }
		uint16							GetHeight() const { return m_iHeight; }

		void							SetOrigX(sint32 x) { m_iOrigX = x; }
		void							SetOrigY(sint32 y) { m_iOrigY = y; }

		void							SetWidth(uint16 w) { m_iWidth = w; }
		void							SetHeight(uint16 h) { m_iHeight = h; }

		virtual GEngine*				GetGEngine() = 0;
		virtual const GEngine*			GetGEngine() const = 0;

		virtual void					DrawImage(const ImageResource& image, sint32 x, sint32 y) const = 0;
		virtual void					DrawImage(const ImageResource& image, sint32 x, sint32 y, float fAngle, float fZoom) const = 0;
		virtual void 					DrawImage(const ImageResource& image, sint32 x, sint32 y, sint32 sx, sint32 sy, uint16 sw, uint16 sh) const { DrawImage(image, x, y, sw, sh, sx, sy, sw, sh); }
		virtual void 					DrawImage(const ImageResource& image, sint32 x, sint32 y, uint16 w, uint16 h, sint32 sx, sint32 sy, uint16 sw, uint16 sh) const = 0;

		virtual void					SetPixel(sint32 x, sint32 y, uint8 r, uint8 g, uint8 b) const = 0;
		virtual void					SetPixel(sint32 x, sint32 y, const Color& oColor) const { SetPixel(x, y, oColor.r, oColor.g, oColor.b); }

		virtual void					DrawRect(sint32 x, sint32 y, sint32 width, sint32 height, uint8 r, uint8 g, uint8 b) const = 0;
		virtual void					DrawRect(sint32 x, sint32 y, sint32 width, sint32 height, const Color& oColor) const { DrawRect(x, y, width, height, oColor.r, oColor.g, oColor.b); }

		virtual void					DrawFillRect(sint32 x, sint32 y, sint32 width, sint32 height, uint8 r, uint8 g, uint8 b) const = 0;
		virtual void					DrawFillRect(sint32 x, sint32 y, sint32 width, sint32 height, const Color& oColor) const { DrawFillRect(x, y, width, height, oColor.r, oColor.g, oColor.b); }

		virtual void					DrawCircle(sint32 x, sint32 y, sint32 radius, uint8 r, uint8 g, uint8 b) const = 0;
		virtual void 					DrawCircle(sint32 x, sint32 y, sint32 radius, const Color& oColor) const { DrawCircle(x, y, radius, oColor.r, oColor.g, oColor.b); }

		virtual void					DrawFillCircle(sint32 x, sint32 y, sint32 radius, uint8 r, uint8 g, uint8 b) const = 0;
		virtual void 					DrawFillCircle(sint32 x, sint32 y, sint32 radius, const Color& oColor) const { DrawFillCircle(x, y, radius, oColor.r, oColor.g, oColor.b); }

		virtual void 					DrawLine(sint32 x1, sint32 y1, sint32 x2, sint32 y2, uint8 r, uint8 g, uint8 b) const = 0;
		virtual void 					DrawLine(sint32 x1, sint32 y1, sint32 x2, sint32 y2, const Color& oColor) const { DrawLine(x1, y1, x2, y2, oColor.r, oColor.g, oColor.b); }

		virtual void					TextSizeArgs(sint32& w, sint32& h, const char* sFontPath, uint16 size, const char* format, va_list oArgs) const = 0;
		void							TextSize(sint32& w, sint32& h, const char* sFontPath, uint16 size, const char* format, ...) const;

		virtual void 					PrintArgs(sint32 x, sint32 y, const char* sFontPath, uint16 size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs) const = 0;
		void 							Print(sint32 x, sint32 y, const char* sFontPath, uint16 size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, ... ) const;
		void 							Print(sint32 x, sint32 y, const char* sFontPath, uint16 size, ETextAlign eAlign, const Color& oColor, const char* format, ... ) const;

		void 							SetPrintParameter(sint32 x, sint32 y, const char* sFontPath, uint16 size, ETextAlign eAlign, const Color& oColor);
		void 							SetPrintParameter(sint32 x, sint32 y, const char* sFontPath = NULL, uint16 size = 0, ETextAlign eAlign = Undefined);
		void 							SetPrintPos(sint32 x, sint32 y);
		void 							SetPrintFont(const char* sFontPath, uint16 size = 0);
		void 							SetPrintSize(uint16 size);

		virtual const char*				GetPrintFont() const;

		void 							Print(const char* format, ...) const;

		bool							IsInside(sint32 x, sint32 y) const { return (x>=m_iOrigX && x<m_iOrigX+m_iWidth && y>=m_iOrigY && y<m_iOrigY+m_iHeight); }

		bool							IsMouseInside() const { return IsInside(GetMouseX(), GetMouseY()); }

		virtual sint32					GetMouseX() const = 0;
		virtual sint32					GetMouseY() const = 0;

		virtual ClampingRect			GetClampingRect() const = 0;

	protected:
		sint32							m_iOrigX; // Coord of the top left corner
		sint32							m_iOrigY; // Coord of the top left corner

		uint16							m_iWidth;
		uint16							m_iHeight;


		mutable
		struct PrintParam
		{
			sint32			x;
			sint32			y;
			const char*		sFontPath;
			uint			size;
			ETextAlign		eAlign;
			Color			oColor;

			PrintParam() : x(0), y(0), sFontPath(NULL), size(0), eAlign(LeftTop), oColor(255, 255, 255) {}
		}								m_oPrintParam;
};

#endif // __CANVASBASE_H__

