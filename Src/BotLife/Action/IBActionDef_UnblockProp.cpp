#include "IBActionDef_UnblockProp.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "World/BLObject.h"
#include "World/IBInt.h"
#include "World/BLDoor.h"


IBActionDef_UnblockProp::IBActionDef_UnblockProp(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_UnblockProp::~IBActionDef_UnblockProp()
{

}

void IBActionDef_UnblockProp::Define()
{
	AddVariable("Obj");    // BLObject
	AddVariable("ObjPos"); // IBVector2
	AddVariable("Dist");   // IBInt = 1

	AddPreCondition("IBFactDef_BotNearPos", true, "Pos", "ObjPos", "Dist", "Dist");
	AddPreCondition("IBFactDef_PropIsBlock", true, "Obj");

	AddPostCondition("IBFactDef_PropIsBlock", false, "Obj");
}

float IBActionDef_UnblockProp::GetCost(const IBAction* pAction) const
{
	return 1.f;
}

bool IBActionDef_UnblockProp::Init(IBAction* pAction) const
{
	return true;
}

bool IBActionDef_UnblockProp::Start(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);

	if (pBot->GetState() != BLBot::Idle)
		return false;

	BLDoor* pObj = pAction->GetVariable<BLDoor>("Obj");
	ASSERT(pObj != nullptr);

	BLBot::BotDir eDir = pBot->ComputeDir(pBot->GetPos(), pObj->GetPos());

	pBot->SetState(BLBot::Action, eDir, 1.f);
	return true;
}

bool IBActionDef_UnblockProp::Execute(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != nullptr);

	if (pBot->HasFinishState())
	{
		BLDoor* pObj = pAction->GetVariable<BLDoor>("Obj");
		ASSERT(pObj != nullptr);

		pObj->Open();

		return true;
	}
	else
	{
		return false;
	}
}

bool IBActionDef_UnblockProp::Finish(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != nullptr);
	pBot->SetState(BLBot::Idle, BLBot::Down, 1.f);
	return true;
}


void IBActionDef_UnblockProp::Destroy(IBAction* pAction) const
{
}
