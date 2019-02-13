#ifndef __FONT_SDL_H__
#define __FONT_SDL_H__

#include "Utils.h"
#include "FontResource.h"

class FontResource_SDL : public FontResource
{
	public:
		FontResource_SDL(GEngine* pGEngine, uint32 crc, const char* path, uint16 size);
		FontResource_SDL(GEngine* pGEngine, uint32 crc, const Desc& oDesc);
		~FontResource_SDL();

		uint16 GetSize() const override;
		uint16 GetLineSkip() const override;

	public:
		struct FC_Font*	m_pFont;
};


#endif // __FONT_SDL_H__

