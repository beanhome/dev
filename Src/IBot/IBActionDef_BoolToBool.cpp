#include "IBActionDef_BoolToBool.h"


IBActionDef_BoolToBool::IBActionDef_BoolToBool(IBPlanner* pPlanner)
	: IBActionDef(pPlanner)
{

}

IBActionDef_BoolToBool::~IBActionDef_BoolToBool()
{

}

void IBActionDef_BoolToBool::Define()
{
	AddPreCondition("IBFactDef_Bool");
	AddPostCondition("IBFactDef_Bool");
}
