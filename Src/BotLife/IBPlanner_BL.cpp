#include "IBPlanner_BL.h"

#include "Action/BLAction.h"

#include "Fact/IBFactDef_BotAtPos.h"
#include "Fact/IBFactDef_HasValidPath.h"
#include "Fact/IBFactDef_BotHasObject.h"
#include "Fact/IBFactDef_ObjectAtPos.h"
#include "Fact/IBFactDef_BotIsEmpty.h"
#include "Fact/IBFactDef_BotNearPos.h"
#include "Fact/IBFactDef_PropIsBlock.h"
#include "Fact/IBFactDef_PropIsPickable.h"
#include "Fact/IBFactDef_PropIsMovable.h"
#include "Fact/IBFactDef_PosIsFree.h"

#include "Action/IBActionDef_FollowPath.h"
#include "Action/IBActionDef_FindPath.h"
#include "Action/IBActionDef_PickObject.h"
#include "Action/IBActionDef_UnblockProp.h"
#include "Action/IBActionDef_DropObject.h"
#include "Action/IBActionDef_PushProp.h"

#include "World/BLInt.h"
#include "BLBot.h"


IBPlanner_BL::IBPlanner_BL(void* pOwner)
	: IBPlanner(pOwner)
{
	REGISTER_FACT(IBFactDef_BotAtPos);
	REGISTER_FACT(IBFactDef_BotNearPos);
	REGISTER_FACT(IBFactDef_PosIsFree);
	REGISTER_FACT(IBFactDef_ObjectAtPos);
	REGISTER_FACT(IBFactDef_HasValidPath);
	REGISTER_FACT(IBFactDef_BotHasObject);
	REGISTER_FACT(IBFactDef_BotIsEmpty);
	REGISTER_FACT(IBFactDef_PropIsBlock);
	REGISTER_FACT(IBFactDef_PropIsPickable);
	REGISTER_FACT(IBFactDef_PropIsMovable);
	REGISTER_FACT_NAMED(IBFactDef_PropIsBlock, "IBFactDef_DoorIsClose");

	REGISTER_ACTION(IBActionDef_FollowPath);
	REGISTER_ACTION(IBActionDef_FindPath);
	REGISTER_ACTION(IBActionDef_PickObject);
	REGISTER_ACTION(IBActionDef_DropObject);
	REGISTER_ACTION(IBActionDef_UnblockProp);
	REGISTER_ACTION(IBActionDef_PushProp);
	REGISTER_ACTION_NAMED(IBActionDef_UnblockProp, "IBActionDef_OpenDoor");
}

IBPlanner_BL::~IBPlanner_BL()
{
}

IBAction* IBPlanner_BL::InstanciateAction(const class IBActionDef* pDef, IBFact* pPostCond)
{
	return new BLAction(pDef, pPostCond, this);
}

bool IBPlanner_BL::AreCompatible(const IBFact* A, const IBFact* B) const
{
	ASSERT(A != nullptr);
	ASSERT(B != nullptr);

	static string sBotNearPos = "BotNearPos";
	static string sBotAtPos = "BotAtPos";

	if (A->GetFactDef()->GetName() == sBotNearPos && B->GetFactDef()->GetName() == sBotNearPos)
	{
		if (A->IsInverted() != B->IsInverted())
			return true;

		ASSERT(A->GetVariables().size() == B->GetVariables().size());

		BLVector2* pPosA = A->GetVariable<BLVector2>("Pos");
		BLInt* pDistA = A->GetVariable<BLInt>("Dist");

		if (pPosA == nullptr || pDistA == nullptr)
			return true;

		BLVector2* pPosB = B->GetVariable<BLVector2>("Pos");
		BLInt* pDistB = B->GetVariable<BLInt>("Dist");

		if (pPosB == nullptr || pDistB == nullptr)
			return true;

		BLBot* pBot = static_cast<BLBot*>(GetOwner());

		return (pBot->GetWorld().GetGrid().Distance(*pPosA, *pPosB) <= pDistA->GetValue() + pDistB->GetValue());
	}

	if (A->GetFactDef()->GetName() == sBotAtPos && B->GetFactDef()->GetName() == sBotAtPos)
	{
		if (A->IsInverted() != B->IsInverted())
			return true;

		ASSERT(A->GetVariables().size() == B->GetVariables().size());

		BLVector2* pPosA = A->GetVariable<BLVector2>("Pos");
		BLVector2* pPosB = B->GetVariable<BLVector2>("Pos");

		if (pPosA == nullptr || pPosB == nullptr)
			return true;

		return *pPosA == *pPosB;
	}

	return true;
}