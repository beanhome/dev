#include "Utils.h"
#include "GEngine.h"
#include "Resource.h"
#include "Canvas.h"

GEngine::GEngine(uint16 width, uint16 height, uint16 depth)
	: CanvasBase(width, height)
	, m_iDepth(depth)
	, m_pInputEvent(NULL)
	, m_pPreviousInputEvent(NULL)
{
}

GEngine::~GEngine()
{
	PurgeResource(); // probablement vide
}

void GEngine::ClampCanvas(const Canvas& canvas) const
{
	ClampRect(canvas.GetParent().GetScreenPosX()+canvas.GetPosX(), canvas.GetParent().GetScreenPosY()+canvas.GetPosY(), canvas.GetWidth(), canvas.GetHeight());
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

void GEngine::SaveEvent()
{
	assert(false);
}

