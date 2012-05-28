#include "IBFactDef_IsFree.h"
#include "World/IBCube.h"
#include "World/IBWorld.h"

extern IBWorld g_oWorld;

IBFactDef_IsFree::IBFactDef_IsFree(const string& name)
	: IBFactDef(name, 1)
{
}

IBFactDef_IsFree::~IBFactDef_IsFree()
{
}

IBF_Result IBFactDef_IsFree::Test(const vector<void*>& aUserData)
{
	assert(aUserData.size() == 1);

	IBCube* pCube = (IBCube*)aUserData[0];
	return ((pCube != NULL && pCube->IsFree()) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_IsFree::ResolveVariable(vector<void*>& aUserData)
{
	assert(aUserData.size() == 1);

	if (aUserData[0] == NULL)
	{
		for (uint i=0 ; i<g_oWorld.GetCubes().size() ; ++i)
		{
			if (g_oWorld.GetCubes()[i].IsFree())
			{
				aUserData[0] = (void*)&(g_oWorld.GetCubes()[i]);
				break;
			}
		}
	}

	assert(aUserData[0] != NULL);
}

void IBFactDef_IsFree::Print(const vector<void*>& aUserData, int tab) const
{
	assert(aUserData.size() == 1);

	IBCube* pCube = (IBCube*)aUserData[0];

	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s (%s)\n", GetName().c_str(), pCube->GetName().c_str());
}


