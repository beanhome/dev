#include "IBActionDef_PushProp.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "World\BLObject.h"
#include "World\IBInt.h"
#include "World\BLDoor.h"
#include "World\BLProp.h"


IBActionDef_PushProp::IBActionDef_PushProp(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_PushProp::~IBActionDef_PushProp()
{

}

void IBActionDef_PushProp::Define()
{
	AddVariable("Obj");    // BLObject
	AddVariable("PushPos"); // IBVector2
	AddVariable("ObjPos"); // IBVector2
	AddVariable("DestPos"); // IBVector2
	AddVariable("Dist");   // IBInt = 0

	AddPreCondition("IBFactDef_PosIsFree", "DestPos");
	AddPreCondition("IBFactDef_ObjectAtPos", "Obj", "ObjPos");
	AddPreCondition("IBFactDef_PropIsMovable", "Obj");
	AddPreCondition("IBFactDef_BotNearPos", "PushPos", "Dist");
	AddPreCondition("IBFactDef_PosIsFree", "PushPos");

	AddPostCondition("IBFactDef_ObjectAtPos", "Obj", "DestPos");
	AddPostCondition("IBFactDef_PosIsFree", "ObjPos");
}

float IBActionDef_PushProp::Evaluate(const IBAction* pAction) const
{
	return 1.f;
}

Vector2 dir[4] = { Vector2(0,1), Vector2(0,-1), Vector2(1,0), Vector2(-1,0) };

bool IBActionDef_PushProp::Init(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	const BLWorld& oWorld = pBot->GetWorld();

	BLProp* pObj = reinterpret_cast<BLProp*>(pAction->FindVariables("Obj"));
	IBVector2* pObjPos = reinterpret_cast<IBVector2*>(pAction->FindVariables("ObjPos"));
	IBVector2* pDestPos = reinterpret_cast<IBVector2*>(pAction->FindVariables("DestPos"));
	IBVector2* pPushPos = reinterpret_cast<IBVector2*>(pAction->FindVariables("PushPos"));
	IBInt* pDist = reinterpret_cast<IBInt*>(pAction->FindVariables("Dist"));

	if (pObj == NULL && pObjPos == NULL)
		return false;

	if (pObj == NULL)
	{
		pObj = (BLProp*)(oWorld.GetGrid().GetCase(*pObjPos).GetProp());
		pAction->SetVariable("Obj", pObj);
	}

	if (pDestPos == NULL)
	{
		pObjPos = &(pObj->GetPos());
		pAction->SetVariable("ObjPos", pObjPos);

		for (uint i=0 ; i<4 ; ++i)
		{
			Vector2 oDestPos = *pObjPos + dir[i];
			Vector2 pushpos = *pObjPos - dir[i];
			if (oWorld.GetGrid().IsCoordValid(oDestPos) && !oWorld.GetGrid().GetCase(oDestPos).IsPermBlock(pObj)
				&& oWorld.GetGrid().IsCoordValid(pushpos) && !oWorld.GetGrid().GetCase(pushpos).IsPermBlock(pObj))
			{
				pDestPos = new IBVector2("Dest", oDestPos, true);
				pPushPos = new IBVector2("Push", pushpos, true);
				pAction->SetVariable("DestPos", pDestPos);
				pAction->SetVariable("PushPos", pPushPos);
				break;
			}
		}
	}

	if (pObjPos == NULL && pDestPos != NULL)
	{
		BLProp& oObj = *pObj;
		IBVector2& oDestPos = *pDestPos;
		Vector2 pushpos_test = pObj->GetPos() - (oDestPos - pObj->GetPos());
		
		if (oWorld.GetGrid().Distance(oDestPos, pObj->GetPos(), false) == 1
		 && oWorld.GetGrid().IsCoordValid(pushpos_test) && oWorld.GetGrid().GetCase(pushpos_test).IsFree(pObj))
		{
			pObjPos = &pObj->GetPos();
		}
		else
		{
			int iBestDist = -1;
			Vector2 oBestPos;
			for (uint i=0 ; i<4 ; ++i)
			{
				Vector2 pos = oDestPos + dir[i];
				Vector2 pushpos = pos + dir[i];
				if (oWorld.GetGrid().IsCoordValid(pos) && !oWorld.GetGrid().GetCase(pos).IsPermBlock(pObj)
				 && oWorld.GetGrid().IsCoordValid(pushpos) && !oWorld.GetGrid().GetCase(pushpos).IsPermBlock(pObj))
				{
					int iDist = oWorld.GetGrid().Distance(pObj->GetPos(), pos, false);
					if (iBestDist == -1 || iDist < iBestDist)
					{
						iBestDist = iDist;
						oBestPos = pos;
					}
				}
			}

			if (iBestDist > 0)
			{
				pObjPos = new IBVector2("Obj Pos", oBestPos, true);
			}
		}

		pAction->SetVariable("ObjPos", pObjPos);
	}

	if (pPushPos == NULL && pDestPos != NULL && pObjPos != NULL)
	{
		Vector2 offset = *pDestPos - *pObjPos;
		pPushPos = new IBVector2("Push Pos", 0, 0, true);
		*pPushPos = *pObjPos - offset;
		pAction->SetVariable("PushPos", pPushPos);
	}

	if (pDist == NULL)
	{
		pDist = new IBInt("Dist", 0, true);
		pAction->SetVariable("Dist", pDist);
	}

	return (pObj != NULL && pObjPos != NULL && pDestPos != NULL && pPushPos != NULL && pDist != NULL);
}

bool IBActionDef_PushProp::Start(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);

	if (pBot->GetState() != BLBot::Idle)
		return false;

	BLDoor* pObj = static_cast<BLDoor*>(pAction->FindVariables("Obj"));
	ASSERT(pObj != NULL);

	BLBot::BotDir eDir = pBot->ComputeDir(pBot->GetPos(), pObj->GetPos());

	pBot->SetState(BLBot::Push, eDir, 1.f, pObj);
	return true;
}

bool IBActionDef_PushProp::Execute(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);

	if (pBot->HasFinishState())
	{
		BLDoor* pObj = static_cast<BLDoor*>(pAction->FindVariables("Obj"));
		ASSERT(pObj != NULL);
		IBVector2* pDestPos = reinterpret_cast<IBVector2*>(pAction->FindVariables("DestPos"));
		ASSERT(pDestPos != NULL);

		BLSquare& prev_sq = pBot->GetWorld().GetGrid().GetCase(pObj->GetPos());
		BLSquare& new_sq = pBot->GetWorld().GetGrid().GetCase(*pDestPos);
		pObj->SetPos(*pDestPos);
		prev_sq.SetProp(NULL);
		new_sq.SetProp(pObj);

		//pBot->SetPos(pBot->GetTarget());
		pBot->SetPos(prev_sq.GetPos());

		return true;
	}
	else
	{
		return false;
	}
}

bool IBActionDef_PushProp::Finish(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	pBot->SetState(BLBot::Idle, BLBot::Down, 1.f);
	return true;
}


void IBActionDef_PushProp::Destroy(IBAction* pAction)
{
}
