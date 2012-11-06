#include "IBTable.h"
#include "IBCube.h"


IBTable::IBTable()
{

}

IBTable::~IBTable()
{
}

void IBTable::PutCube(IBCube* pCube)
{
	assert(m_aCube.find(pCube) == m_aCube.end());
	m_aCube.insert(pCube);
}

void IBTable::TakeCube(IBCube* pCube)
{
	assert(m_aCube.find(pCube) != m_aCube.end());
	m_aCube.erase(pCube);
}

bool IBTable::HasCube(IBCube* pCube) const
{
	return (m_aCube.find(pCube) != m_aCube.end());
}

void IBTable::Print() const
{
	LOG("Table : ");
	for (set<IBCube*>::const_iterator it = m_aCube.begin() ; it != m_aCube.end() ; ++it)
	{
		LOG("%s ", (*it)->GetName().c_str());
	}
	LOG("\n");
}
