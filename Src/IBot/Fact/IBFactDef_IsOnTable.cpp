#include "IBFactDef_IsOnTable.h"
#include "IBCube.h"
#include "IBWorld.h"

extern IBWorld g_oWorld;

IBFactDef_IsOnTable::IBFactDef_IsOnTable()
{
}

IBFactDef_IsOnTable::~IBFactDef_IsOnTable()
{
}

IBF_Result IBFactDef_IsOnTable::Test(void* pUserData)
{
	IBCube* pCube = (IBCube*)pUserData;
	return (g_oWorld.IsCubeOnTable(pCube) ? IBF_OK : IBF_FAIL);
}


