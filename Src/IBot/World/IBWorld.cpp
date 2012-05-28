#include "IBWorld.h"


IBWorld::IBWorld()
{
	m_oCubes.resize(3);

	GetCubeA()->SetName("Cube_A");
	GetCubeB()->SetName("Cube_B");
	GetCubeC()->SetName("Cube_C");
}

IBWorld::~IBWorld()
{
}

#define WORLD_CONFIG 1

void IBWorld::Init()
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

void IBWorld::Print() const
{
	m_oTable.Print();

	GetCubeA()->Print();
	GetCubeB()->Print();
	GetCubeC()->Print();
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

