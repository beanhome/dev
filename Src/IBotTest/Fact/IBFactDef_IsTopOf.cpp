#include "IBFactDef_IsTopOf.h"
#include "World/IBCube.h"
#include "World/IBCubeWorld.h"
#include "IBPlanner.h"


IBFactDef_IsTopOf::IBFactDef_IsTopOf(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 2, pPlanner)
{
}

IBFactDef_IsTopOf::~IBFactDef_IsTopOf()
{
}

IBF_Result IBFactDef_IsTopOf::Test(const vector<IBObject*>& aUserData)
{
	assert(aUserData.size() == 2);

	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(m_pPlanner->GetOwner());
	IBCube* pCube1 = (IBCube*)aUserData[0];
	IBCube* pCube2 = (IBCube*)aUserData[1];

	if (pCube1 == NULL || pCube2 == NULL)
		return IBF_UNKNOW;

	return (pWorld->IsCubeOnCube(pCube1, pCube2) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_IsTopOf::ResolveVariable(vector<IBObject*>& aUserData)
{
	assert(aUserData.size() == 2);

	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(m_pPlanner->GetOwner());
	IBCube* pCubeTop = (IBCube*)aUserData[0];
	IBCube* pCubeDown = (IBCube*)aUserData[1];

	if (pCubeTop == NULL && pCubeDown == NULL)
	{
		for (uint i=0 ; i<pWorld->GetCubes().size() ; ++i)
		{
			for (uint j=0 ; j<pWorld->GetCubes().size() ; ++j)
			{
				if (i!=j)
				{
					IBCube* pCubeA = pWorld->GetCubes()[i];
					IBCube* pCubeB = pWorld->GetCubes()[j];
					if (pWorld->IsCubeOnCube(pCubeA, pCubeB))
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
		for (uint i=0 ; i<pWorld->GetCubes().size() ; ++i)
		{
			IBCube* pCube = pWorld->GetCubes()[i];
			if (pWorld->IsCubeOnCube(pCube, pCubeDown))
			{
				pCubeTop = pCube;
				break;
			}
		}
	}
	else if (pCubeDown == NULL)
	{
		for (uint i=0 ; i<pWorld->GetCubes().size() ; ++i)
		{
			IBCube* pCube = pWorld->GetCubes()[i];
			if (pWorld->IsCubeOnCube(pCubeTop, pCube))
			{
				pCubeDown = pCube;
				break;
			}
		}
	}

	aUserData[0] = (IBObject*)pCubeTop;
	aUserData[1] = (IBObject*)pCubeDown;
}


