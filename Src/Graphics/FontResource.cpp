#include "FontResource.h"
#include "CRC32.h"

FontResource::FontResource(GEngine* pGEngine, uint32 crc, const char* path, uint16 size)
	: Resource(pGEngine, crc)
	, m_sPath(path)
	, m_iSize(size)
{}

FontResource::FontResource(GEngine* pGEngine, uint32 crc, const Desc& oDesc)
	: Resource(pGEngine, crc)
	, m_sPath(oDesc.path)
	, m_iSize(oDesc.size)
{}

FontResource::~FontResource()
{}

uint32 FontResource::ComputeCRC32(const Desc& oDesc)
{
	uint32 crc = 0;
	CRC32::s_oGenerator.FullCRC((uint8*)oDesc.path, strlen(oDesc.path), &crc);
	crc += oDesc.size;
	return crc;
}
