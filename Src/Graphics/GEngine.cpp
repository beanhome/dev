#include "Utils.h"
#include "GEngine.h"


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
	set<Resource*> aCopy = m_aResource;

	for (set<Resource*>::iterator it = aCopy.begin() ; it != aCopy.end() ; ++it)
		delete *it;
}

bool GEngine::AddResource(Resource* pRes)
{
	pair<set<Resource*>::iterator, bool> res = m_aResource.insert(pRes);
	return res.second;
}

bool GEngine::RemResource(Resource* pRes)
{
	set<Resource*>::iterator it = m_aResource.find(pRes);

	if (it == m_aResource.end())
		return false;

	m_aResource.erase(it);

	return true;
}


const Font* const GEngine::GetFont(const char* path, uint16 size)
{
	Font* pFont = NULL;
	FontMap::iterator iter = m_aFontMap.find(size);
	if (iter == m_aFontMap.end())
	{
		pFont = CreateFontResource(path, size);
		m_aFontMap.insert(FontPair(size, pFont));
	}
	else
	{
		pFont = iter->second;
	}

	return pFont;
}
