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

	AddPreCondition("IBFactDef_BotNearPos", "ObjPos", "Dist");
	AddPreCondition("IBFactDef_PropIsBlock", "Obj");

	AddPostCondition("IBFactDef_PropIsUnblock", "Obj");
}

float IBActionDef_UnblockProp::Evaluate(const IBAction* pAction) const
{
	return 1.f;
}

bool IBActionDef_UnblockProp::Init(IBAction* pAction)
{
	BLObject* pObj = reinterpret_cast<BLObject*>(pAction->FindVariables("Obj"));
	ASSERT(pObj != NULL);
	IBVector2* pObjPos = reinterpret_cast<IBVector2*>(pAction->FindVariables("ObjPos"));
	ASSERT(pObjPos == NULL || pObjPos == &pObj->GetPos());
	IBInt* pDist = reinterpret_cast<IBInt*>(pAction->FindVariables("Dist"));
	ASSERT(pDist == NULL);

	if (pObjPos == NULL)
	{
		pObjPos = (IBVector2*)&pObj->GetPos();
		pObjPos->SetName(pObj->GetName() + "Pos");
		pAction->SetVariable("ObjPos", pObjPos);
	}

	pDist = new IBInt("Dist = 1", 1);
	pAction->SetVariable("Dist", pDist);

	return true;
}

bool IBActionDef_UnblockProp::Start(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);

	if (pBot->GetState() != BLBot::Idle)
		return false;

	BLDoor* pObj = static_cast<BLDoor*>(pAction->FindVariables("Obj"));
	ASSERT(pObj != NULL);

	BLBot::BotDir eDir = pBot->ComputeDir(pBot->GetPos(), pObj->GetPos());

	pBot->SetState(BLBot::Action, eDir, 1.f);
	return true;
}

bool IBActionDef_UnblockProp::Execute(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);

	if (pBot->HasFinishState())
	{
		BLDoor* pObj = static_cast<BLDoor*>(pAction->FindVariables("Obj"));
		ASSERT(pObj != NULL);

		pObj->Open();

		return true;
	}
	else
	{
		return false;
	}
}

bool IBActionDef_UnblockProp::Finish(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	pBot->SetState(BLBot::Idle, BLBot::Down, 1.f);
	return true;
}


void IBActionDef_UnblockProp::Destroy(IBAction* pAction)
{
	IBInt* pDist = pAction->FindVariables<IBInt>("Dist");
	if (pDist != NULL)
	{
		delete pDist;
		pAction->SetVariable("Dist", NULL);
	}
}
