#include "IBActionDef_MoveCubeFromCubeToCube.h"


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
}
