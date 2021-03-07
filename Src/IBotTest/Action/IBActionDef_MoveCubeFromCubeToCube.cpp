#include "IBActionDef_MoveCubeFromCubeToCube.h"
#include "IBPlanner.h"
#include "World/IBCubeWorld.h"
#include "World/IBCube.h"

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

	AddPreCondition("IBFactDef_IsTopOf", true, "Top", "Cube", "Bottom", "SrcCube");
	AddPreCondition("IBFactDef_IsFree", true, "Cube");
	AddPreCondition("IBFactDef_IsFree", true, "DestCube");

	AddPostCondition("IBFactDef_IsTopOf", true, "Top", "Cube", "Bottom", "DestCube");
	AddPostCondition("IBFactDef_IsFree", true, "SrcCube");
	//AddPostCondition("IBFactDef_IsTopOf", false, "Top", "Cube", "Bottom", "SrcCube");
	AddPostCondition("IBFactDef_IsFree", false, "DestCube");
}

void	 IBActionDef_MoveCubeFromCubeToCube::CompleteVariables(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(pOwner);
	ASSERT(pWorld != nullptr);

	IBCube* pCube = pAction->GetVariable<IBCube>("Cube");
	IBCube* pDestCube = pAction->GetVariable<IBCube>("DestCube");
	IBCube* pSrcCube = pAction->GetVariable<IBCube>("SrcCube");

	map<string, IBCube*> aCubes;
	aCubes.insert(pair<string, IBCube*>("Cube", pCube));
	aCubes.insert(pair<string, IBCube*>("DestCube", pDestCube));
	aCubes.insert(pair<string, IBCube*>("SrcCube", pSrcCube));

	vector<IBCube*> aUnusedCube;
	for (IBCube* pOneCube : pWorld->GetCubes())
	{
		if (pOneCube != pCube && pOneCube != pDestCube && pOneCube != pSrcCube)
			aUnusedCube.push_back(pOneCube);
	}

	for (map<string, IBCube*>::iterator it = aCubes.begin(); it != aCubes.end(); ++it)
	{
		const string& name = it->first;
		IBCube* cube = it->second;

		if (cube == nullptr)
		{
			for (IBCube* potential : aUnusedCube)
			{
				pAction->AddPotentialVariable(name, potential->GetName(), potential);
			}
		}
	}
}

bool IBActionDef_MoveCubeFromCubeToCube::Start(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(pOwner);
	ASSERT(pWorld != nullptr);

	IBCube* pCube = pAction->GetVariable<IBCube>("Cube");
	IBCube* pDestCube = pAction->GetVariable<IBCube>("DestCube");
	IBCube* pSrcCube = pAction->GetVariable<IBCube>("SrcCube");

	ASSERT(pCube != nullptr && pDestCube != nullptr && pSrcCube != nullptr);

	pWorld->MoveCubeFromCubeToCube(pCube, pSrcCube, pDestCube);

	return true;
}