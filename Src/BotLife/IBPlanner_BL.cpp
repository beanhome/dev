#include "IBPlanner_BL.h"

#include "Fact\IBFactDef_BotAtPos.h"
#include "Fact\IBFactDef_HasValidPath.h"
#include "Fact\IBFactDef_BotHasObject.h"
#include "Fact\IBFactDef_ObjectAtPos.h"
#include "Fact\IBFactDef_BotIsEmpty.h"
#include "Fact\IBFactDef_BotNearPos.h"
#include "Fact\IBFactDef_PropIsUnblock.h"
#include "Fact\IBFactDef_PosIsFree.h"

#include "Action\IBActionDef_FollowPath.h"
#include "Action\IBActionDef_FindPath.h"
#include "Action\IBActionDef_PickObject.h"
#include "Action\IBActionDef_UnblockProp.h"
#include "Action\IBActionDef_DropObject.h"


IBPlanner_BL::IBPlanner_BL(void* pOwner, CanvasBase& canvas)
	: IBGPlanner(pOwner, canvas)
{
	REGISTER_FACT(IBFactDef_BotAtPos);
	REGISTER_FACT(IBFactDef_BotNearPos);
	REGISTER_FACT(IBFactDef_PosIsFree);
	REGISTER_FACT(IBFactDef_ObjectAtPos);
	REGISTER_FACT(IBFactDef_HasValidPath);
	REGISTER_FACT(IBFactDef_BotHasObject);
	REGISTER_FACT(IBFactDef_BotIsEmpty);
	REGISTER_FACT(IBFactDef_PropIsUnblock);
	REGISTER_FACT(IBFactDef_PropIsBlock);
	REGISTER_FACT_NAMED(IBFactDef_PropIsUnblock, "IBFactDef_DoorIsOpen");
	REGISTER_FACT_NAMED(IBFactDef_PropIsBlock, "IBFactDef_DoorIsClose");

	REGISTER_ACTION(IBActionDef_FollowPath);
	REGISTER_ACTION(IBActionDef_FindPath);
	REGISTER_ACTION(IBActionDef_PickObject);
	REGISTER_ACTION(IBActionDef_DropObject);
	REGISTER_ACTION(IBActionDef_UnblockProp);
	REGISTER_ACTION_NAMED(IBActionDef_UnblockProp, "IBActionDef_OpenDoor");
}

IBPlanner_BL::~IBPlanner_BL()
{
}


