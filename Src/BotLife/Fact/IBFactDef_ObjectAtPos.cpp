#include "IBFactDef_ObjectAtPos.h"
#include "Utils.h"
#include "BLBot.h"
#include "World/BLVector2.h"
#include "IBPlanner.h"
#include "World/BLProp.h"

IBFactDef_ObjectAtPos::IBFactDef_ObjectAtPos(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, pPlanner)
{
	AddVariable("Obj");
	AddVariable("Pos");
}

IBFactDef_ObjectAtPos::~IBFactDef_ObjectAtPos()
{
}

IBF_Result IBFactDef_ObjectAtPos::Test(const class IBFact* pFact) const
{
	BLBot* pBot = static_cast<BLBot*>(m_pPlanner->GetOwner());
	BLWorld& oWorld = pBot->GetWorld();

	BLProp* pProp = pFact->GetVariable<BLProp>("Obj");
	BLVector2* pPos = pFact->GetVariable<BLVector2>("Pos");

	if (pPos == nullptr || pProp == nullptr)
		return IBF_UNKNOW;

	const BLSquare& sq = oWorld.GetGrid().GetCase(*pPos);

	return ((sq.GetProp() != nullptr && sq.GetProp() == pProp) ? IBF_OK : IBF_FAIL);
}
