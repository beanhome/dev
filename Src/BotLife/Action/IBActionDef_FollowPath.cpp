#include "IBActionDef_FollowPath.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "Action/BLAction.h"
#include "World/BLPath.h"


IBActionDef_FollowPath::IBActionDef_FollowPath(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_FollowPath::~IBActionDef_FollowPath()
{
}

void IBActionDef_FollowPath::Define()
{
	AddVariable("Target");
	AddVariable("Dist");
	AddVariable("Path");

	AddPreCondition("IBFactDef_HasValidPath", true, "Path", "Path", "Target", "Target", "Dist", "Dist");
	AddPostCondition("IBFactDef_BotNearPos", true, "Pos", "Target", "Dist", "Dist");
}

float IBActionDef_FollowPath::GetCost(const IBAction* pAction) const
{
	BLVector2* pTarget = pAction->GetVariable<BLVector2>("Target");
	ASSERT(pTarget != nullptr);
	BLPath* pPath = pAction->GetVariable<BLPath>("Path");
	ASSERT(pPath != nullptr);

	if (pPath == nullptr || pTarget == nullptr)
		return IBPlanner::s_fMaxActionDelay;

	void* pOwner =  m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	const BLWorld& oWorld = pBot->GetWorld();

	int dist = oWorld.GetGrid().Distance(pBot->GetPos(), *pTarget);
	int ln = pPath->GetLength();

	return ((float)(std::max<int>(dist, ln)) * 0.5f);
}

void	 IBActionDef_FollowPath::CreateOwnedVariables(IBAction* pAction) const
{
	BLAction* pBLAction = dynamic_cast<BLAction*>(pAction);
	ASSERT(pBLAction != nullptr);

	if (pAction->GetVariable("Path")->GetUserData() == nullptr)
	{
		BLPath* pPath = new BLPath("path");
		pBLAction->AddOwnedObject(pPath);
		pAction->SetVariable("Path", pPath->GetName(), (void*)pPath);
	}
}

bool IBActionDef_FollowPath::Start(IBAction* pAction) const
{
 	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);

	BLPath* pPath = pAction->GetVariable<BLPath>("Path");
	ASSERT(pPath != nullptr);

	//if (!pBot->HasFinishState())
	//	return false;

	pPath->ResetStep();

	Vector2 vTarget = pPath->GetFirstStep();
	//LOG("FollowPath::Start (%d %d) -> (%d %d)\n", pBot->GetPos().x, pBot->GetPos().y, vTarget.x, vTarget.y);
	BLBot::BotDir eDir = pBot->ComputeDir(vTarget);

	pBot->SetState(BLBot::Walk, eDir, 0.5f);

	return true;
}

/*
bool IBActionDef_FollowPath::Execute(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != nullptr);
	BLPath* pPath = pAction->GetVariable<BLPath>("Path");
	ASSERT(pPath != nullptr);

	if (pBot->HasFinishState())
	{
		pBot->SetPos(pBot->GetTarget());

		if (pPath->NextStep())
		{
			Vector2 vTarget = pPath->GetCurrentStep();
			//LOG("FollowPath::Execute (%d %d) -> (%d %d)\n", pBot->GetPos().x, pBot->GetPos().y, vTarget.x, vTarget.y);
			BLBot::BotDir eDir = pBot->ComputeDir(pBot->GetPos(), vTarget);

			pBot->SetState(BLBot::Walk, eDir, 0.5f);
		}
		else
		{
			return true;
		}
	}

	return false;
}
*/

void IBActionDef_FollowPath::Interrupt(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != nullptr);
	BLPath* pPath = pAction->GetVariable<BLPath>("Path");
	ASSERT(pPath != nullptr);

	//LOG("FollowPath::Abort \n");

	/*
	if (pBot->HasFinishState())
	{
		pPath->PopFront();
		pBot->SetPos(pBot->GetTarget());
		return true;
	}
	*/
}

/*
bool IBActionDef_FollowPath::Finish(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != nullptr);
	//pBot->SetPos(pBot->GetTarget());
	//LOG("FollowPath::Finish \n");
	pBot->SetState(BLBot::Idle, pBot->GetDir(), 0.5f);
	return true;
}
*/

void IBActionDef_FollowPath::Destroy(IBAction* pAction) const
{
}
