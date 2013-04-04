#include "IBFactDef_ObjectAtPos.h"
#include "Utils.h"
#include "BLBot.h"
#include "Vector2.h"
#include "IBPlanner.h"
#include "World/BLProp.h"

IBFactDef_ObjectAtPos::IBFactDef_ObjectAtPos(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 2, pPlanner)
{
}

IBFactDef_ObjectAtPos::~IBFactDef_ObjectAtPos()
{
}

IBF_Result IBFactDef_ObjectAtPos::Test(const vector<IBObject*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == GetDegree());

	BLProp* pProp = ((BLProp*)aUserData[0]);
	IBVector2* pPos = ((IBVector2*)aUserData[1]);

	if (pPos == NULL || pProp == NULL)
		return IBF_UNKNOW;

	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	BLWorld& oWorld = pBot->GetWorld();

	const BLSquare& sq = oWorld.GetGrid().GetCase(*pPos);
	return ((sq.GetProp() != NULL && sq.GetProp() == pProp) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_ObjectAtPos::ResolveVariable(vector<IBObject*>& aUserData)
{
	ASSERT(aUserData.size() == GetDegree());
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	BLWorld& oWorld = pBot->GetWorld();

	BLProp* pProp = ((BLProp*)aUserData[0]);
	IBVector2* pPos = ((IBVector2*)aUserData[1]);

	if (pPos == NULL && pProp != NULL)
	{
		pPos = &pProp->GetPos();
		aUserData[1] = pPos;
	}
	else if (pPos != NULL && pProp == NULL)
	{
		pProp = (BLProp*)oWorld.GetGrid().GetCase(*pPos).GetProp();
		aUserData[0] = pProp;
	}
}

/*
IBFactDef_HeavyObjectAtPos::IBFactDef_HeavyObjectAtPos(const string& name, IBPlanner* pPlanner)
	: IBFactDef_ObjectAtPos(name, pPlanner)
{
}



IBF_Result IBFactDef_HeavyObjectAtPos::Test(const vector<IBObject*>& aUserData)
{
	IBF_Result res = IBFactDef_ObjectAtPos::Test(aUserData);

	if (res == IBF_OK)
	{
		BLProp* pProp = ((BLProp*)aUserData[0]);
		return (pProp->IsMovable() ? IBF_OK : IBF_FAIL);
	}

	return res;
}
*/
