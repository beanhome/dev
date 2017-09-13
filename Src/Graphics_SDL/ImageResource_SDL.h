#ifndef __IMAGERESOURCE_SDL_H__
#define __IMAGERESOURCE_SDL_H__

#include "Utils.h"
#include "ImageResource.h"

class ImageResource_SDL : public ImageResource
{
	public:
		ImageResource_SDL(GEngine* pGEngine, uint32 crc, const char* path);
		ImageResource_SDL(GEngine* pGEngine, uint32 crc, const Desc& oDesc);
		~ImageResource_SDL();

	public:
		struct SDL_Texture*	m_pTexture;
};


#endif // __IMAGERESOURCE_SDL_H__

