#include "Resource.h"
#include "GEngine.h"

Resource::Resource(GEngine* pGEngine, uint32 crc)
	: m_pEngine(pGEngine)
{
	m_pEngine->AddResource(crc, this);
}

Resource::~Resource()
{
	m_pEngine->RemResource(this);
}
