#include "IBFactDef_IsTopOf.h"
#include "World/IBCube.h"
#include "World/IBWorld.h"

extern IBWorld g_oWorld;


IBFactDef_IsTopOf::IBFactDef_IsTopOf(const string& name)
	: IBFactDef(name, 2)
{
}

IBFactDef_IsTopOf::~IBFactDef_IsTopOf()
{
}

IBF_Result IBFactDef_IsTopOf::Test(const vector<void*>& aUserData)
{
	assert(aUserData.size() == 2);

	IBCube* pCube1 = (IBCube*)aUserData[0];
	IBCube* pCube2 = (IBCube*)aUserData[1];

	if (pCube1 == NULL || pCube2 == NULL)
		return IBF_UNKNOW;

	return (g_oWorld.IsCubeOnCube(pCube1, pCube2) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_IsTopOf::ResolveVariable(vector<void*>& aUserData)
{
	assert(aUserData.size() == 2);

	IBCube* pCubeTop = (IBCube*)aUserData[0];
	IBCube* pCubeDown = (IBCube*)aUserData[1];

	if (pCubeTop == NULL && pCubeDown == NULL)
	{
		for (uint i=0 ; i<g_oWorld.GetCubes().size() ; ++i)
		{
			for (uint j=0 ; j<g_oWorld.GetCubes().size() ; ++j)
			{
				if (i!=j)
				{
					IBCube* pCubeA = &g_oWorld.GetCubes()[i];
					IBCube* pCubeB = &g_oWorld.GetCubes()[j];
					if (g_oWorld.IsCubeOnCube(pCubeA, pCubeB))
					{
						pCubeTop = pCubeA;
						pCubeDown = pCubeB;
						break;
					}
				}
			}
		}
	}
	else if (pCubeTop == NULL)
	{
		for (uint i=0 ; i<g_oWorld.GetCubes().size() ; ++i)
		{
			IBCube* pCube = &g_oWorld.GetCubes()[i];
			if (g_oWorld.IsCubeOnCube(pCube, pCubeDown))
			{
				pCubeTop = pCube;
				break;
			}
		}
	}
	else if (pCubeDown == NULL)
	{
		for (uint i=0 ; i<g_oWorld.GetCubes().size() ; ++i)
		{
			IBCube* pCube = &g_oWorld.GetCubes()[i];
			if (g_oWorld.IsCubeOnCube(pCubeTop, pCube))
			{
				pCubeDown = pCube;
				break;
			}
		}
	}

	aUserData[0] = pCubeTop;
	aUserData[1] = pCubeDown;
}

void IBFactDef_IsTopOf::Print(const vector<void*>& aUserData, int tab) const
{
	assert(aUserData.size() == 2);

	IBCube* pCube1 = (IBCube*)aUserData[0];
	IBCube* pCube2 = (IBCube*)aUserData[1];

	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s (%s, %s)\n", GetName().c_str(), (pCube1 != NULL ? pCube1->GetName().c_str() : "NULL"), (pCube2 != NULL ? pCube2->GetName().c_str() : "NULL"));
}

