#include "IBFactDef_HasValidPath.h"
#include "Utils.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "World/BLPath.h"
#include "World/BLInt.h"
#include "World/BLVector2.h"

IBFactDef_HasValidPath::IBFactDef_HasValidPath(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, pPlanner)
{
	AddVariable("Target");
	AddVariable("Dist");
	AddVariable("Path");
}

IBFactDef_HasValidPath::~IBFactDef_HasValidPath()
{
}

IBF_Result IBFactDef_HasValidPath::Test(const class IBFact* pFact) const
{
	BLBot* pBot = static_cast<BLBot*>(m_pPlanner->GetOwner());

	BLPath* pPath = pFact->GetVariable<BLPath>("Path");
	BLVector2* pTarget = pFact->GetVariable<BLVector2>("Target");
	BLInt* pDist = pFact->GetVariable<BLInt>("Dist");

	if (pPath == nullptr || pTarget == nullptr || pDist == nullptr)
		return IBF_UNKNOW;

	if (!pPath->IsValid())
		return IBF_FAIL;

	if (!pPath->InOnPath(pBot->GetPos()))
		return IBF_FAIL;

	if (pBot->GetWorld().GetGrid().Distance(pPath->GetTarget(), *pTarget) > pDist->GetValue())
		return IBF_FAIL;

	return (pBot->GetWorld().TestPath(*pPath) ? IBF_OK : IBF_FAIL);
}
