#include "IBFactDef_IsTopOf.h"
#include "World/IBCube.h"
#include "World/IBCubeWorld.h"
#include "IBPlanner.h"


IBFactDef_IsTopOf::IBFactDef_IsTopOf(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, pPlanner)
{
	AddVariable("Top");
	AddVariable("Bottom");
}

IBFactDef_IsTopOf::~IBFactDef_IsTopOf()
{
}

IBF_Result IBFactDef_IsTopOf::Test(const class IBFact* pFact) const
{
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(m_pPlanner->GetOwner());

	IBCube* pCube1 = pFact->GetVariable<IBCube>("Top");
	IBCube* pCube2 = pFact->GetVariable<IBCube>("Bottom");

	if (pCube1 == NULL || pCube2 == NULL)
		return IBF_UNKNOW;

	return (pWorld->IsCubeOnCube(pCube1, pCube2) ? IBF_OK : IBF_FAIL);
}
