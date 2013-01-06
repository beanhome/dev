#ifndef __GENGINE_SDL_H__
#define __GENGINE_SDL_H__

#include "Utils.h"
#include "GEngine.h"
#include "ImageResource_SDL.h"
#include "FontResource_SDL.h"

struct SDL_Surface;
struct SDL_Cursor;

class ImageResource;
class FontResource;
class ImageResource_SDL;
class FontResource_SDL;

class GEngine_SDL : public GEngine
{
	public:
		GEngine_SDL(uint16 width, uint16 height, uint16 depth);
		~GEngine_SDL();

		void 							Clear();
		void 							Flip();

		virtual void					DrawImage(const ImageResource& image, sint16 x, sint16 y) const;
		virtual void 					DrawImage(const ImageResource& image, sint16 x, sint16 y, float fAngle, float fZoom) const;
		virtual void 					DrawImage(const ImageResource& image, sint16 x, sint16 y, sint16 sx, sint16 sy, uint16 sw, uint16 sh) const;
		virtual void 					SetPixel(sint16 x, sint16 y, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawFillCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b) const;
		virtual void 					PrintArgs(sint16 x, sint16 y, const char* sFontPath, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs);

		void							SaveEvent();
		bool							PollEvent();
		const InputEvent&				WaitEvent();

		virtual ImageResource* const	GetImageResource(const ImageResource::Desc& oDesc) { return GetResource<ImageResource_SDL>(ImageResource_SDL::Desc(oDesc)); }
		virtual FontResource* const		GetFontResource(const FontResource::Desc& oDesc) { return GetResource<FontResource_SDL>(FontResource_SDL::Desc(oDesc)); }

	protected:
		uint 							Init();
		uint 							Close();

	private:
		SDL_Surface*					m_pScreen;
		SDL_Cursor*						m_pCursor;
};

#endif // __GENGINE_SDL_H__

