#include "IBActionDef_FollowPath.h"
#include "BLBot.h"
#include "Path.h"
#include "IBPlanner.h"
#include "World\IBPath.h"


IBActionDef_FollowPath::IBActionDef_FollowPath(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_FollowPath::~IBActionDef_FollowPath()
{
}

void IBActionDef_FollowPath::Define()
{
	AddVariable("Start");
	AddVariable("Target");
	AddVariable("Path");
	AddVariable("Dist");

	AddPreCondition("IBFactDef_HasValidPath", "Path", "Start", "Target", "Dist");
	AddPreCondition("IBFactDef_BotAtPos", "Start");

	//AddPostCondition("IBFactDef_BotAtPos", "Target");
	AddPostCondition("IBFactDef_BotNearPos", "Target", "Dist");
}

bool IBActionDef_FollowPath::Init(IBAction* pAction)
{
	IBVector2* pStart = static_cast<IBVector2*>(pAction->FindVariables("Start"));
	ASSERT(pStart != NULL);
	IBVector2* pTarget = static_cast<IBVector2*>(pAction->FindVariables("Target"));
	ASSERT(pTarget != NULL);
	IBPath* pPath = static_cast<IBPath*>(pAction->FindVariables("Path"));
	ASSERT(pPath == NULL);

	pPath = new IBPath("MyPath");
	pAction->SetVariable("Path", pPath);

	return true;
}

bool IBActionDef_FollowPath::Start(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	//const BLWorld& oWorld = pBot->GetWorld();

	IBPath* pPath = static_cast<IBPath*>(pAction->FindVariables("Path"));
	ASSERT(pPath != NULL);

	if (pBot->GetState() != BLBot::Idle)
		return false;

	Vector2 vTarget = pPath->PopFront();
	BLBot::BotDir eDir = pBot->ComputeDir(pBot->GetPos(), vTarget);

	pBot->SetState(BLBot::Walk, eDir, 0.5f);
	pBot->SetPos(vTarget);

	return true;
}

bool IBActionDef_FollowPath::Execute(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	IBPath* pPath = static_cast<IBPath*>(pAction->FindVariables("Path"));
	ASSERT(pPath != NULL);

	if (pPath->GetLength() == 0)
		return true;

	if (pBot->GetState() == BLBot::Idle)
	{
		Vector2 vTarget = pPath->PopFront();
		BLBot::BotDir eDir = pBot->ComputeDir(pBot->GetPos(), vTarget);

		pBot->SetState(BLBot::Walk, eDir, 0.5f);
		pBot->SetPos(vTarget);
	}

	return false;
}

bool IBActionDef_FollowPath::Finish(IBAction* pAction)
{
	return true;
}

void IBActionDef_FollowPath::Destroy(IBAction* pAction)
{
	IBPath* pPath = static_cast<IBPath*>(pAction->FindVariables("Path"));
	ASSERT(pPath != NULL);

	delete pPath;
}