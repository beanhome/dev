#include "IBWorld.h"


IBWorld::IBWorld()
{

}

IBWorld::~IBWorld()
{
}

void IBWorld::Init()
{
	m_oTable.PutCube(&m_oCube1);
	m_oTable.PutCube(&m_oCube2);
	m_oTable.PutCube(&m_oCube3);
	//m_oCube2.PutCube(&m_oCube1);
}


void IBWorld::MoveCubeFromTableToCube(IBCube* pCube, IBCube* pDestCube)
{
	assert(m_oTable.HasCube(pCube));
	assert(pCube->IsFree());
	assert(pDestCube->IsFree());

	m_oTable.TakeCube(pCube);
	pDestCube->PutCube(pCube);
}

void IBWorld::MoveCubeFromCubeToCube(IBCube* pCube, IBCube* pOrigCube, IBCube* pDestCube)
{
	assert(pCube->IsFree());
	assert(pDestCube->IsFree());
	assert(pOrigCube->HasCube(pCube));

	pOrigCube->TakeCube();
	pDestCube->PutCube(pCube);
}

void IBWorld::MoveCubeFromCubeToTable(IBCube* pCube, IBCube* pOrigCube)
{
	assert(pCube->IsFree());
	assert(pOrigCube->HasCube(pCube));

	pOrigCube->TakeCube();
	m_oTable.PutCube(pCube);
}

bool IBWorld::IsCubeOnTable(IBCube* pCube)
{
	return (m_oTable.HasCube(pCube));
}

bool IBWorld::IsCubeOnCube(IBCube* pCube1, IBCube* pCube2)
{
	return (pCube2->HasCube(pCube1));
}

