#include "IBPlanner_BL.h"

#include "Fact\IBFactDef_BotAtPos.h"
#include "Fact\IBFactDef_HasValidPath.h"

#include "Action\IBActionDef_FollowPath.h"
#include "Action\IBActionDef_FindPath.h"


IBPlanner_BL::IBPlanner_BL(void* pOwner)
	: IBPlanner(pOwner)
{
	REGISTER_FACT(IBFactDef_BotAtPos);
	REGISTER_FACT(IBFactDef_HasValidPath);

	REGISTER_ACTION(IBActionDef_FollowPath);
	REGISTER_ACTION(IBActionDef_FindPath);
}

IBPlanner_BL::~IBPlanner_BL()
{
}


