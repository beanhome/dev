#include "ImageResource.h"
#include "CRC32.h"

ImageResource::ImageResource(GEngine* pGEngine, uint32 crc, const char* path)
	: Resource(pGEngine, crc)
	, m_sPath(path)
	, m_iWidth(0)
	, m_iHeight(0)
{
}

ImageResource::ImageResource(GEngine* pGEngine, uint32 crc, const Desc& oDesc)
	: Resource(pGEngine, crc)
	, m_sPath(oDesc.path)
	, m_iWidth(0)
	, m_iHeight(0)
{
}


ImageResource::~ImageResource()
{
}

uint32 ImageResource::ComputeCRC32(const Desc& oDesc)
{
	uint32 crc = 0;
	CRC32::s_oGenerator.FullCRC((uint8*)oDesc.path, strlen(oDesc.path), &crc);
	return crc;
}

