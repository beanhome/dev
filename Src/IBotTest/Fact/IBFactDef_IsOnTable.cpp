#include "IBFactDef_IsOnTable.h"
#include "World/IBCube.h"
#include "World/IBCubeWorld.h"
#include "IBPlanner.h"

IBFactDef_IsOnTable::IBFactDef_IsOnTable(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 1, pPlanner)
{
}

IBFactDef_IsOnTable::~IBFactDef_IsOnTable()
{
}

IBF_Result IBFactDef_IsOnTable::Test(const vector<void*>& aUserData)
{
	assert(aUserData.size() == 1);
	IBWorld* pWorld = static_cast<IBWorld*>(m_pPlanner->GetOwner());

	IBCube* pCube = (IBCube*)aUserData[0];
	return (pWorld->IsCubeOnTable(pCube) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_IsOnTable::ResolveVariable(vector<void*>& aUserData)
{
	assert(aUserData.size() == 1);
	IBWorld* pWorld = static_cast<IBWorld*>(m_pPlanner->GetOwner());

	if (aUserData[0] == NULL)
	{
		for (uint i=0 ; i<pWorld->GetCubes().size() ; ++i)
		{
			if (pWorld->IsCubeOnTable(&pWorld->GetCubes()[i]))
			{
				aUserData[0] = (void*)&(pWorld->GetCubes()[i]);
				break;
			}
		}
	}

	assert(aUserData[0] != NULL);
}

void IBFactDef_IsOnTable::Print(const vector<void*>& aUserData, int tab) const
{
	assert(aUserData.size() == 1);

	IBCube* pCube = (IBCube*)aUserData[0];

	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s (%s)\n", GetName().c_str(), pCube->GetName().c_str());
}

