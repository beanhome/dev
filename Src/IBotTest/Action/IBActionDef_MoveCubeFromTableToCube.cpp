#include "IBActionDef_MoveCubeFromTableToCube.h"
#include "World\IBCubeWorld.h"
#include "World\IBCube.h"
#include "IBPlanner.h"


IBActionDef_MoveCubeFromTableToCube::IBActionDef_MoveCubeFromTableToCube(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_MoveCubeFromTableToCube::~IBActionDef_MoveCubeFromTableToCube()
{

}

void IBActionDef_MoveCubeFromTableToCube::Define()
{
	AddVariable("Cube");
	AddVariable("DestCube");

	AddPreCondition("IBFactDef_IsOnTable", "Cube");
	AddPreCondition("IBFactDef_IsFree", "Cube");
	AddPreCondition("IBFactDef_IsFree", "DestCube");

	AddPostCondition("IBFactDef_IsTopOf", "Cube", "DestCube");
	
	AddCounterPostCondition("IBFactDef_IsFree", "DestCube");
}

bool IBActionDef_MoveCubeFromTableToCube::Init(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(pOwner);
	ASSERT(pWorld != NULL);

	IBCube* pCube = pAction->FindVariables<IBCube>("Cube");
	IBCube* pDestCube = pAction->FindVariables<IBCube>("DestCube");

	ASSERT(pCube == NULL || pCube != pDestCube);

	return (pCube != NULL && pDestCube != NULL);
}


bool IBActionDef_MoveCubeFromTableToCube::Execute(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(pOwner);
	ASSERT(pWorld != NULL);

	IBCube* pCube = pAction->FindVariables<IBCube>("Cube");
	IBCube* pDestCube = pAction->FindVariables<IBCube>("DestCube");

	ASSERT(pCube != NULL && pDestCube != NULL);

	pWorld->MoveCubeFromTableToCube(pCube, pDestCube);

	return true;
}

