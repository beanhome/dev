#include "FontResource_SDL.h"
#include "SDL_ttf.h"

FontResource_SDL::FontResource_SDL(GEngine* pGEngine, uint32 crc, const char* path, uint16 size)
	: FontResource(pGEngine, crc, path, size)
	, m_pFont(NULL)
{
	m_pFont = TTF_OpenFont(path, m_iSize);
}

FontResource_SDL::FontResource_SDL(GEngine* pGEngine, uint32 crc, const Desc& oDesc)
	: FontResource(pGEngine, crc, oDesc)
	, m_pFont(NULL)
{
	m_pFont = TTF_OpenFont(oDesc.path, m_iSize);
}


FontResource_SDL::~FontResource_SDL()
{
	TTF_CloseFont(m_pFont);
}

