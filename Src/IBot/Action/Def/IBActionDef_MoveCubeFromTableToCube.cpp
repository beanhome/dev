#include "IBActionDef_MoveCubeFromTableToCube.h"


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
}
