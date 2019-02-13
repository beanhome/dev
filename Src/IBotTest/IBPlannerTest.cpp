#include "IBPlannerTest.h"

#include "Fact/IBFactDef_IsOnTable.h"
#include "Fact/IBFactDef_IsTopOf.h"
#include "Fact/IBFactDef_IsFree.h"

#include "Action/IBActionDef_MoveCubeFromTableToCube.h"
#include "Action/IBActionDef_MoveCubeFromCubeToCube.h"
#include "Action/IBActionDef_MoveCubeFromCubeToTable.h"


IBPlannerTest::IBPlannerTest(void* pOwner)
	: IBPlanner(pOwner)
{
	REGISTER_FACT(IBFactDef_IsOnTable);
	REGISTER_FACT(IBFactDef_IsFree);
	REGISTER_FACT(IBFactDef_IsTopOf);

	REGISTER_ACTION(IBActionDef_MoveCubeFromTableToCube);
	REGISTER_ACTION(IBActionDef_MoveCubeFromCubeToTable);
	REGISTER_ACTION(IBActionDef_MoveCubeFromCubeToCube);
}

IBPlannerTest::~IBPlannerTest()
{
}


