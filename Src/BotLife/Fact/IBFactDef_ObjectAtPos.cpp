#include "IBFactDef_ObjectAtPos.h"
#include "Utils.h"
#include "BLBot.h"
#include "Vector2.h"
#include "IBPlanner.h"
#include "World\BLProp.h"

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
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == GetDegree());

	BLProp* pProp = ((BLProp*)aUserData[0]);
	IBVector2* pPos = ((IBVector2*)aUserData[1]);

	if (pPos == NULL && pProp != NULL)
	{
		pPos = &pProp->GetPos();
		aUserData[1] = pPos;
	}
}

void IBFactDef_ObjectAtPos::Print(const vector<IBObject*>& aUserData, int tab) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == GetDegree());

	BLProp* pProp = ((BLProp*)aUserData[0]);
	IBVector2* pPos = ((IBVector2*)aUserData[1]);

	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s (%s, %s)\n", GetName().c_str(), (pProp != NULL ? pProp->GetData().c_str() : "nil"), (pPos != NULL ? pPos->GetData().c_str() : "nil"));
}


