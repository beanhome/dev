#include "IBActionDef_DropObject.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "World/BLObject.h"
#include "World/IBInt.h"


IBActionDef_DropObject::IBActionDef_DropObject(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_DropObject::~IBActionDef_DropObject()
{

}

void IBActionDef_DropObject::Define()
{
	AddVariable("Obj");    // BLObject
	AddVariable("Pos"); // IBVector2
	AddVariable("Dist");   // IBInt = 1

	AddPreCondition("IBFactDef_PosIsFree", "Pos");
	AddPreCondition("IBFactDef_PropIsPickable", "Obj");
	AddPreCondition("IBFactDef_BotHasObject", "Obj");
	AddPreCondition("IBFactDef_BotNearPos", "Pos", "Dist");

	AddPostCondition("IBFactDef_BotIsEmpty");
	AddPostCondition("IBFactDef_ObjectAtPos", "Obj", "Pos");
}

float IBActionDef_DropObject::Evaluate(const IBAction* pAction) const
{
	return 1.f;
}


bool IBActionDef_DropObject::Init(IBAction* pAction)
{
	BLObject* pObj = reinterpret_cast<BLObject*>(pAction->FindVariables("Obj"));
	IBInt* pDist = reinterpret_cast<IBInt*>(pAction->FindVariables("Dist"));

	if (pDist == NULL)
	{
		pDist = new IBInt("NearDist", 1);
		pAction->SetVariable("Dist", pDist);
	}

	return (pObj != NULL && pDist != NULL);
}

bool IBActionDef_DropObject::Start(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	IBVector2* pPos = reinterpret_cast<IBVector2*>(pAction->FindVariables("Pos"));
	ASSERT(pPos != NULL);

	if (pBot->GetState() != BLBot::Idle)
		return false;

	BLBot::BotDir eDir = (pBot->GetWorld().GetGrid().Distance(pBot->GetPos(), *pPos) > 0 ? pBot->ComputeDir(pBot->GetPos(), *pPos) : pBot->GetDir()) ;

	pBot->SetState(BLBot::Action, eDir, 1.f);
	return true;
}

bool IBActionDef_DropObject::Execute(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	IBVector2* pPos = reinterpret_cast<IBVector2*>(pAction->FindVariables("Pos"));
	ASSERT(pPos != NULL);

	if (pBot->HasFinishState())
	{
		BLObject* pObj = static_cast<BLObject*>(pAction->FindVariables("Obj"));
		ASSERT(pObj != NULL);

		pBot->DropObject(reinterpret_cast<BLProp*>(pObj), *pPos);
		return true;
	}
	else
	{
		return false;
	}
}

bool IBActionDef_DropObject::Finish(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	pBot->SetState(BLBot::Idle, BLBot::Down, 1.f);
	return true;
}

void IBActionDef_DropObject::Destroy(IBAction* pAction)
{
	IBInt* pDist = pAction->FindVariables<IBInt>("Dist");
	if (pDist != NULL)
	{
		delete pDist;
		pAction->SetVariable("Dist", NULL);
	}
}
