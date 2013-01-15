#include "IBFactDef_HasValidPath.h"
#include "Utils.h"
#include "BLBot.h"
#include "Vector2.h"
#include "IBPlanner.h"
#include "World\IBPath.h"

IBFactDef_HasValidPath::IBFactDef_HasValidPath(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 3, pPlanner)
{
}

IBFactDef_HasValidPath::~IBFactDef_HasValidPath()
{
}

IBF_Result IBFactDef_HasValidPath::Test(const vector<void*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 3);

	BLBot* pBot = static_cast<BLBot*>(pOwner);
	Path* pPath = static_cast<IBPath*>(aUserData[0]);
	Vector2* pStart = static_cast<IBVector2*>(aUserData[1]);
	Vector2* pTarget = static_cast<IBVector2*>(aUserData[2]);

	return ((pPath != NULL && pStart != NULL && pTarget != NULL && pPath->IsValid() && pPath->GetStart() == *pStart && pPath->GetTarget() == *pTarget) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_HasValidPath::ResolveVariable(vector<void*>& aUserData)
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

void IBFactDef_HasValidPath::Print(const vector<void*>& aUserData, int tab) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 3);

	BLBot* pBot = static_cast<BLBot*>(pOwner);
	Path* pPath = static_cast<IBPath*>(aUserData[0]);
	Vector2* pStart = static_cast<IBVector2*>(aUserData[1]);
	Vector2* pTarget = static_cast<IBVector2*>(aUserData[2]);

	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s (%p (%d,%d) (%d,%d) )\n", GetName().c_str(), pPath, (pStart != NULL ? pStart->x : 0), (pStart != NULL ? pStart->y : 0), (pTarget != NULL ? pTarget->x : 0), (pTarget != NULL ? pTarget->y : 0));
}


