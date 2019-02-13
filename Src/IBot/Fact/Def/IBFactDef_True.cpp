#include "IBFactDef_True.h"

IBFactDef_True::IBFactDef_True(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 0, pPlanner)
{

}

IBFactDef_True::~IBFactDef_True()
{

}

/*
string IBFactDef_True::GetVariableData(uint i) const
{
	return "true";
}
*/

IBF_Result IBFactDef_True::Test(const class IBFact* pFact) const
{
	return IBF_OK;
}
