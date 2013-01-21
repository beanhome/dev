#include "IBActionDef_FindPath.h"
#include "World\IBPath.h"
#include "IBPlanner.h"
#include "BLBot.h"
#include "NavAStar.h"
#include "Timer.h"
#include "World\IBInt.h"
#include "World\BLProp.h"


IBActionDef_FindPath::IBActionDef_FindPath(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{
	void* pOwner = pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	const BLWorld& oWorld = pBot->GetWorld();

	m_pNavigation = new NavAStar<BLSquare>(oWorld.GetGrid(), false);
}

IBActionDef_FindPath::~IBActionDef_FindPath()
{
	delete m_pNavigation;
}

void IBActionDef_FindPath::Define()
{
	AddVariable("Start");
	AddVariable("Target");
	AddVariable("Path");
	AddVariable("Dist");

	AddPostCondition("IBFactDef_HasValidPath", "Path", "Start", "Target", "Dist");
}

bool IBActionDef_FindPath::Start(IBAction* pAction)
{
	IBVector2* pStart = pAction->FindVariables<IBVector2>("Start");
	ASSERT(pStart != NULL);
	IBVector2* pTarget = pAction->FindVariables<IBVector2>("Target");
	ASSERT(pTarget != NULL);
	IBPath* pPath = pAction->FindVariables<IBPath>("Path");
	ASSERT(pPath != NULL);
	IBInt* pDist = pAction->FindVariables<IBInt>("Dist");
	ASSERT(pDist != NULL);

	m_pNavigation->FindPathInit(*pStart, *pTarget, pDist->GetValue(), *pPath);
	
	return true;
}

bool IBActionDef_FindPath::Execute(IBAction* pAction)
{
	IBVector2* pStart = pAction->FindVariables<IBVector2>("Start");
	ASSERT(pStart != NULL);
	IBVector2* pTarget = pAction->FindVariables<IBVector2>("Target");
	ASSERT(pTarget != NULL);
	IBPath* pPath = pAction->FindVariables<IBPath>("Path");
	ASSERT(pPath != NULL);
	IBInt* pDist = pAction->FindVariables<IBInt>("Dist");
	ASSERT(pDist != NULL);

	Navigation<BLSquare>::State state = Navigation<BLSquare>::FP_Find;
	
	LOG("Find Path step :");
	double start = Timer::Get();
	while (Timer::Get() < start + 0.001 && state == Navigation<BLSquare>::FP_Find)
	{
		state = m_pNavigation->FindPathStep(*pStart, *pTarget, pDist->GetValue(), *pPath);
		LOG(" *");
	}
	LOG("\n");

	return (state != Navigation<BLSquare>::FP_Find);
}

bool IBActionDef_FindPath::Finish(IBAction* pAction)
{
	IBVector2* pStart = pAction->FindVariables<IBVector2>("Start");
	ASSERT(pStart != NULL);
	IBVector2* pTarget = pAction->FindVariables<IBVector2>("Target");
	ASSERT(pTarget != NULL);
	IBPath* pPath = pAction->FindVariables<IBPath>("Path");
	ASSERT(pPath != NULL);
	//IBInt* pDist = pAction->FindVariables<IBInt>("Dist");
	//ASSERT(pDist != NULL);

	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	const BLWorld& oWorld = pBot->GetWorld();

	for (uint i=0 ; i<pPath->GetLength() ; ++i)
	{
		const BLSquare& sq = oWorld.GetGrid().GetCase((*pPath)[i]);
		if (sq.GetProp() != NULL && sq.GetProp()->IsTempBlock())
		{
			m_pPlanner->AddPreCond(pAction, "IBFactDef_PropIsUnblock", (IBObject*)sq.GetProp());
		}
	}

	return oWorld.TestPath(*pPath);
}

