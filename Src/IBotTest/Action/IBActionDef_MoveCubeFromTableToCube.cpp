#include "IBActionDef_MoveCubeFromTableToCube.h"
#include "World/IBCubeWorld.h"
#include "World/IBCube.h"
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

	AddPreCondition("IBFactDef_IsOnTable", true, "Cube");
	AddPreCondition("IBFactDef_IsFree", true, "Cube");
	AddPreCondition("IBFactDef_IsFree", true, "DestCube");

	AddPostCondition("IBFactDef_IsTopOf", true, "Top", "Cube", "Bottom", "DestCube");
	AddPostCondition("IBFactDef_IsOnTable", false, "Cube");
	AddPostCondition("IBFactDef_IsFree", false, "DestCube");
}

void	 IBActionDef_MoveCubeFromTableToCube::CompleteVariables(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(pOwner);
	ASSERT(pWorld != nullptr);

	IBCube* pCube = pAction->GetVariable<IBCube>("Cube");
	IBCube* pDestCube = pAction->GetVariable<IBCube>("DestCube");

	map<string, IBCube*> aCubes;
	aCubes.insert(pair<string, IBCube*>("Cube", pCube));
	aCubes.insert(pair<string, IBCube*>("DestCube", pDestCube));

	vector<IBCube*> aUnusedCube;
	for (IBCube* pOneCube : pWorld->GetCubes())
	{
		if (pOneCube != pCube && pOneCube != pDestCube)
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

bool IBActionDef_MoveCubeFromTableToCube::Execute(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(pOwner);
	ASSERT(pWorld != NULL);

	IBCube* pCube = pAction->GetVariable<IBCube>("Cube");
	IBCube* pDestCube = pAction->GetVariable<IBCube>("DestCube");

	ASSERT(pCube != NULL && pDestCube != NULL);

	pWorld->MoveCubeFromTableToCube(pCube, pDestCube);

	return true;
}