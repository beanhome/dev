#include "IBFactDef_BotAtPos.h"
#include "Utils.h"
#include "BLBot.h"
#include "Vector2.h"
#include "IBPlanner.h"

IBFactDef_BotAtPos::IBFactDef_BotAtPos(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 1, pPlanner)
{
}

IBFactDef_BotAtPos::~IBFactDef_BotAtPos()
{
}

IBF_Result IBFactDef_BotAtPos::Test(const class IBFact* pFact) const
{
	BLBot* pBot = static_cast<BLBot*>(m_pPlanner->GetOwner());

	BLVector2* pPos = pFact->GetVariable<BLVector2>();

	if (pPos == nullptr)
		return IBF_UNKNOW;

	return ((pBot->GetPos() == *pPos) ? IBF_OK : IBF_FAIL);
}

/*
bool IBFactDef_BotAtPos::AreCompatible(const IBFact* A, const IBFact* B) const
{
	ASSERT(A != nullptr);
	ASSERT(B != nullptr);

	if (A->GetFactDef() != this)
		return true;

	if (B->GetFactDef() != this)
		return true;

	ASSERT(A->GetVariables().size() == B->GetVariables().size());

	BLVector2* pPosA = A->GetVariable<BLVector2>();

	if (pPosA == nullptr)
		return true;

	BLVector2* pPosB = B->GetVariable<BLVector2>();

	if (pPosB == nullptr)
		return true;

	return *pPosA == *pPosB;
}
*/
