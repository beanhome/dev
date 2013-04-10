#include "IBFactDef_IsFree.h"
#include "World/IBCube.h"
#include "World/IBCubeWorld.h"
#include "IBPlanner.h"

IBFactDef_IsFree::IBFactDef_IsFree(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 1, pPlanner)
{
}

IBFactDef_IsFree::~IBFactDef_IsFree()
{
}

IBF_Result IBFactDef_IsFree::Test(const vector<IBObject*>& aUserData)
{
	assert(aUserData.size() == 1);

	IBCube* pCube = (IBCube*)aUserData[0];

	if (pCube == NULL)
		return IBF_UNKNOW;

	return (pCube->IsFree() ? IBF_OK : IBF_FAIL);


}

void IBFactDef_IsFree::ResolveVariable(vector<IBObject*>& aUserData)
{
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(m_pPlanner->GetOwner());
	assert(aUserData.size() == 1);

	if (aUserData[0] == NULL)
	{
		for (uint i=0 ; i<pWorld->GetCubes().size() ; ++i)
		{
			IBCube* pCube = pWorld->GetCubes()[i];

			if (pCube->IsFree())
			{
				aUserData[0] = pCube;
				break;
			}
		}
	}

	assert(aUserData[0] != NULL);
}
