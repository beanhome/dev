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

IBF_Result IBFactDef_IsOnTable::Test(const vector<IBObject*>& aUserData)
{
	assert(aUserData.size() == 1);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(m_pPlanner->GetOwner());

	IBCube* pCube = (IBCube*)aUserData[0];

	if (pCube == NULL)
		return IBF_UNKNOW;

	return (pWorld->IsCubeOnTable(pCube) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_IsOnTable::ResolveVariable(vector<IBObject*>& aUserData)
{
	assert(aUserData.size() == 1);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(m_pPlanner->GetOwner());

	if (aUserData[0] == NULL)
	{
		for (uint i=0 ; i<pWorld->GetCubes().size() ; ++i)
		{
			if (pWorld->IsCubeOnTable(pWorld->GetCubes()[i]))
			{
				aUserData[0] = (IBObject*)(pWorld->GetCubes()[i]);
				break;
			}
		}
	}

	assert(aUserData[0] != NULL);
}

