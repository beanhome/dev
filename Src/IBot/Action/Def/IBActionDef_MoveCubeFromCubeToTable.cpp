#include "IBActionDef_MoveCubeFromCubeToTable.h"


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
