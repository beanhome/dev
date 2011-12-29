#include "Utils.h"
#include "GEngine.h"
#include "CRC32.h"


GEngine::GEngine(uint16 width, uint16 height, uint16 depth)
	: CanvasBase(width, height)
	, m_iDepth(depth)
	, m_pInputEvent(NULL)
{
}

GEngine::~GEngine()
{
	PurgeResource(); // probablement vide
}

void GEngine::PurgeResource()
{
	ResourceMap aCopy = m_aResources;

	for (ResourceMap::iterator it = aCopy.begin() ; it != aCopy.end() ; ++it)
		delete it->second;
}

bool GEngine::AddResource(uint32 crc, Resource* pRes)
{
	if (m_aResources.find(crc) != m_aResources.end())
		return false;

	m_aResources.insert(ResourcePair(crc, pRes));

	return true;
}

bool GEngine::RemResource(uint32 crc)
{
	ResourceMap::iterator it = m_aResources.find(crc);

	if (it == m_aResources.end())
		return false;

	m_aResources.erase(it);

	return true;
}

bool GEngine::RemResource(Resource* pRes)
{
	for (ResourceMap::iterator it = m_aResources.begin() ; it != m_aResources.end() ; ++it)
	{
		if (it->second == pRes)
		{
			m_aResources.erase(it);
			return true;
		}
	}

	return false;
}

uint32 GEngine::ComputeFontCRC32(const char* path, uint16 size)
{
	uint32 crc = 0;
	CRC32::s_oGenerator.FullCRC((uint8*)path, strlen(path), &crc);
	crc += size;
	return crc;
}

uint32 GEngine::ComputeImageCRC32(const char* path)
{
	uint32 crc = 0;
	CRC32::s_oGenerator.FullCRC((uint8*)path, strlen(path), &crc);
	return crc;
}

Font* const GEngine::GetFontResource(const char* path, uint16 size)
{
	uint32 crc = ComputeFontCRC32(path, size);

	ResourceMap::iterator iter = m_aResources.find(crc);

	return (iter == m_aResources.end() ? CreateFontResource(crc, path, size) : (Font*)iter->second);
}

ImageResource* const GEngine::GetImageResource(const char* path)
{
	uint32 crc = ComputeImageCRC32(path);

	ResourceMap::iterator iter = m_aResources.find(crc);

	return (iter == m_aResources.end() ? CreateImageResource(crc, path) : (ImageResource*)iter->second);
}


const Font* const GEngine::GetFont(const char* path, uint16 size)
{
	return GetFontResource(path, size);	
}
