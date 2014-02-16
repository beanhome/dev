#include "IBActionDef_FollowPath.h"
#include "BLBot.h"
#include "Path.h"
#include "IBPlanner.h"
#include "World/IBPath.h"


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

float IBActionDef_FollowPath::Evaluate(const IBAction* pAction) const
{
	IBVector2* pStart = static_cast<IBVector2*>(pAction->FindVariables("Start"));
	IBVector2* pTarget = static_cast<IBVector2*>(pAction->FindVariables("Target"));
	IBPath* pPath = static_cast<IBPath*>(pAction->FindVariables("Path"));

	if (pPath == NULL || pStart == NULL || pTarget == NULL)
		return IBPlanner::s_fMaxActionDelay;

	void* pOwner =  m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	const BLWorld& oWorld = pBot->GetWorld();

	int dist = oWorld.GetGrid().Distance(*pStart, *pTarget);
	int ln = pPath->GetLength();

	return ((float)(std::max<int>(dist, ln)) * 0.5f);
}

bool IBActionDef_FollowPath::Init(IBAction* pAction)
{
	IBVector2* pStart = static_cast<IBVector2*>(pAction->FindVariables("Start"));
	IBVector2* pTarget = static_cast<IBVector2*>(pAction->FindVariables("Target"));
	IBPath* pPath = static_cast<IBPath*>(pAction->FindVariables("Path"));

	if (pPath == NULL)
	{
		pPath = new IBPath("MyPath", true);
		pAction->SetVariable("Path", pPath);
	}

	if (pStart == NULL)
	{
		void* pOwner =  m_pPlanner->GetOwner();
		ASSERT(pOwner != NULL);
		BLBot* pBot = static_cast<BLBot*>(pOwner);
		pStart = pBot->GetIBPosAd();
		pAction->SetVariable("Start", pStart);
	}

	return (pStart != NULL && pTarget != NULL && pPath != NULL);
}

bool IBActionDef_FollowPath::Start(IBAction* pAction)
{
 	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);

	IBPath* pPath = static_cast<IBPath*>(pAction->FindVariables("Path"));
	ASSERT(pPath != NULL);

	if (!pBot->HasFinishState())
		return false;

	Vector2 vTarget = pPath->GetFirstStep();
	//LOG("FollowPath::Start (%d %d) -> (%d %d)\n", pBot->GetPos().x, pBot->GetPos().y, vTarget.x, vTarget.y);
	BLBot::BotDir eDir = pBot->ComputeDir(pBot->GetPos(), vTarget);

	pBot->SetState(BLBot::Walk, eDir, 0.5f);

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

	if (pBot->HasFinishState())
	{
		pPath->PopFront();

		pBot->SetPos(pBot->GetTarget());

		if (pPath->GetLength() == 0)
			return true;

		Vector2 vTarget = pPath->GetFirstStep();
		//LOG("FollowPath::Execute (%d %d) -> (%d %d)\n", pBot->GetPos().x, pBot->GetPos().y, vTarget.x, vTarget.y);
		BLBot::BotDir eDir = pBot->ComputeDir(pBot->GetPos(), vTarget);

		pBot->SetState(BLBot::Walk, eDir, 0.5f);
	}

	return false;
}

bool IBActionDef_FollowPath::Abort(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	IBPath* pPath =  pAction->FindVariables<IBPath>("Path");
	ASSERT(pPath != NULL);

	//LOG("FollowPath::Abort \n");

	if (pBot->HasFinishState())
	{
		pPath->PopFront();
		pBot->SetPos(pBot->GetTarget());
		return true;
	}

	return false;
}


bool IBActionDef_FollowPath::Finish(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	//pBot->SetPos(pBot->GetTarget());
	//LOG("FollowPath::Finish \n");
	pBot->SetState(BLBot::Idle, pBot->GetDir(), 0.5f);
	return true;
}

void IBActionDef_FollowPath::Destroy(IBAction* pAction)
{
	//IBPath* pPath = static_cast<IBPath*>(pAction->FindVariables("Path"));
	//ASSERT(pPath != NULL);

	//delete pPath;
}
