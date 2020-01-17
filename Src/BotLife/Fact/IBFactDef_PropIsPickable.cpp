#include "IBFactDef_PropIsPickable.h"
#include "Utils.h"
#include "Fact/IBFact.h"
#include "World/BLProp.h"

IBFactDef_PropIsPickable::IBFactDef_PropIsPickable(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, pPlanner)
{
	AddVariable("Var");
}

IBFactDef_PropIsPickable::~IBFactDef_PropIsPickable()
{
}

IBF_Result IBFactDef_PropIsPickable::Test(const class IBFact* pFact) const
{
	BLProp* pProp = pFact->GetVariable<BLProp>();

	if (pProp == nullptr)
		return IBF_UNKNOW;

	return (pProp->IsPickable() ? IBF_OK : IBF_FAIL);
}
