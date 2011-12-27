#include "ImageResource.h"

ImageResource::ImageResource(GEngine* pGEngine)
	: Resource(pGEngine)
	, m_iWidth(0)
	, m_iHeight(0)
{
}

ImageResource::~ImageResource()
{
}
