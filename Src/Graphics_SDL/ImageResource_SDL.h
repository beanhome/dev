#ifndef __IMAGERESOURCE_SDL_H__
#define __IMAGERESOURCE_SDL_H__

#include "Utils.h"
#include "ImageResource.h"

struct SDL_Surface;

class ImageResource_SDL : public ImageResource
{
	public:
		ImageResource_SDL(GEngine* pGEngine, uint32 crc, const char* path);
		~ImageResource_SDL();

	public:
		SDL_Surface*	m_pSurface;
};


#endif // __IMAGERESOURCE_SDL_H__

