#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <map>
#include "InputEvent.h"

//#define FONT_PATH "Fonts/COUR.TTF"
#define FONT_PATH "../../Data/PlanetWar/Fonts/arial.ttf"

struct SDL_Surface;
struct _TTF_Font;

typedef SDL_Surface GraphicImage;
typedef _TTF_Font GraphicFont;

extern class GraphicEngine ge;
extern class GraphicFrame gf_pw;
extern class GraphicFrame gf_dbg;

enum ETextAlign
{
	LeftTop,
	LeftCenter,
	LeftBottom,
	CenterTop,
	Center,
	CenterBottom,
	RightTop,
	RightCenter,
	RightBottom
};

typedef map<uint, GraphicFont*> FontMap;

class GraphicEngine
{
	public:
		GraphicEngine(uint16 width, uint16 height, uint16 depth);
		~GraphicEngine();

		uint Init();
		uint Close();

		uint16 GetWidth() { return m_iWidth; }
		uint16 GetHeight() { return m_iHeight; }

		void Clear();
		void Flip();

		const InputEvent& PollEvent();
		const InputEvent& WaitEvent();

		void SetPixel(sint16 x, sint16 y, uint8 r, uint8 g, uint8 b) const;
		void DrawImage(GraphicImage* image, sint16 x, sint16 y, float fAngle, float fZoom) const;
		void DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const;
		void DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const;
		void DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const;
		void DrawFillCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const;
		void DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b) const;
		void Print(sint16 x, sint16 y, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, ...);
		void Print(sint16 x, sint16 y, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs);
		bool IsMouseOverlapping(sint16 x, sint16 y, uint16 radius) { return (m_iMouseX - x) * (m_iMouseX - x) + (m_iMouseY - y) * (m_iMouseY - y) < radius*radius; }

		GraphicImage* LoadBMP(const char* pFileName) const;
		void FreeImage(GraphicImage* pImage) const;
		GraphicImage* CopyImage(GraphicImage* pImage) const;

	private:
		uint16 m_iWidth;
		uint16 m_iHeight;
		uint16 m_iDepth;
		GraphicImage* m_pScreen;

		InputEvent m_oInpuEvent;

		uint16 m_iMouseX;
		uint16 m_iMouseY;

		FontMap m_aFontMap;
};

class GraphicFrame
{
	public:
		GraphicFrame(GraphicEngine* ge, sint16 x, sint16 y, uint16 xl, uint16 yl);
		~GraphicFrame();

		sint16 GetPosX() const { return m_iPosX; }
		sint16 GetPosY() const { return m_iPosY; }
		uint16 GetWidth() const { return m_iWidth; }
		uint16 GetHeight() const { return m_iHeight; }

		void DrawImage(GraphicImage* image, sint16 x, sint16 y, float fAngle, float fZoom) const;
		void DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const;
		void DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const;
		void DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const;
		void DrawFillCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const;
		void DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b) const;
		void Print(sint16 x, sint16 y, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, ...) const;

		bool IsMouseOverlapping(sint16 x, sint16 y, uint16 radius);

	protected:
		void ConvertFrameToGraphic(sint16& x, sint16& y) const;
		void ConvertFrameToGraphic(sint16& x, sint16& y, uint16& xl, uint16& yl) const;
		void ConvertGraphicToFrame(sint16& x, sint16& y) const;
		void ConvertGraphicToFrame(sint16& x, sint16& y, uint16& xl, uint16& yl) const;

	private:
		GraphicEngine* m_pGraphicEngine;
		sint16 m_iPosX;
		sint16 m_iPosY;
		uint16 m_iWidth;
		uint16 m_iHeight;
		

};

#endif // __GRAPHIC_H__

