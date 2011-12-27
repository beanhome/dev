#ifndef __GCANVAS_H__
#define __GCANVAS_H__

#include <map>
#include "InputEvent.h"


class GCanvas
{
	public:
		GCanvas(uint16 xl, uint16 yl);
		//GCanvas(GraphicEngine* ge, sint16 x, sint16 y, uint16 xl, uint16 yl);
		~GCanvas();

		sint16 GetPosX() const { return m_iPosX; }
		sint16 GetPosY() const { return m_iPosY; }
		uint16 GetWidth() const { return m_iWidth; }
		uint16 GetHeight() const { return m_iHeight; }

		void DrawImage(GraphicImage* image, sint16 x, sint16 y, float fAngle, float fZoom) const;

		void DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const;
		void DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, const Color& oColor) const { DrawRect(x, y, width, height, oColor.r, oColor.g, oColor.b); }

		void DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const;
		void DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, const Color& oColor) const { DrawFillRect(x, y, width, height, oColor.r, oColor.g, oColor.b); }

		void DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const;
		void DrawCircle(sint16 x, sint16 y, sint16 radius, const Color& oColor) const { DrawCircle(x, y, radius, oColor.r, oColor.g, oColor.b); }

		void DrawFillCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const;
		void DrawFillCircle(sint16 x, sint16 y, sint16 radius, const Color& oColor) const { DrawFillCircle(x, y, radius, oColor.r, oColor.g, oColor.b); }

		void DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b) const;
		void DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, const Color& oColor) const { DrawLine(x1, x2, y1, y2, oColor.r, oColor.g, oColor.b); }

		void Print( sint16 x, sint16 y, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, ... ) const;

		bool IsMouseOverlapping(sint16 x, sint16 y, uint16 radius);

	protected:
		void ConvertFrameToGraphic(sint16& x, sint16& y) const;
		void ConvertFrameToGraphic(sint16& x, sint16& y, uint16& xl, uint16& yl) const;
		void ConvertGraphicToFrame(sint16& x, sint16& y) const;
		void ConvertGraphicToFrame(sint16& x, sint16& y, uint16& xl, uint16& yl) const;

	private:
		sint16 m_iPosX;
		sint16 m_iPosY;
		uint16 m_iWidth;
		uint16 m_iHeight;
};

#endif // __GCANVAS_H__

