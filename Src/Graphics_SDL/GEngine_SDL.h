#ifndef __GENGINE_SDL_H__
#define __GENGINE_SDL_H__

#include "Utils.h"
#include "GEngine.h"

struct SDL_Surface;

class ImageResource;

class GEngine_SDL : public GEngine
{
	public:
		GEngine_SDL(uint16 width, uint16 height, uint16 depth);
		~GEngine_SDL();

		void 							Clear();
		void 							Flip();

		virtual void					DrawImage(const ImageResource& image, sint16 x, sint16 y) const;
		virtual void 					DrawImage(const ImageResource& image, sint16 x, sint16 y, float fAngle, float fZoom) const;
		virtual void 					SetPixel(sint16 x, sint16 y, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawFillRect(sint16 x, sint16 y, sint16 width, sint16 height, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawFillCircle(sint16 x, sint16 y, sint16 radius, uint8 r, uint8 g, uint8 b) const;
		virtual void 					DrawLine(sint16 x1, sint16 y1, sint16 x2, sint16 y2, uint8 r, uint8 g, uint8 b) const;
		virtual void 					PrintArgs(sint16 x, sint16 y, uint size, ETextAlign eAlign, uint8 r, uint8 g, uint8 b, const char* format, va_list oArgs);

		virtual Font*					CreateFontResource(const char* path, uint16 size);
		virtual ImageResource*			CreateImageResource(const char* path);


		const InputEvent&				PollEvent();
		const InputEvent&				WaitEvent();

	protected:
		uint 							Init();
		uint 							Close();

	private:
		SDL_Surface*					m_pScreen;
};

#endif // __GENGINE_SDL_H__

