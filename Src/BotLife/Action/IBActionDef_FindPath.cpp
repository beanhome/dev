#include "IBActionDef_FindPath.h"
#include "World/BLPath.h"
#include "IBPlanner.h"
#include "BLBot.h"
#include "NavAStar.h"
#include "Timer.h"
#include "World/BLInt.h"
#include "World/BLVector2.h"
#include "World/BLProp.h"

float IBActionDef_FindPath::s_fFindPathStepDelay = 0.001f;

IBActionDef_FindPath::IBActionDef_FindPath(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{
}

IBActionDef_FindPath::~IBActionDef_FindPath()
{
}

void IBActionDef_FindPath::Define()
{
	AddVariable("Target");
	AddVariable("Dist");
	AddVariable("Path");

	AddPostCondition("IBFactDef_HasValidPath", true, "Target", "Target", "Path", "Path", "Dist", "Dist");
}


float IBActionDef_FindPath::GetCost(const IBAction* pAction) const
{	
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	const BLWorld& oWorld = pBot->GetWorld();

	BLVector2* pTarget = pAction->GetVariable<BLVector2>("Target");
	ASSERT(pTarget != nullptr);

	if (pTarget == nullptr)
		return IBPlanner::s_fMaxActionDelay;

	// TODO: Improve this evaluation depands on the StepDelay of the planner and the findpathspeed
	return (float)(oWorld.GetGrid().Distance(pBot->GetPos(), *pTarget)) * s_fFindPathStepDelay;
}

bool IBActionDef_FindPath::Start(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	const BLWorld& oWorld = pBot->GetWorld();

	BLVector2* pTarget = pAction->GetVariable<BLVector2>("Target");
	ASSERT(pTarget != nullptr);
	BLPath* pPath = pAction->GetVariable<BLPath>("Path");
	ASSERT(pPath != nullptr);
	BLInt* pDist = pAction->GetVariable<BLInt>("Dist");
	ASSERT(pDist != nullptr);

	if (pAction->GetUserData() != nullptr)
		delete (Navigation<BLSquare>*)pAction->GetUserData();

	Navigation<BLSquare>* pNav = new NavAStar<BLSquare>(oWorld.GetGrid());
	pNav->FindPathInit(pBot->GetPos(), *pTarget, pDist->GetValue(), *pPath);

	pAction->SetUserData(pNav);

	return true;
}

bool IBActionDef_FindPath::Execute(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	const BLWorld& oWorld = pBot->GetWorld();

	BLVector2* pTarget = pAction->GetVariable<BLVector2>("Target");
	ASSERT(pTarget != nullptr);
	BLPath* pPath = pAction->GetVariable<BLPath>("Path");
	ASSERT(pPath != nullptr);
	BLInt* pDist = pAction->GetVariable<BLInt>("Dist");
	ASSERT(pDist != nullptr);

	Navigation<BLSquare>* pNav = static_cast<Navigation<BLSquare>*>(pAction->GetUserData());
	Navigation<BLSquare>::State state = Navigation<BLSquare>::FP_Find;
	
	LOG("Find Path step :");
	double start = Timer::Get();
	while (Timer::Get() < start + s_fFindPathStepDelay && state == Navigation<BLSquare>::FP_Find)
	{
		pNav->FindPathStep(pBot->GetPos(), *pTarget, pDist->GetValue(), *pPath);
		state = pNav->GetState();
		LOG(" *");
	}
	LOG("\n");

	return (state != Navigation<BLSquare>::FP_Find);
}

bool IBActionDef_FindPath::Finish(IBAction* pAction) const
{
	BLVector2* pTarget = pAction->GetVariable<BLVector2>("Target");
	ASSERT(pTarget != nullptr);
	BLPath* pPath = pAction->GetVariable<BLPath>("Path");
	ASSERT(pPath != nullptr);
	//BLInt* pDist = pAction->GetVariable<BLInt>("Dist");
	//ASSERT(pDist != nullptr);

	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	const BLWorld& oWorld = pBot->GetWorld();

	/*
	for (uint i=0 ; i<pPath->GetLength() ; ++i)
	{
		const BLSquare& sq = oWorld.GetGrid().GetCase((*pPath)[i]);
		if (sq.GetProp() != nullptr && sq.GetProp()->IsBlock())
		{
			m_pPlanner->AddPreCond(pAction, "IBFactDef_PropIsUnblock", (IBObject*)sq.GetProp());
		}
	}
	*/

	if (pAction->GetUserData() != nullptr)
	{
		delete (Navigation<BLSquare>*)pAction->GetUserData();
		pAction->SetUserData(nullptr);
	}

	pBot->SetState(BLBot::Idle);

	return oWorld.TestPath(*pPath);
}

void IBActionDef_FindPath::Destroy(IBAction* pAction) const
{
}
