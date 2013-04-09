#include "Utils.h"
#include "GEngine.h"
#include "Resource.h"
#include "Canvas.h"
#include "Input.h"

GEngine::GEngine(uint16 width, uint16 height, uint16 depth, const char* rootpath)
	: CanvasBase(width, height)
	, m_iDepth(depth)
	, m_sRootPath(rootpath)
	, m_pInputEvent(NULL)
	, m_pPreviousInputEvent(NULL)
	, m_pInput(NULL)
{
	m_pInput = new Input(*this);
}

GEngine::~GEngine()
{
	delete m_pInput;
	PurgeResource(); // probablement vide
}

void GEngine::ClampCanvas(const Canvas& canvas) const
{
	ClampRect(canvas.GetClampingRect());
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

void GEngine::UpdateInput()
{
	m_pInput->Update();
}

sint32 GEngine::GetMouseX() const
{
	return m_pInput->GetMouseX();
}

sint32 GEngine::GetMouseY() const
{
	return m_pInput->GetMouseY();
}
