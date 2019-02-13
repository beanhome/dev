#include "IBFactDef_PropIsBlock.h"
#include "Utils.h"
#include "Fact/IBFact.h"
#include "World/BLProp.h"

IBFactDef_PropIsBlock::IBFactDef_PropIsBlock(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 1, pPlanner)
{
}

IBFactDef_PropIsBlock::~IBFactDef_PropIsBlock()
{
}

IBF_Result IBFactDef_PropIsBlock::Test(const class IBFact* pFact) const
{
	BLProp* pProp = pFact->GetVariable<BLProp>();

	if (pProp == nullptr)
		return IBF_UNKNOW;

	return (pProp->IsBlock() ? IBF_OK : IBF_FAIL);
}



