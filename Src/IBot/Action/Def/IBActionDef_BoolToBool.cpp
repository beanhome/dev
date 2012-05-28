#include "IBActionDef_BoolToBool.h"


IBActionDef_BoolToBool::IBActionDef_BoolToBool(const string& name, IBPlanner* pPlanner)
	: IBActionDef(name, pPlanner)
{

}

IBActionDef_BoolToBool::~IBActionDef_BoolToBool()
{

}

void IBActionDef_BoolToBool::Define()
{
	AddPreCondition("IBFactDef_Bool", "VarIn");
	AddPostCondition("IBFactDef_Bool", "VarOut");
}
