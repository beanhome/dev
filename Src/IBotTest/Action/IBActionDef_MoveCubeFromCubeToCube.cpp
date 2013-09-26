#include "IBActionDef_MoveCubeFromCubeToCube.h"
#include "IBPlanner.h"
#include "World\IBCubeWorld.h"
#include "World\IBCube.h"


IBActionDef_MoveCubeFromCubeToCube::IBActionDef_MoveCubeFromCubeToCube(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_MoveCubeFromCubeToCube::~IBActionDef_MoveCubeFromCubeToCube()
{

}

void IBActionDef_MoveCubeFromCubeToCube::Define()
{
	AddVariable("Cube");
	AddVariable("DestCube");
	AddVariable("SrcCube");

	AddPreCondition("IBFactDef_IsTopOf", "Cube", "SrcCube");
	AddPreCondition("IBFactDef_IsFree", "Cube");
	AddPreCondition("IBFactDef_IsFree", "DestCube");

	AddPostCondition("IBFactDef_IsTopOf", "Cube", "DestCube");
	AddPostCondition("IBFactDef_IsFree", "SrcCube");

	AddCounterPostCondition("IBFactDef_IsFree", "DestCube");
}

bool IBActionDef_MoveCubeFromCubeToCube::Init(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(pOwner);
	ASSERT(pWorld != NULL);

	IBCube* pCube = pAction->FindVariables<IBCube>("Cube");
	IBCube* pDestCube = pAction->FindVariables<IBCube>("DestCube");
	IBCube* pSrcCube = pAction->FindVariables<IBCube>("SrcCube");

 	if (pCube != NULL && pSrcCube == NULL && pDestCube != NULL)
	{
		for (uint i=0 ; i<pWorld->GetCubes().size() ; ++i)
		{
			IBCube* pTmpCube = pWorld->GetCubes()[i];

			if (pTmpCube != pCube && pTmpCube != pDestCube)
			{
				pSrcCube = pTmpCube;
				break;
			}
		}

		pAction->SetVariable("SrcCube", pSrcCube);
	}
	else if (pSrcCube != NULL && pCube == NULL)
	{
		pCube = (IBCube*) pSrcCube->GetTopCube();
		pAction->SetVariable("Cube", pCube);
	}

	if (pDestCube == NULL)
	{
		for (uint i=0 ; i<pWorld->GetCubes().size() ; ++i)
		{
			IBCube* pTmpCube = pWorld->GetCubes()[i];
			if (pTmpCube != pCube && pTmpCube != pSrcCube && pTmpCube->IsFree())
			{
				pDestCube = pTmpCube;
				pAction->SetVariable("DestCube", pDestCube);
				break;
			}
		}
	}

	ASSERT((pCube == NULL || pCube != pSrcCube) && (pCube == NULL || pCube != pDestCube) && (pSrcCube == NULL || pSrcCube != pDestCube));

	return (pCube != NULL && pDestCube != NULL && pSrcCube != NULL);
}

bool IBActionDef_MoveCubeFromCubeToCube::Execute(IBAction* pAction)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(pOwner);
	ASSERT(pWorld != NULL);

	IBCube* pCube = pAction->FindVariables<IBCube>("Cube");
	IBCube* pDestCube = pAction->FindVariables<IBCube>("DestCube");
	IBCube* pSrcCube = pAction->FindVariables<IBCube>("SrcCube");

	ASSERT(pCube != NULL && pDestCube != NULL && pSrcCube != NULL);

	pWorld->MoveCubeFromCubeToCube(pCube, pSrcCube, pDestCube);

	return true;
}

