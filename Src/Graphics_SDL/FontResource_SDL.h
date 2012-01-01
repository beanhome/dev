#ifndef __FONT_SDL_H__
#define __FONT_SDL_H__

#include "Utils.h"
#include "FontResource.h"

typedef struct _TTF_Font TTF_Font;

class FontResource_SDL : public FontResource
{
	public:
		FontResource_SDL(GEngine* pGEngine, uint32 crc, const char* path, uint16 size);
		FontResource_SDL(GEngine* pGEngine, uint32 crc, const Desc& oDesc);
		~FontResource_SDL();

	public:
		TTF_Font*		m_pFont;
};


#endif // __FONT_SDL_H__

