#ifndef __IMAGERESOURCE_H__
#define __IMAGERESOURCE_H__

#include "Utils.h"
#include "Resource.h"

class ImageResource : public Resource
{
	public:
		ImageResource(GEngine* pGEngine);
		~ImageResource();

		uint16 GetWidth() const { return m_iWidth; }
		uint16 GetHeight() const { return m_iHeight; }

	protected:
		uint16 m_iWidth;
		uint16 m_iHeight;
};


#endif // __IMAGERESOURCE_H__

