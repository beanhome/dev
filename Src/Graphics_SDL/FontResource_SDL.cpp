#include "FontResource_SDL.h"
#include "SDL_ttf.h"
#include "GEngine.h"

FontResource_SDL::FontResource_SDL(GEngine* pGEngine, uint32 crc, const char* path, uint16 size)
	: FontResource(pGEngine, crc, path, size)
	, m_pFont(NULL)
{
	string sPath = FormatString("%s%s%s", pGEngine->GetRootPath(), (pGEngine->GetRootPath()[strlen(pGEngine->GetRootPath())-1] == '/' ? "" : "/"), path);
	m_pFont = TTF_OpenFont(sPath.c_str(), m_iSize);
}

FontResource_SDL::FontResource_SDL(GEngine* pGEngine, uint32 crc, const Desc& oDesc)
	: FontResource(pGEngine, crc, oDesc)
	, m_pFont(NULL)
{
	string sPath = FormatString("%s%s%s", pGEngine->GetRootPath(), (pGEngine->GetRootPath()[strlen(pGEngine->GetRootPath())-1] == '/' ? "" : "/"), oDesc.path);
	m_pFont = TTF_OpenFont(sPath.c_str(), m_iSize);
}


FontResource_SDL::~FontResource_SDL()
{
	TTF_CloseFont(m_pFont);
}

