#include "IBFactDef_IsOnTable.h"
#include "World/IBCube.h"
#include "World/IBCubeWorld.h"

extern IBWorld g_oWorld;

IBFactDef_IsOnTable::IBFactDef_IsOnTable(const string& name)
	: IBFactDef(name, 1)
{
}

IBFactDef_IsOnTable::~IBFactDef_IsOnTable()
{
}

IBF_Result IBFactDef_IsOnTable::Test(const vector<void*>& aUserData)
{
	assert(aUserData.size() == 1);

	IBCube* pCube = (IBCube*)aUserData[0];
	return (g_oWorld.IsCubeOnTable(pCube) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_IsOnTable::ResolveVariable(vector<void*>& aUserData)
{
	assert(aUserData.size() == 1);

	if (aUserData[0] == NULL)
	{
		for (uint i=0 ; i<g_oWorld.GetCubes().size() ; ++i)
		{
			if (g_oWorld.IsCubeOnTable(&g_oWorld.GetCubes()[i]))
			{
				aUserData[0] = (void*)&(g_oWorld.GetCubes()[i]);
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

