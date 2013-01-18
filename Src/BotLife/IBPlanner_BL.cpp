#include "IBPlanner_BL.h"

#include "Fact\IBFactDef_BotAtPos.h"
#include "Fact\IBFactDef_HasValidPath.h"
#include "Fact\IBFactDef_BotHasObject.h"
#include "Fact\IBFactDef_BotIsEmpty.h"
#include "Fact\IBFactDef_BotNearPos.h"

#include "Action\IBActionDef_FollowPath.h"
#include "Action\IBActionDef_FindPath.h"
#include "Action\IBActionDef_PickObject.h"


IBPlanner_BL::IBPlanner_BL(void* pOwner)
	: IBPlanner(pOwner)
{
	REGISTER_FACT(IBFactDef_BotAtPos);
	REGISTER_FACT(IBFactDef_BotNearPos);
	REGISTER_FACT(IBFactDef_HasValidPath);
	REGISTER_FACT(IBFactDef_BotHasObject);
	REGISTER_FACT(IBFactDef_BotIsEmpty);

	REGISTER_ACTION(IBActionDef_FollowPath);
	REGISTER_ACTION(IBActionDef_FindPath);
	REGISTER_ACTION(IBActionDef_PickObject);
}

IBPlanner_BL::~IBPlanner_BL()
{
}


