#include "SDL_ttf.h"

#include "FontResource_SDL.h"
#include "GEngine.h"

FontResource_SDL::FontResource_SDL(GEngine* pGEngine, uint32 crc, const char* path, uint16 size)
	: FontResource(pGEngine, crc/*, path, size*/)
	, m_pFont(NULL)
{
	string sPath = FormatString("%s%s", pGEngine->GetRootPath().c_str(), path);
	m_pFont = TTF_OpenFont(sPath.c_str(), size);
}

FontResource_SDL::FontResource_SDL(GEngine* pGEngine, uint32 crc, const Desc& oDesc)
	: FontResource(pGEngine, crc/*, oDesc*/)
	, m_pFont(NULL)
{
	string sPath = FormatString("%s%s", pGEngine->GetRootPath().c_str(), oDesc.path);
	m_pFont = TTF_OpenFont(sPath.c_str(), oDesc.size);
}


FontResource_SDL::~FontResource_SDL()
{
	TTF_CloseFont(m_pFont);
}

uint16 FontResource_SDL::GetSize() const
{
	return (m_pFont != NULL ? (uint16)TTF_FontHeight(m_pFont) : 0);
}

uint16 FontResource_SDL::GetLineSkip() const
{
	return (m_pFont != NULL ? (uint16)TTF_FontLineSkip(m_pFont) : 0);
}


