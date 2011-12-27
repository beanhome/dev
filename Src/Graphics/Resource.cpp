#include "Resource.h"
#include "GEngine.h"

Resource::Resource(GEngine* pGEngine)
	: m_pGEngine(pGEngine)
{
	m_pGEngine->AddResource(this);
}

Resource::~Resource()
{
	m_pGEngine->RemResource(this);
}