#include "ImageResource_SDL.h"

#include "SDL.h"
#include "SDL_video.h"
#include "SDL_Draw.h"
#include "SDL_ttf.h"
#include "SDL_rotozoom.h"


ImageResource_SDL::ImageResource_SDL(GEngine* pGEngine, const char* pPath)
	: ImageResource(pGEngine)
	, m_pSurface(NULL)
{
	/* Load the BMP file into a surface */
	m_pSurface = SDL_LoadBMP(pPath);
	if (m_pSurface == NULL)
	{
		LOG("Couldn't load %s: %s\n", pPath, SDL_GetError());
	}
	else
	{
		//SDL_SetColorKey(m_pSurface, SDL_SRCCOLORKEY, SDL_MapRGB(m_pSurface->format, 255, 255, 255));
	}
}

ImageResource_SDL::~ImageResource_SDL()
{
	SDL_FreeSurface(m_pSurface);
}
