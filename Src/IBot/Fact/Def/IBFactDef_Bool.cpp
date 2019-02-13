#include "IBFactDef_Bool.h"
#include "Fact/IBFact.h"
#include "World/IBObject.h"


IBFactDef_Bool::IBFactDef_Bool(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 1, pPlanner)
{
}

IBFactDef_Bool::~IBFactDef_Bool()
{
}

/*
string IBFactDef_Bool::GetVariableData(uint i) const
{
	return "false";
}
*/

IBF_Result IBFactDef_Bool::Test(const class IBFact* pFact) const
{
	bool res = *(pFact->GetVariable<bool>());
	return (res ? IBF_OK : IBF_FAIL);
}

