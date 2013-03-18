#include "IBCubeWorld.h"


IBCubeWorld::IBCubeWorld()
{
	m_oCubes.resize(3);

	for (uint i=0 ; i<m_oCubes.size() ; ++i)
	{
		m_oCubes[i] = new IBCube(FormatString("Cube_%c", 'A'+i));
	}
}

IBCubeWorld::~IBCubeWorld()
{
	for (uint i=0 ; i<m_oCubes.size() ; ++i)
	{
		delete m_oCubes[i];
	}
}

#define WORLD_CONFIG 1

void IBCubeWorld::Init()
{
#if WORLD_CONFIG == 0
	// Config A
	m_oTable.PutCube(GetCubeA());
	m_oTable.PutCube(GetCubeB());
	m_oTable.PutCube(GetCubeC());
#elif WORLD_CONFIG == 1
	// ConfigB
	m_oTable.PutCube(GetCubeA());
	m_oTable.PutCube(GetCubeB());
	GetCubeB()->PutCube(GetCubeC());
#endif
}

void IBCubeWorld::Print() const
{
	m_oTable.Print();

	GetCubeA()->Print();
	GetCubeB()->Print();
	GetCubeC()->Print();
}



void IBCubeWorld::MoveCubeFromTableToCube(IBCube* pCube, IBCube* pDestCube)
{
	assert(m_oTable.HasCube(pCube));
	assert(pCube->IsFree());
	assert(pDestCube->IsFree());

	m_oTable.TakeCube(pCube);
	pDestCube->PutCube(pCube);
}

void IBCubeWorld::MoveCubeFromCubeToCube(IBCube* pCube, IBCube* pOrigCube, IBCube* pDestCube)
{
	assert(pCube->IsFree());
	assert(pDestCube->IsFree());
	assert(pOrigCube->HasCube(pCube));

	pOrigCube->TakeCube();
	pDestCube->PutCube(pCube);
}

void IBCubeWorld::MoveCubeFromCubeToTable(IBCube* pCube, IBCube* pOrigCube)
{
	assert(pCube->IsFree());
	assert(pOrigCube->HasCube(pCube));

	pOrigCube->TakeCube();
	m_oTable.PutCube(pCube);
}

bool IBCubeWorld::IsCubeOnTable(IBCube* pCube)
{
	return (m_oTable.HasCube(pCube));
}

bool IBCubeWorld::IsCubeOnCube(IBCube* pCube1, IBCube* pCube2)
{
	return (pCube2->HasCube(pCube1));
}

