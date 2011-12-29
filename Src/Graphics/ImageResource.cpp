#include "ImageResource.h"

ImageResource::ImageResource(GEngine* pGEngine, uint32 crc, const char* path)
	: Resource(pGEngine, crc)
	, m_sPath(path)
	, m_iWidth(0)
	, m_iHeight(0)
{
}

ImageResource::~ImageResource()
{
}

