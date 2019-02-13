#include "IBFactDef_BotNearPos.h"
#include "Utils.h"
#include "BLBot.h"
#include "World/BLVector2.h"
#include "IBPlanner.h"
#include "World/BLInt.h"

IBFactDef_BotNearPos::IBFactDef_BotNearPos(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 2, pPlanner)
{
	AddVariable("Pos");
	AddVariable("Dist");
}

IBFactDef_BotNearPos::~IBFactDef_BotNearPos()
{
}

IBF_Result IBFactDef_BotNearPos::Test(const class IBFact* pFact) const
{
	BLBot* pBot = static_cast<BLBot*>(m_pPlanner->GetOwner());

	BLVector2* pPos = pFact->GetVariable<BLVector2>("Pos");
	BLInt* pDist = pFact->GetVariable<BLInt>("Dist");

	if (pPos == nullptr || pDist == nullptr)
		return IBF_UNKNOW;

	return ((pBot->GetWorld().GetGrid().Distance(pBot->GetPos(), *pPos) <= pDist->GetValue()) ? IBF_OK : IBF_FAIL);
}

