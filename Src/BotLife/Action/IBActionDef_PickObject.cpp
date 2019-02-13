#include "IBActionDef_PickObject.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "World/BLObject.h"
#include "World/BLProp.h"
#include "World/BLInt.h"
#include "World/BLVector2.h"
#include "Action/BLAction.h"


IBActionDef_PickObject::IBActionDef_PickObject(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_PickObject::~IBActionDef_PickObject()
{

}


void IBActionDef_PickObject::Define()
{
	AddVariable("Obj");
	AddVariable("ObjPos");
	AddVariable("Dist");

	AddPreCondition("IBFactDef_ObjectAtPos", true, "Obj", "Obj", "Pos", "ObjPos");
	AddPreCondition("IBFactDef_PropIsPickable", true, "Obj");
	AddPreCondition("IBFactDef_BotIsEmpty", true);
	AddPreCondition("IBFactDef_BotNearPos", true, "Pos", "ObjPos", "Dist", "Dist");

	AddPostCondition("IBFactDef_BotHasObject", true, "Obj");
	AddPostCondition("IBFactDef_PosIsFree", true, "ObjPos");
	AddPostCondition("IBFactDef_BotIsEmpty", false);
}

float IBActionDef_PickObject::GetCost(const IBAction* pAction) const
{
	return 1.f;
}

void	 IBActionDef_PickObject::CreateOwnedVariables(IBAction* pAction) const
{
	BLAction* pBLAction = dynamic_cast<BLAction*>(pAction);
	ASSERT(pBLAction != nullptr);

	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);

	BLProp* pObj = pAction->GetVariable<BLProp>("Obj");

	BLVector2* pObjPos = pAction->GetVariable<BLVector2>("ObjPos");

	if (pObj != nullptr && pObjPos == nullptr)
	{
		BLVector2* pObjPos = new BLVector2("ObjPos");
		pObjPos->Set(pObj->GetPos());
		pBLAction->AddOwnedObject(pObjPos);
		pAction->SetVariable("ObjPos", pObjPos->GetName(), (void*)pObjPos);
	}

	if (pObj == nullptr && pObjPos != nullptr)
	{
		pObj = pBot->GetWorld().GetGrid().GetCase(*pObjPos).GetProp();
		pAction->SetVariable("Obj", pObj->GetName(), (void*)pObj);
	}

	if (pAction->GetVariable("Dist")->GetUserData() == nullptr)
	{
		BLInt* pDist = new BLInt(0);
		pBLAction->AddOwnedObject(pDist);
		pAction->SetVariable("Dist", pDist->GetName(), (void*)pDist);
	}
}

bool IBActionDef_PickObject::Init(IBAction* pAction) const
{
	/*
	BLObject* pObj = pAction->GetVariable<BLObject>("Obj");
	BLVector2* pObjPos = pAction->GetVariable<BLVector2>("ObjPos");
	BLInt* pDist = pAction->GetVariable<BLInt>("Dist");
	*/

	return true;
}

bool IBActionDef_PickObject::Start(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);

	BLVector2* pObjPos = pAction->GetVariable<BLVector2>("ObjPos");

	if (pBot->GetState() != BLBot::Idle)
		return false;

	BLBot::BotDir eDir = (pBot->GetWorld().GetGrid().Distance(pBot->GetPos(), *pObjPos) > 0 ? pBot->ComputeDir(pBot->GetPos(), *pObjPos) : pBot->GetDir()) ;

	pBot->SetState(BLBot::Action, eDir, 1.f);
	return true;
}

bool IBActionDef_PickObject::Execute(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);

	if (pBot->HasFinishState())
	{
		BLObject* pObj = pAction->GetVariable<BLObject>("Obj");
		ASSERT(pObj != NULL);

		pBot->PickProp(reinterpret_cast<BLProp*>(pObj));
		return true;
	}
	else
	{
		return false;
	}
}

bool IBActionDef_PickObject::Finish(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	pBot->SetState(BLBot::Idle, BLBot::Down, 1.f);
	return true;
}

void IBActionDef_PickObject::Destroy(IBAction* pAction) const
{
}
