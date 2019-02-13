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

IBF_Result IBFactDef_IsFree::Test(const class IBFact* pFact) const
{
	IBCube* pCube = pFact->GetVariable<IBCube>();

	if (pCube == NULL)
		return IBF_UNKNOW;

	return (pCube->IsFree() ? IBF_OK : IBF_FAIL);
}
