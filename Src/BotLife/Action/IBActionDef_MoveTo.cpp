#include "IBActionDef_MoveTo.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "Action/BLAction.h"
#include "World/BLPath.h"
#include "World/BLInt.h"
#include "NavAStar.h"
#include "Timer.h"

float IBActionDef_MoveTo::s_fFindPathStepDelay = 0.001f;

IBActionDef_MoveTo::IBActionDef_MoveTo(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_MoveTo::~IBActionDef_MoveTo()
{
}

void IBActionDef_MoveTo::Define()
{
	AddVariable("Target");
	AddVariable("Dist");
	AddVariable("Path");

	AddPostCondition("IBFactDef_BotNearPos", true, "Pos", "Target", "Dist", "Dist");
}

float IBActionDef_MoveTo::GetCost(const IBAction* pAction) const
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

void	 IBActionDef_MoveTo::CreateOwnedVariables(IBAction* pAction) const
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

bool IBActionDef_MoveTo::Init(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	const BLWorld& oWorld = pBot->GetWorld();

	ASSERT(pAction->GetUserData() == nullptr);
	Navigation<BLSquare>* pNav = new NavAStar<BLSquare>(oWorld.GetGrid());
	pAction->SetUserData(pNav);

	return true;
}

void IBActionDef_MoveTo::Update(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);

	Navigation<BLSquare>* pNav = static_cast<Navigation<BLSquare>*>(pAction->GetUserData());
	ASSERT(pNav != nullptr);

	BLVector2* pTarget = pAction->GetVariable<BLVector2>("Target");
	BLInt* pDist = pAction->GetVariable<BLInt>("Dist");
	BLPath* pPath = pAction->GetVariable<BLPath>("Path");
	ASSERT(pPath != nullptr);

	if (pTarget == nullptr && pDist == nullptr)
		return;

	if (pPath->IsValid() && !pPath->InOnPath(pBot->GetPos()))
	{
		ASSERT(pNav->GetState() == Navigation<BLSquare>::FP_Succeed);
		pPath->Clear();
	}

	if (!pPath->IsValid())
	{
		if (pNav->GetState() == Navigation<BLSquare>::FP_Find)
			pNav->FindPathStep(pBot->GetPos(), *pTarget, pDist->GetValue(), *pPath);
		else
			pNav->FindPathInit(pBot->GetPos(), *pTarget, pDist->GetValue(), *pPath);
	}
}

void IBActionDef_MoveTo::Destroy(IBAction* pAction) const
{
	ASSERT(pAction->GetUserData() != nullptr);

	delete (Navigation<BLSquare>*)pAction->GetUserData();
	pAction->SetUserData(nullptr);
}


bool IBActionDef_MoveTo::Start(IBAction* pAction) const
{
 	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);

	BLVector2* pTarget = pAction->GetVariable<BLVector2>("Target");
	ASSERT(pTarget != nullptr);
	BLInt* pDist = pAction->GetVariable<BLInt>("Dist");
	ASSERT(pDist != nullptr);
	BLPath* pPath = pAction->GetVariable<BLPath>("Path");
	ASSERT(pPath != nullptr);

	Navigation<BLSquare>* pNav = static_cast<Navigation<BLSquare>*>(pAction->GetUserData());
	if (pNav->GetState() == Navigation<BLSquare>::FP_Create)
		pNav->FindPathInit(pBot->GetPos(), *pTarget, pDist->GetValue(), *pPath);

	return true;
}

bool IBActionDef_MoveTo::Execute(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != nullptr);
	BLPath* pPath = pAction->GetVariable<BLPath>("Path");
	ASSERT(pPath != nullptr);
	BLVector2* pTarget = pAction->GetVariable<BLVector2>("Target");
	ASSERT(pTarget != nullptr);
	BLInt* pDist = pAction->GetVariable<BLInt>("Dist");
	ASSERT(pDist != nullptr);

	Navigation<BLSquare>* pNav = static_cast<Navigation<BLSquare>*>(pAction->GetUserData());
	ASSERT(pNav != nullptr);

	if (!pPath->IsValid())
	{
		LOG("Find Path step :");
		double start = Timer::Get();
		do
		{
			pNav->FindPathStep(pBot->GetPos(), *pTarget, pDist->GetValue(), *pPath);
			LOG(" *");
		} while (Timer::Get() < start + s_fFindPathStepDelay && !pPath->IsValid());

		LOG("\n");

		if (pPath->IsValid())
		{
			pPath->ResetStep();
			Vector2 vTarget = pPath->GetFirstStep();
			//LOG("FollowPath::Start (%d %d) -> (%d %d)\n", pBot->GetPos().x, pBot->GetPos().y, vTarget.x, vTarget.y);
			BLBot::BotDir eDir = pBot->ComputeDir(pBot->GetPos(), vTarget);
			pBot->SetState(BLBot::Walk, eDir, 0.5f);
		}
	}
	else if (pBot->HasFinishState())
	{
		pBot->SetPos(pBot->GetTarget());

		if (pPath->NextStep())
		{
			Vector2 vTarget = pPath->GetCurrentStep();
			//LOG("MoveTo::Execute (%d %d) -> (%d %d)\n", pBot->GetPos().x, pBot->GetPos().y, vTarget.x, vTarget.y);
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

bool IBActionDef_MoveTo::Abort(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != nullptr);
	BLPath* pPath = pAction->GetVariable<BLPath>("Path");
	ASSERT(pPath != nullptr);

	//LOG("MoveTo::Abort \n");

	if (pBot->HasFinishState())
	{
		pPath->PopFront();
		pBot->SetPos(pBot->GetTarget());
		return true;
	}

	return false;
}


bool IBActionDef_MoveTo::Finish(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != nullptr);
	//pBot->SetPos(pBot->GetTarget());
	//LOG("MoveTo::Finish \n");
	pBot->SetState(BLBot::Idle, pBot->GetDir(), 0.5f);
	return true;
}
