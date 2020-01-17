#include "IBFactDef_PropIsMovable.h"
#include "Utils.h"
#include "Fact/IBFact.h"
#include "World/BLProp.h"

IBFactDef_PropIsMovable::IBFactDef_PropIsMovable(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, pPlanner)
{
	AddVariable("Var");
}

IBFactDef_PropIsMovable::~IBFactDef_PropIsMovable()
{
}

IBF_Result IBFactDef_PropIsMovable::Test(const class IBFact* pFact) const
{
	BLProp* pProp = pFact->GetVariable<BLProp>();
	
	if (pProp == nullptr)
		return IBF_UNKNOW;

	return (pProp->IsMovable() ? IBF_OK : IBF_FAIL);
}
