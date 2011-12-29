#include "Resource.h"
#include "GEngine.h"

Resource::Resource(GEngine* pGEngine, uint32 crc)
	: m_pGEngine(pGEngine)
{
	m_pGEngine->AddResource(crc, this);
}

Resource::~Resource()
{
	m_pGEngine->RemResource(this);
}