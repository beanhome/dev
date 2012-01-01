#include "ImageResource_SDL.h"

#include "SDL.h"
#include "SDL_video.h"
#include "SDL_Draw.h"
#include "SDL_ttf.h"
#include "SDL_rotozoom.h"
#include "SDL_image.h"


ImageResource_SDL::ImageResource_SDL(GEngine* pGEngine, uint32 crc, const char* pPath)
	: ImageResource(pGEngine, crc, pPath)
	, m_pSurface(NULL)
{
	m_pSurface = IMG_Load(pPath);
	if (m_pSurface == NULL)
	{
		LOG("Couldn't load %s: %s\n", pPath, SDL_GetError());
	}
	else
	{
		m_iWidth = m_pSurface->w;
		m_iHeight = m_pSurface->h;
	}
}

ImageResource_SDL::ImageResource_SDL(GEngine* pGEngine, uint32 crc, const Desc& oDesc)
	: ImageResource(pGEngine, crc, oDesc)
	, m_pSurface(NULL)
{
	m_pSurface = IMG_Load(oDesc.path);
	if (m_pSurface == NULL)
	{
		LOG("Couldn't load %s: %s\n", oDesc.path, SDL_GetError());
	}
	else
	{
		m_iWidth = m_pSurface->w;
		m_iHeight = m_pSurface->h;
	}
}


ImageResource_SDL::~ImageResource_SDL()
{
	SDL_FreeSurface(m_pSurface);
}
