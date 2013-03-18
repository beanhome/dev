#include "IBCube.h"


IBCube::IBCube(const string& name)
	: IBObject(name)
	, m_pTopCube(NULL)
{
}

IBCube::~IBCube()
{
}

void IBCube::PutCube(IBCube* pCube)
{
	assert(m_pTopCube == NULL);
	m_pTopCube = pCube;
}

void IBCube::TakeCube()
{
	m_pTopCube = NULL;
}

void IBCube::Print() const
{
	LOG("Cube : %s", m_sName.c_str());
	if (m_pTopCube != NULL)
		LOG("  support %s", m_pTopCube->GetName().c_str());
	else
		LOG("  free");

	LOG("\n");
}

void IBCube::FormatData() const
{
	if (m_pTopCube != NULL)
		m_sData = " [" + m_pTopCube->GetName() + "]";
	else
		m_sData = " [free]";
}
