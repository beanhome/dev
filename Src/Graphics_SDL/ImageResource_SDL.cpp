#include "SDL.h"
#include "SDL_video.h"
//#include "SDL_draw.h"
#include "SDL_ttf.h"
#include "SDL2_rotozoom.h"
#include "SDL_image.h"

#include "ImageResource_SDL.h"
#include "GEngine.h"
#include "GEngine_SDL.h"

ImageResource_SDL::ImageResource_SDL(GEngine* pGEngine, uint32 crc, const char* pPath)
	: ImageResource(pGEngine, crc, pPath)
	, m_pTexture(NULL)
{
	string path = FormatString("%s%s", pGEngine->GetRootPath().c_str(), pPath);
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface == NULL)
	{
		LOG("Couldn't load %s: %s\n", pPath, SDL_GetError());
		return;
	}

	m_iWidth = pSurface->w;
	m_iHeight = pSurface->h;

	GEngine_SDL* pGEngineSDL = (GEngine_SDL*)pGEngine;
	m_pTexture = SDL_CreateTextureFromSurface(pGEngineSDL->GetRenderer(), pSurface);

	SDL_FreeSurface(pSurface);
}

ImageResource_SDL::ImageResource_SDL(GEngine* pGEngine, uint32 crc, const Desc& oDesc)
	: ImageResource(pGEngine, crc, oDesc)
	, m_pTexture(NULL)
{
	string path = FormatString("%s%s", pGEngine->GetRootPath().c_str(), oDesc.path);
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface == NULL)
	{
		LOG("Couldn't load %s: %s\n", oDesc.path, SDL_GetError());
		return;
	}
	
	m_iWidth = pSurface->w;
	m_iHeight = pSurface->h;

	GEngine_SDL* pGEngineSDL = (GEngine_SDL*)pGEngine;
	m_pTexture = SDL_CreateTextureFromSurface(pGEngineSDL->GetRenderer(), pSurface);

	SDL_FreeSurface(pSurface);
}


ImageResource_SDL::~ImageResource_SDL()
{
	SDL_DestroyTexture(m_pTexture);
}
