#include "IBActionDef_PickObject.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "World/BLObject.h"
#include "World/IBInt.h"


IBActionDef_PickObject::IBActionDef_PickObject(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_PickObject::~IBActionDef_PickObject()
{

}


void IBActionDef_PickObject::Define()
{
	AddVariable("Obj");    // BLObject
	AddVariable("ObjPos"); // IBVector2
	AddVariable("Dist");   // IBInt = 1

	AddPreCondition("IBFactDef_ObjectAtPos", "Obj", "ObjPos");
	AddPreCondition("IBFactDef_PropIsPickable", "Obj");
	AddPreCondition("IBFactDef_BotIsEmpty");
	AddPreCondition("IBFactDef_BotNearPos", "ObjPos", "Dist");

	AddPostCondition("IBFactDef_BotHasObject", "Obj");
	AddPostCondition("IBFactDef_PosIsFree", "ObjPos");

	AddCounterPostCondition("IBFactDef_BotIsEmpty");

}

float IBActionDef_PickObject::Evaluate(const IBAction* pAction) const
{
	return 1.f;
}

bool IBActionDef_PickObject::Init(IBAction* pAction)
{
	BLObject* pObj = reinterpret_cast<BLObject*>(pAction->FindVariables("Obj"));
	IBVector2* pObjPos = reinterpret_cast<IBVector2*>(pAction->FindVariables("ObjPos"));
	IBInt* pDist = reinterpret_cast<IBInt*>(pAction->FindVariables("Dist"));

	if (pObjPos == NULL)
	{
		pObjPos = (IBVector2*)&pObj->GetPos();
		pObjPos->SetName(pObj->GetName() + "Pos");
		pAction->SetVariable("ObjPos", pObjPos);
	}

	if (pDist == NULL)
	{
		pDist = new IBInt("NearDist", 1, true);
		pAction->SetVariable("Dist", pDist);
	}

	return (pObj != NULL && pObjPos != NULL && pDist != NULL);
}

bool IBActionDef_PickObject::Start(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	IBVector2* pObjPos = reinterpret_cast<IBVector2*>(pAction->FindVariables("ObjPos"));
	ASSERT(pObjPos != NULL);

	if (pBot->GetState() != BLBot::Idle)
		return false;

	BLBot::BotDir eDir = (pBot->GetWorld().GetGrid().Distance(pBot->GetPos(), *pObjPos) > 0 ? pBot->ComputeDir(pBot->GetPos(), *pObjPos) : pBot->GetDir()) ;

	pBot->SetState(BLBot::Action, eDir, 1.f);
	return true;
}

bool IBActionDef_PickObject::Execute(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);

	if (pBot->HasFinishState())
	{
		BLObject* pObj = static_cast<BLObject*>(pAction->FindVariables("Obj"));
		ASSERT(pObj != NULL);

		pBot->PickProp(reinterpret_cast<BLProp*>(pObj));
		return true;
	}
	else
	{
		return false;
	}
}

bool IBActionDef_PickObject::Finish(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	pBot->SetState(BLBot::Idle, BLBot::Down, 1.f);
	return true;
}

void IBActionDef_PickObject::Destroy(IBAction* pAction)
{
	IBInt* pDist = pAction->FindVariables<IBInt>("Dist");
	if (pDist != NULL)
	{
		delete pDist;
		pAction->SetVariable("Dist", NULL);
	}
}
