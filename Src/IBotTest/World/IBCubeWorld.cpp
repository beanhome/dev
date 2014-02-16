#include "IBCubeWorld.h"


IBCubeWorld::IBCubeWorld()
{
}

IBCubeWorld::~IBCubeWorld()
{
	for (uint i=0 ; i<m_oCubes.size() ; ++i)
	{
		delete m_oCubes[i];
	}
}


void IBCubeWorld::CreateCube(int nb)
{
	for (uint i=0 ; i<m_oCubes.size() ; ++i)
		delete m_oCubes[i];
		
	m_oCubes.resize(nb);

	for (uint i=0 ; i<m_oCubes.size() ; ++i)
		m_oCubes[i] = new IBCube(FormatString("Cube_%c", 'A'+i));
}

void IBCubeWorld::Init(int config)
{
	switch (config)
	{
		case 1:
			CreateCube(3);
			m_oTable.PutCube(GetCubeA());
			m_oTable.PutCube(GetCubeB());
			GetCubeB()->PutCube(GetCubeC());
			break;

		case 2:
			CreateCube(3);
			m_oTable.PutCube(GetCubeA());
			GetCubeA()->PutCube(GetCubeB());
			GetCubeB()->PutCube(GetCubeC());
			break;

		case 3:
			CreateCube(4);
			m_oTable.PutCube(GetCubes()[0]);
			for (uint i=0 ; i<GetCubes().size()-1 ; ++i)
				GetCubes()[i]->PutCube(GetCubes()[i+1]);
			break;

		default:
			CreateCube(3);
			for (uint i=0 ; i<GetCubes().size() ; ++i)
				m_oTable.PutCube(GetCubes()[i]);
	}
}

void IBCubeWorld::Print() const
{
	m_oTable.Print();

	for (uint i=0 ; i<GetCubes().size() ; ++i)
		GetCubes()[i]->Print();
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

