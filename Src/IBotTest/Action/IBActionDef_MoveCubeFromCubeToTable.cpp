#include "IBActionDef_MoveCubeFromCubeToTable.h"
#include "IBPlanner.h"
#include "World\IBCubeWorld.h"
#include "World\IBCube.h"


IBActionDef_MoveCubeFromCubeToTable::IBActionDef_MoveCubeFromCubeToTable(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_MoveCubeFromCubeToTable::~IBActionDef_MoveCubeFromCubeToTable()
{

}

void IBActionDef_MoveCubeFromCubeToTable::Define()
{
	AddVariable("Cube");
	AddVariable("SrcCube");

	AddPreCondition("IBFactDef_IsTopOf", "Cube", "SrcCube");
	AddPreCondition("IBFactDef_IsFree", "Cube");

	AddPostCondition("IBFactDef_IsFree", "SrcCube");
}

bool IBActionDef_MoveCubeFromCubeToTable::Init(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(pOwner);
	ASSERT(pWorld != NULL);

	IBCube* pCube = pAction->FindVariables<IBCube>("Cube");
	IBCube* pSrcCube = pAction->FindVariables<IBCube>("SrcCube");

	if (pCube == NULL && pSrcCube != NULL)
	{
		pCube = (IBCube*) pSrcCube->GetTopCube();
		pAction->SetVariable("Cube", pCube);
	}

	ASSERT(pCube == NULL || pCube != pSrcCube);

	return (pCube != NULL && pSrcCube != NULL);
}

bool IBActionDef_MoveCubeFromCubeToTable::Execute(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(pOwner);
	ASSERT(pWorld != NULL);

	IBCube* pCube = pAction->FindVariables<IBCube>("Cube");
	IBCube* pSrcCube = pAction->FindVariables<IBCube>("SrcCube");

	ASSERT(pCube != NULL && pSrcCube != NULL);

	pWorld->MoveCubeFromCubeToTable(pCube, pSrcCube);

	return true;
}

