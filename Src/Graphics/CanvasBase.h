#ifndef __GCANVASBASE_H__
#define __GCANVASBASE_H__

#include <map>
#include "Utils.h"
#include "Color.h"
#include "GUtils.h"

class ImageResource;
class GEngine;

class CanvasBase
{
	public:
		CanvasBase(uint16 xl, uint16 yl);
		~CanvasBase();

		uint16 GetWidth() const { return m_iWidth; }
		uint16 GetHeight() const { return m_iHeight; }

		virtual GEngine* GetGEngine() = 0;

		virtual void DrawImage(const ImageResource& image, sint16 x, sint16 y) const = 0;
		virtual void DrawImage(const ImageResource& image, sint16 x, sint16 y, float fAngle, float fZoom) const = 0;

		virtual void SetPixel(sint16 x, sint16 y, uint8 r, uint8 g, uint8 b) const = 0;
		void SetPixel(sint16 x, sint16 y, const Color& oColor) const { SetPixel(x, y, oColor.r, oColor.g, oColor.b); }

		virtual void DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const = 0;
		void DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, const Color& oColor) const { DrawRect(x, y, width, height, oColor.r, oColor.g, oColor.b); }

		virtual void DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const = 0;
		void DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, const Color& oColor) const { DrawFillRect(x, y, width, height, oColor.r, oColor.g, oColor.b); }

		virtual void DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const = 0;
		void DrawCircle(sint16 x, sint16 y, sint16 radius, const Color& oColor) const { DrawCircle(x, y, radius, oColor.r, oColor.g, oColor.b); }

		virtual void DrawFillCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const = 0;
		void DrawFillCircle(sint16 x, sint16 y, sint16 radius, const Color& oColor) const { DrawFillCircle(x, y, radius, oColor.r, oColor.g, oColor.b); }

		virtual void DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b) const = 0;
		void DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, const Color& oColor) const { DrawLine(x1, x2, y1, y2, oColor.r, oColor.g, oColor.b); }

		virtual void PrintArgs(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs) = 0;
		void Print(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, ... );
		void Print(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, const Color& oColor, const char* format, ... );

		void SetPrintParameter(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, const Color& oColor);
		void SetPrintParameter(sint16 x, sint16 y, const char* sFontPath = NULL, uint size = 0, ETextAlign eAlign = Undefined);
		void SetPrintPos(sint16 x, sint16 y);
		void SetPrintFont(const char* sFontPath, uint size = 0);
		void SetPrintSize(uint size);

		void Print(const char* format, ...);

		//virtual bool IsMouseOverlapping(sint16 x, sint16 y, uint16 radius);

	protected:
		uint16			m_iWidth;
		uint16			m_iHeight;

		struct PrintParam
		{
			sint16			x;
			sint16			y;
			const char*		sFontPath;
			uint			size;
			ETextAlign		eAlign;
			Color			oColor;

			PrintParam() : x(0), y(0), sFontPath(NULL), size(0), eAlign(Undefined), oColor(255, 255, 255) {}
		}				m_oPrintParam;
};

#endif // __GCANVASBASE_H__
