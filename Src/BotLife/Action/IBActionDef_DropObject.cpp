#include "IBActionDef_DropObject.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "World/BLObject.h"
#include "World/BLProp.h"
#include "World/BLInt.h"
#include "World/BLVector2.h"
#include "Action/BLAction.h"


IBActionDef_DropObject::IBActionDef_DropObject(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_DropObject::~IBActionDef_DropObject()
{

}

void IBActionDef_DropObject::Define()
{
	AddVariable("Obj");
	AddVariable("Pos");
	AddVariable("Dist");

	AddPreCondition("IBFactDef_PosIsFree", true, "Pos");
	AddPreCondition("IBFactDef_PropIsPickable", true, "Obj");
	AddPreCondition("IBFactDef_BotHasObject", true, "Obj");
	AddPreCondition("IBFactDef_BotNearPos", true, "Pos", "Pos", "Dist", "Dist");

	AddPostCondition("IBFactDef_BotIsEmpty", true);
	AddPostCondition("IBFactDef_ObjectAtPos", true, "Obj", "Obj", "Pos", "Pos");
	AddPostCondition("IBFactDef_PosIsFree", false, "Pos");
}

float IBActionDef_DropObject::GetCost(const IBAction* pAction) const
{
	return 1.f;
}

void	 IBActionDef_DropObject::CreateOwnedVariables(IBAction* pAction) const
{
	BLAction* pBLAction = dynamic_cast<BLAction*>(pAction);
	ASSERT(pBLAction != nullptr);

	BLProp* pObj = pAction->GetVariable<BLProp>("Obj");
	if (pObj == nullptr)
		return;

	if (pAction->GetVariable("Dist")->GetUserData() == nullptr)
	{
		BLInt* pDist = new BLInt(0);
		pBLAction->AddOwnedObject(pDist);
		pAction->SetVariable("Dist", pDist->GetName(), (void*)pDist);
	}
}

bool IBActionDef_DropObject::Init(IBAction* pAction) const
{
	return true;
}

bool IBActionDef_DropObject::Start(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	BLVector2* pPos = pAction->GetVariable<BLVector2>("Pos");
	ASSERT(pPos != NULL);

	if (pBot->GetState() != BLBot::Idle)
		return false;

	BLBot::BotDir eDir = (pBot->GetWorld().GetGrid().Distance(pBot->GetPos(), *pPos) > 0 ? pBot->ComputeDir(pBot->GetPos(), *pPos) : pBot->GetDir()) ;

	pBot->SetState(BLBot::Action, eDir, 1.f);
	return true;
}

bool IBActionDef_DropObject::Execute(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	BLVector2* pPos = pAction->GetVariable<BLVector2>("Pos");
	ASSERT(pPos != NULL);

	if (pBot->HasFinishState())
	{
		BLProp* pObj = pAction->GetVariable<BLProp>("Obj");
		ASSERT(pObj != NULL);

		pBot->DropObject(pObj, *pPos);
		return true;
	}
	else
	{
		return false;
	}
}

bool IBActionDef_DropObject::Finish(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	pBot->SetState(BLBot::Idle, BLBot::Down, 1.f);
	return true;
}

void IBActionDef_DropObject::Destroy(IBAction* pAction) const
{
}
