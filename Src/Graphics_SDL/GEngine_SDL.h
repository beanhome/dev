#ifndef __GENGINE_SDL_H__
#define __GENGINE_SDL_H__

#include "Utils.h"
#include "GEngine.h"
#include "ImageResource_SDL.h"
#include "FontResource_SDL.h"

class ImageResource;
class FontResource;
class ImageResource_SDL;
class FontResource_SDL;

class GEngine_SDL : public GEngine
{
	public:
		GEngine_SDL(uint16 width, uint16 height, uint16 depth, const char* rootpath);
		GEngine_SDL(GAppBase* pApp, uint16 width, uint16 height, uint16 depth, const char* rootpath);
		virtual ~GEngine_SDL();

		void 							Clear();
		void 							Flip();

		void							Resize(uint16 w, uint16 h);

		virtual void					DrawImage(const ImageResource& image, sint32 x, sint32 y) const;
		virtual void 					DrawImage(const ImageResource& image, sint32 x, sint32 y, float fAngle, float fZoom) const;
		virtual void 					DrawImage(const ImageResource& image, sint32 x, sint32 y, sint32 sx, sint32 sy, uint16 sw, uint16 sh) const;
		virtual void 					DrawImage(const ImageResource& image, sint32 x, sint32 y, uint16 w, uint16 h, sint32 sx, sint32 sy, uint16 sw, uint16 sh) const;
		virtual void 					SetPixel(sint32 x, sint32 y, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawRect(sint32 x, sint32 y, sint32 width, sint32 height, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawFillRect(sint32 x, sint32 y, sint32 width, sint32 height, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawCircle(sint32 x, sint32 y, sint32 radius, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawFillCircle(sint32 x, sint32 y, sint32 radius, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawLine(sint32 x1, sint32 y1, sint32 x2, sint32 y2, uint8 r, uint8 g, uint8 b) const;
		virtual void					TextSizeArgs(sint32& w, sint32& h, class FontResource* pFont, const char* format, va_list oArgs) const;
		virtual void 					PrintArgs(sint32 x, sint32 y, class FontResource* pFont, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs) const;

		virtual void					ClampClear() const;
		virtual void					ClampRect(sint32 x, sint32 y, uint16 w, uint16 h) const;

		virtual Event*					CreateEvent() const;
		virtual bool					PollEvent(Event* pEvent);
		virtual const Event&			WaitEvent(Event* pEvent);

		virtual ImageResource* const	GetImageResource(const char* path) const { return GetResource<ImageResource_SDL>(ImageResource_SDL::Desc(path)); }
		virtual FontResource* const		GetFontResource(const char* path, uint16 size) const { return GetResource<FontResource_SDL>(FontResource_SDL::Desc(path, size)); }

		struct SDL_Renderer*			GetRenderer();

	protected:
		uint 							Init();
		uint 							Close();

	private:
		struct SDL_Window*				m_pWindow;
		struct SDL_Renderer*			m_pRenderer;
		struct SDL_Surface*				m_pScreen;
		struct SDL_Cursor*				m_pCursor;
};

#endif // __GENGINE_SDL_H__

