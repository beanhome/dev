#include "IBActionDef_PushProp.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "World/BLObject.h"
#include "World/BLInt.h"
#include "World/BLVector2.h"
#include "World/BLDoor.h"
#include "World/BLProp.h"
#include "BLAction.h"


IBActionDef_PushProp::IBActionDef_PushProp(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_PushProp::~IBActionDef_PushProp()
{

}

void IBActionDef_PushProp::Define()
{
	AddVariable("Obj");
	AddVariable("PushPos");
	AddVariable("ObjPos");
	AddVariable("DestPos");
	AddVariable("Dist");

	AddPreCondition("IBFactDef_PosIsFree", true, "DestPos");
	AddPreCondition("IBFactDef_ObjectAtPos", true, "Obj", "Obj", "Pos", "ObjPos");
	AddPreCondition("IBFactDef_PropIsMovable", true, "Obj");
	AddPreCondition("IBFactDef_BotNearPos", true, "Pos", "PushPos", "Dist", "Dist");
	AddPreCondition("IBFactDef_PosIsFree", true, "PushPos");

	AddPostCondition("IBFactDef_ObjectAtPos", true, "Obj", "Obj", "Pos", "DestPos");
	AddPostCondition("IBFactDef_PosIsFree", true, "ObjPos");

	AddPostCondition("IBFactDef_PosIsFree", false, "DestPos");
}

float IBActionDef_PushProp::GetCost(const IBAction* pAction) const
{
	return 1.f;
}

Vector2 dir[4] = { Vector2(0,1), Vector2(0,-1), Vector2(1,0), Vector2(-1,0) };

void	 IBActionDef_PushProp::CreateOwnedVariables(IBAction* pAction) const
{
	BLAction* pBLAction = dynamic_cast<BLAction*>(pAction);
	ASSERT(pBLAction != nullptr);

	BLProp* pObj = pAction->GetVariable<BLProp>("Obj");
	if (pObj == nullptr)
		return;

	BLVector2* pDestPos = pAction->GetVariable<BLVector2>("DestPos");
	if (pDestPos == nullptr)
		return;

	if (pAction->GetVariable("ObjPos")->GetUserData() == nullptr)
	{
		Vector2 diff = *pDestPos - pObj->GetPos();
		if (abs(diff.x) + abs(diff.y) == 1)
		{
			BLVector2* pObjPos = new BLVector2("ObjPos");
			pObjPos->Set(pObj->GetPos());
			pBLAction->AddOwnedObject(pObjPos);
			pAction->SetVariable("ObjPos", pObjPos->GetName(), (void*)pObjPos);
		}
	}

	if (pAction->GetVariable("PushPos")->GetUserData() == nullptr
	 && pAction->GetVariable("ObjPos")->GetUserData() == nullptr)
	{
		BLVector2* pPushPos = new BLVector2("PushPos");
		Vector2 diff = *pDestPos - pObj->GetPos();
		pPushPos->Set(pObj->GetPos() - diff);
		pBLAction->AddOwnedObject(pPushPos);
		pAction->SetVariable("PushPos", pPushPos->GetName(), (void*)pPushPos);
	}

	if (pAction->GetVariable("Dist")->GetUserData() == nullptr)
	{
		BLInt* pDist = new BLInt(0);
		pBLAction->AddOwnedObject(pDist);
		pAction->SetVariable("Dist", pDist->GetName(), (void*)pDist);
	}
}

void	 IBActionDef_PushProp::CompleteVariables(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);

	if (pAction->GetVariable("ObjPos")->GetUserData() == nullptr)
	{
		BLVector2* pDestPos = pAction->GetVariable<BLVector2>("DestPos");
		if (pDestPos == nullptr)
			return;

		for (int i = 0; i < 4; ++i)
		{
			Vector2 pos = *pDestPos + dir[i];
			const BLVector2& oObjPos = pBot->GetWorld().GetGrid().GetCase(pos).GetPos();
			pAction->AddPotentialVariable("DestPos", oObjPos.GetName(), (void*)&oObjPos);
		}
	}
}

bool IBActionDef_PushProp::Start(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);

	if (pBot->GetState() != BLBot::Idle)
		return false;

	BLDoor* pObj = pAction->GetVariable<BLDoor>("Obj");
	ASSERT(pObj != NULL);

	BLBot::BotDir eDir = pBot->ComputeDir(pObj->GetPos());

	pBot->SetState(BLBot::Push, eDir, 1.f, pObj);
	
	return true;
}

/*
bool IBActionDef_PushProp::Execute(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);

	if (pBot->HasFinishState())
	{
		BLDoor* pObj = pAction->GetVariable<BLDoor>("Obj");
		ASSERT(pObj != NULL);
		BLVector2* pDestPos = pAction->GetVariable<BLVector2>("DestPos");
		ASSERT(pDestPos != NULL);

		BLSquare& prev_sq = pBot->GetWorld().GetGrid().GetCase(pObj->GetPos());
		BLSquare& new_sq = pBot->GetWorld().GetGrid().GetCase(*pDestPos);
		pObj->SetPos(*pDestPos);
		prev_sq.SetProp(NULL);
		new_sq.SetProp(pObj);

		pBot->SetPos(prev_sq.GetPos());

		return true;
	}
	else
	{
		return false;
	}
}
*/

/*
bool IBActionDef_PushProp::Finish(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	pBot->SetState(BLBot::Idle, BLBot::Down, 1.f);
	return true;
}
*/


void IBActionDef_PushProp::Destroy(IBAction* pAction) const
{
}
