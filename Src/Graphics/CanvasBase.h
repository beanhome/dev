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
	sint16 x,y;
	uint16 w,h;

	ClampingRect(sint16 _x, sint16 _y, uint16 _w, uint16 _h) : x(_x), y(_y), w(_w), h(_h) {}
};

class CanvasBase
{
	public:
		CanvasBase(uint16 xl, uint16 yl);
		CanvasBase(sint16 x, sint16 y, uint16 xl, uint16 yl);
		virtual ~CanvasBase();

		virtual sint16					GetScreenPosX() const { return -m_iOrigX; }
		virtual sint16					GetScreenPosY() const { return -m_iOrigY; }

		sint16							GetOrigX() const { return m_iOrigX; }
		sint16							GetOrigY() const { return m_iOrigY; }

		uint16							GetWidth() const { return m_iWidth; }
		uint16							GetHeight() const { return m_iHeight; }

		void							SetOrigX(sint16 x) { m_iOrigX = x; }
		void							SetOrigY(sint16 y) { m_iOrigY = y; }

		void							SetWidth(uint16 w) { m_iWidth = w; }
		void							SetHeight(uint16 h) { m_iHeight = h; }

		virtual GEngine*				GetGEngine() = 0;
		virtual const GEngine*			GetGEngine() const = 0;

		virtual void					DrawImage(const ImageResource& image, sint16 x, sint16 y) const = 0;
		virtual void					DrawImage(const ImageResource& image, sint16 x, sint16 y, float fAngle, float fZoom) const = 0;
		virtual void 					DrawImage(const ImageResource& image, sint16 x, sint16 y, sint16 sx, sint16 sy, uint16 sw, uint16 sh) const { DrawImage(image, x, y, sw, sh, sx, sy, sw, sh); }
		virtual void 					DrawImage(const ImageResource& image, sint16 x, sint16 y, uint16 w, uint16 h, sint16 sx, sint16 sy, uint16 sw, uint16 sh) const = 0;

		virtual void					SetPixel(sint16 x, sint16 y, uint8 r, uint8 g, uint8 b) const = 0;
		void							SetPixel(sint16 x, sint16 y, const Color& oColor) const { SetPixel(x, y, oColor.r, oColor.g, oColor.b); }

		virtual void					DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const = 0;
		void							DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, const Color& oColor) const { DrawRect(x, y, width, height, oColor.r, oColor.g, oColor.b); }

		virtual void					DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const = 0;
		void							DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, const Color& oColor) const { DrawFillRect(x, y, width, height, oColor.r, oColor.g, oColor.b); }

		virtual void					DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const = 0;
		void 							DrawCircle(sint16 x, sint16 y, sint16 radius, const Color& oColor) const { DrawCircle(x, y, radius, oColor.r, oColor.g, oColor.b); }

		virtual void					DrawFillCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const = 0;
		void 							DrawFillCircle(sint16 x, sint16 y, sint16 radius, const Color& oColor) const { DrawFillCircle(x, y, radius, oColor.r, oColor.g, oColor.b); }

		virtual void 					DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b) const = 0;
		void 							DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, const Color& oColor) const { DrawLine(x1, y1, x2, y2, oColor.r, oColor.g, oColor.b); }

		virtual void					TextSizeArgs(int& w, int& h, const char* sFontPath, uint size, const char* format, va_list oArgs) const = 0;
		void							TextSize(int& w, int& h, const char* sFontPath, uint size, const char* format, ...) const;

		virtual void 					PrintArgs(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs) const = 0;
		void 							Print(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, ... ) const;
		void 							Print(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, const Color& oColor, const char* format, ... ) const;

		void 							SetPrintParameter(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, const Color& oColor);
		void 							SetPrintParameter(sint16 x, sint16 y, const char* sFontPath = NULL, uint size = 0, ETextAlign eAlign = Undefined);
		void 							SetPrintPos(sint16 x, sint16 y);
		void 							SetPrintFont(const char* sFontPath, uint size = 0);
		void 							SetPrintSize(uint size);

		virtual const char*				GetPrintFont() const;

		void 							Print(const char* format, ...) const;

		bool							IsInside(sint32 x, sint32 y) const { return (x>=m_iOrigX && x<m_iOrigX+m_iWidth && y>=m_iOrigY && y<m_iOrigY+m_iHeight); }

		bool							IsMouseInside() const { return IsInside(GetMouseX(), GetMouseY()); }


		//virtual bool IsMouseOverlapping(sint16 x, sint16 y, uint16 radius);

		virtual sint32					GetMouseX() const = 0;
		virtual sint32					GetMouseY() const = 0;

		virtual ClampingRect			GetClampingRect() const = 0;

	protected:
		sint16							m_iOrigX; // position du Canva par rapport à l'origine
		sint16							m_iOrigY; // position du Canva par rapport à l'origine

		uint16							m_iWidth;
		uint16							m_iHeight;


		mutable
		struct PrintParam
		{
			sint16			x;
			sint16			y;
			const char*		sFontPath;
			uint			size;
			ETextAlign		eAlign;
			Color			oColor;

			PrintParam() : x(0), y(0), sFontPath(NULL), size(0), eAlign(LeftTop), oColor(255, 255, 255) {}
		}								m_oPrintParam;
};

#endif // __CANVASBASE_H__

