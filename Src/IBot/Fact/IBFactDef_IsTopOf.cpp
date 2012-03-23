#include "IBFactDef_IsTopOf.h"
#include "IBCube.h"
#include "IBWorld.h"

extern IBWorld g_oWorld;


IBFactDef_IsTopOf::IBFactDef_IsTopOf()
{
}

IBFactDef_IsTopOf::~IBFactDef_IsTopOf()
{
}

IBF_Result IBFactDef_IsTopOf::Test(void* pUserData1, void* pUserData2)
{
	IBCube* pCube1 = (IBCube*)pUserData1;
	IBCube* pCube2 = (IBCube*)pUserData2;

	return (g_oWorld.IsCubeOnCube(pCube1, pCube2) ? IBF_OK : IBF_FAIL);
}


