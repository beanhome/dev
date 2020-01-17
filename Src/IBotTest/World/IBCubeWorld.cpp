#include "IBCubeWorld.h"
#include "CanvasBase.h"


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

IBCube* IBCubeWorld::CreateCube(const string& name)
{
	IBCube* pCube = GetCube(name);
	if (pCube == nullptr)
	{
		pCube = new IBCube(name);
		m_oCubes.push_back(pCube);
	}

	return pCube;
}

IBCube* IBCubeWorld::GetCube(const string& name)
{
	for (uint i = 0; i < m_oCubes.size(); ++i)
	{
		if (m_oCubes[i] != nullptr && m_oCubes[i]->GetName() == name)
			return m_oCubes[i];
	}

	return nullptr;
}


void IBCubeWorld::Init(const char* sInit)
{
	IBCube* pPreviousCube = nullptr;

	for (uint i = 0; i < strlen(sInit); ++i)
	{
		if (!isalpha(sInit[i]))
		{
			pPreviousCube = nullptr;
			continue;
		}

		string sName = FormatString("Cube_%c", toupper(sInit[i]));
		IBCube* pCube = CreateCube(sName);

		if (!m_oTable.HasCube(pCube))
			m_oTable.PutCube(pCube);

		if (pPreviousCube != nullptr)
		{
			m_oTable.TakeCube(pPreviousCube);
			pCube->PutCube(pPreviousCube);
		}

		pPreviousCube = pCube;
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

void IBCubeWorld::Draw(class CanvasBase& oWorldCanva) const
{
	int size = 48;
	int space = 32;
	int line = oWorldCanva.GetHeight() - size;
	int left_space = 32;

	oWorldCanva.DrawLine(left_space, line, left_space + (size*GetCubes().size()) + ((size + 1)*GetCubes().size()), line, Color(192, 255, 255));

	for (uint i = 0; i < GetCubes().size(); ++i)
	{
		const IBCube* pCube = GetCubes()[i];

		if (GetTable().HasCube((IBCube*)pCube))
		{
			pCube->Draw(oWorldCanva, i, 0);
		}
	}
}
