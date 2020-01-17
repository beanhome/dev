#include "IBFactDef_BotNearPos.h"
#include "Utils.h"
#include "BLBot.h"
#include "World/BLVector2.h"
#include "IBPlanner.h"
#include "World/BLInt.h"

IBFactDef_BotNearPos::IBFactDef_BotNearPos(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, pPlanner)
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

bool	 IBFactDef_BotNearPos::HasSameVariables(const class IBFact* pA, const class IBFact* pB) const
{
	ASSERT(pA != nullptr && pB != nullptr);
	ASSERT(pA->GetFactDef() == this && pB->GetFactDef() == this);
	ASSERT(pA->GetVariables().size() == GetDegree() && pB->GetVariables().size() == GetDegree());

	BLVector2* pAPos = pA->GetVariable<BLVector2>("Pos");
	BLVector2* pBPos = pB->GetVariable<BLVector2>("Pos");

	if (pAPos != pBPos && *pAPos != *pBPos)
		return false;

	BLInt* pADist = pA->GetVariable<BLInt>("Dist");
	BLInt* pBDist = pB->GetVariable<BLInt>("Dist");

	if (pADist != pBDist && *pADist != *pBDist)
		return false;

	return true;
}

