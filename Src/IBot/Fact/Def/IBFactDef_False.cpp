#include "IBFactDef_False.h"


IBFactDef_False::IBFactDef_False(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 0, pPlanner)
{

}

IBFactDef_False::~IBFactDef_False()
{

}
/*
string IBFactDef_False::GetVariableData(uint i) const
{
	return "false";
}
*/

IBF_Result IBFactDef_False::Test(const class IBFact* pFact) const
{
	return IBF_FAIL;
}

