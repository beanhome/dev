#include "IBActionDef_MoveCubeFromCubeToTable.h"
#include "IBPlanner.h"
#include "World/IBCubeWorld.h"
#include "World/IBCube.h"


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

	AddPreCondition("IBFactDef_IsTopOf", true, "Top", "Cube", "Bottom", "SrcCube");
	AddPreCondition("IBFactDef_IsFree", true, "Cube");

	AddPostCondition("IBFactDef_IsFree", true, "SrcCube");
}

void	 IBActionDef_MoveCubeFromCubeToTable::CompleteVariables(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != nullptr);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(pOwner);
	ASSERT(pWorld != nullptr);

	IBCube* pCube = pAction->GetVariable<IBCube>("Cube");
	IBCube* pSrcCube = pAction->GetVariable<IBCube>("SrcCube");

	map<string, IBCube*> aCubes;
	aCubes.insert(pair<string, IBCube*>("Cube", pCube));
	aCubes.insert(pair<string, IBCube*>("SrcCube", pSrcCube));

	vector<IBCube*> aUnusedCube;
	for (IBCube* pOneCube : pWorld->GetCubes())
	{
		if (pOneCube != pCube && pOneCube != pSrcCube)
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

bool IBActionDef_MoveCubeFromCubeToTable::Start(IBAction* pAction) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	IBCubeWorld* pWorld = static_cast<IBCubeWorld*>(pOwner);
	ASSERT(pWorld != NULL);

	IBCube* pCube = pAction->GetVariable<IBCube>("Cube");
	IBCube* pSrcCube = pAction->GetVariable<IBCube>("SrcCube");

	ASSERT(pCube != NULL && pSrcCube != NULL);

	pWorld->MoveCubeFromCubeToTable(pCube, pSrcCube);

	return true;
}

