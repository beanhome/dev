#include "IBFactDef_PosIsFree.h"
#include "Utils.h"
#include "BLBot.h"
#include "World/BLVector2.h"
#include "IBPlanner.h"

IBFactDef_PosIsFree::IBFactDef_PosIsFree(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, pPlanner)
{
	AddVariable("Var");
}

IBFactDef_PosIsFree::~IBFactDef_PosIsFree()
{
}

IBF_Result IBFactDef_PosIsFree::Test(const class IBFact* pFact) const
{
	BLBot* pBot = static_cast<BLBot*>(m_pPlanner->GetOwner());

	BLVector2* pPos = pFact->GetVariable<BLVector2>();

	if (pPos == nullptr)
		return IBF_UNKNOW;

	BLSquare& sq = pBot->GetWorld().GetGrid().GetCase(*pPos);

	return ((sq.IsFree()) ? IBF_OK : IBF_FAIL);
}
