#include "IBTable.h"


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

bool IBTable::HasCube(IBCube* pCube)
{
	return (m_aCube.find(pCube) != m_aCube.end());
}
