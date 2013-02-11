#include "IBFactDef_HasValidPath.h"
#include "Utils.h"
#include "BLBot.h"
#include "Vector2.h"
#include "IBPlanner.h"
#include "World\IBPath.h"
#include "World\IBInt.h"

IBFactDef_HasValidPath::IBFactDef_HasValidPath(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 4, pPlanner)
{
}

IBFactDef_HasValidPath::~IBFactDef_HasValidPath()
{
}

IBF_Result IBFactDef_HasValidPath::Test(const vector<IBObject*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == GetDegree());

	BLBot* pBot = static_cast<BLBot*>(pOwner);
	Path* pPath = reinterpret_cast<IBPath*>(aUserData[0]);
	Vector2* pStart = reinterpret_cast<IBVector2*>(aUserData[1]);
	Vector2* pTarget = reinterpret_cast<IBVector2*>(aUserData[2]);
	IBInt* pDist = reinterpret_cast<IBInt*>(aUserData[3]);

	if (pPath == NULL || pStart == NULL || pTarget == NULL || pDist == NULL || !pPath->IsValid())
		return IBF_FAIL;

	if (pPath->GetStart() != *pStart)
		return IBF_FAIL;

	if (pBot->GetWorld().GetGrid().DistanceSq(pPath->GetTarget(), *pTarget) > pDist->GetValue() * pDist->GetValue())
		return IBF_FAIL;

	return (pBot->GetWorld().TestPath(*pPath) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_HasValidPath::ResolveVariable(vector<IBObject*>& aUserData)
{
	/*
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 3);

	BLBot* pBot = static_cast<BLBot*>(pOwner);
	Path* pPath = static_cast<IBPath*>(aUserData[0]);
	Vector2* pStart = static_cast<IBVector2*>(aUserData[1]);
	Vector2* pTarget = static_cast<IBVector2*>(aUserData[2]);
	*/

	// Do nothing, have to wait variables filled and use other action to get the path
}

void IBFactDef_HasValidPath::Print(const vector<IBObject*>& aUserData, int tab) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == GetDegree());

	BLBot* pBot = static_cast<BLBot*>(pOwner);
	Path* pPath = reinterpret_cast<IBPath*>(aUserData[0]);
	Vector2* pStart = reinterpret_cast<IBVector2*>(aUserData[1]);
	Vector2* pTarget = reinterpret_cast<IBVector2*>(aUserData[2]);

	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s (%p (%d,%d) (%d,%d) )\n", GetName().c_str(), pPath, (pStart != NULL ? pStart->x : 0), (pStart != NULL ? pStart->y : 0), (pTarget != NULL ? pTarget->x : 0), (pTarget != NULL ? pTarget->y : 0));
}

