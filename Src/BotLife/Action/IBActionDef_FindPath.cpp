#include "IBActionDef_FindPath.h"
#include "World\IBPath.h"
#include "IBPlanner.h"
#include "BLBot.h"
#include "NavAStar.h"


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

	AddPostCondition("IBFactDef_HasValidPath", "Path", "Start", "Target");
}

bool IBActionDef_FindPath::Start(IBAction* pAction)
{
	IBVector2* pStart = static_cast<IBVector2*>(pAction->FindVariables("Start"));
	ASSERT(pStart != NULL);
	IBVector2* pTarget = static_cast<IBVector2*>(pAction->FindVariables("Target"));
	ASSERT(pTarget != NULL);
	IBPath* pPath = static_cast<IBPath*>(pAction->FindVariables("Path"));

	if (pPath != NULL)
		delete pPath;

	pAction->SetVariable("Path", new IBPath("MyPath"));

	m_pNavigation->FindPathInit(*pStart, *pTarget, 0, *pPath);
	
	return true;
}

bool IBActionDef_FindPath::Execute(IBAction* pAction)
{
	IBVector2* pStart = static_cast<IBVector2*>(pAction->FindVariables("Start"));
	ASSERT(pStart != NULL);
	IBVector2* pTarget = static_cast<IBVector2*>(pAction->FindVariables("Target"));
	ASSERT(pTarget != NULL);
	IBPath* pPath = static_cast<IBPath*>(pAction->FindVariables("Path"));
	ASSERT(pPath != NULL);

	Navigation<BLSquare>::State state = m_pNavigation->FindPathStep(*pStart, *pTarget, 0, *pPath);

	LOG("Path : ");
	pPath->Print();

	return (state != Navigation<BLSquare>::FP_Find);
}

bool IBActionDef_FindPath::Finish(IBAction* pAction)
{
	/*
	IBVector2* pStart = static_cast<IBVector2*>(pAction->FindVariables("Start"));
	ASSERT(pStart != NULL);
	IBVector2* pTarget = static_cast<IBVector2*>(pAction->FindVariables("Target"));
	ASSERT(pTarget != NULL);
	IBPath* pPath = static_cast<IBPath*>(pAction->FindVariables("Path"));
	ASSERT(pPath != NULL);
	*/

	return true;
}

