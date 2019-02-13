#include "SDL_ttf.h"
#include "SDL_FontCache.h"

#include "FontResource_SDL.h"
#include "GEngine_SDL.h"
#include "GEngine.h"

FontResource_SDL::FontResource_SDL(GEngine* pGEngine, uint32 crc, const char* path, uint16 size)
	: FontResource(pGEngine, crc/*, path, size*/)
	, m_pFont(NULL)
{
	string sPath = FormatString("%s%s", pGEngine->GetRootPath().c_str(), path);
	m_pFont = FC_CreateFont();
	FC_LoadFont(m_pFont, ((GEngine_SDL*)pGEngine)->GetRenderer(), sPath.c_str(), size, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);
}

FontResource_SDL::FontResource_SDL(GEngine* pGEngine, uint32 crc, const Desc& oDesc)
	: FontResource(pGEngine, crc/*, oDesc*/)
	, m_pFont(NULL)
{
	string sPath = FormatString("%s%s", pGEngine->GetRootPath().c_str(), oDesc.path);
	m_pFont = FC_CreateFont();
	FC_LoadFont(m_pFont, ((GEngine_SDL*)pGEngine)->GetRenderer(), sPath.c_str(), oDesc.size, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);
}


FontResource_SDL::~FontResource_SDL()
{
	FC_FreeFont(m_pFont);
}

uint16 FontResource_SDL::GetSize() const
{
	return (m_pFont != NULL ? (uint16)FC_GetLineHeight(m_pFont) : 0);
}

uint16 FontResource_SDL::GetLineSkip() const
{
	return (m_pFont != NULL ? (uint16)FC_GetLineSpacing(m_pFont) : 0);
}


