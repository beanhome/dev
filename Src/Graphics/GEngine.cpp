#include "Utils.h"
#include "GEngine.h"
#include "Resource.h"
#include "Canvas.h"
#include "EventManager.h"
#include "GApp.h"

GEngine::GEngine(uint16 width, uint16 height, uint16 depth, const char* rootpath)
	: CanvasBase(width, height)
	, m_pApp(NULL)
	, m_iDepth(depth)
	, m_sRootPath(rootpath)
	, m_pEventManager(NULL)
{
	if (m_sRootPath[m_sRootPath.length()-1] != '/') m_sRootPath.push_back('/');
	m_pEventManager = new EventManager(*this);
}

GEngine::GEngine(GAppBase* pApp, uint16 width, uint16 height, uint16 depth, const char* rootpath)
	: CanvasBase(width, height)
	, m_pApp(pApp)
	, m_iDepth(depth)
	, m_sRootPath(rootpath)
	, m_pEventManager(NULL)
{
	if (m_sRootPath[m_sRootPath.length()-1] != '/') m_sRootPath.push_back('/');
	m_pEventManager = new EventManager(*this);
}

GEngine::~GEngine()
{
	delete m_pEventManager;
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

void GEngine::UpdateEvent(float dt)
{
	m_pEventManager->Update(dt);
}

sint32 GEngine::GetMouseX() const
{
	return m_pEventManager->GetMouseX();
}

sint32 GEngine::GetMouseY() const
{
	return m_pEventManager->GetMouseY();
}

void GEngine::ReceiveEvent( Event* pEvent )
{
	if (m_pApp != NULL)
		m_pApp->CatchEvent(pEvent);
}
