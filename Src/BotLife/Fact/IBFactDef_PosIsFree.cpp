#include "IBFactDef_PosIsFree.h"
#include "Utils.h"
#include "BLBot.h"
#include "Vector2.h"
#include "IBPlanner.h"
#include "World\IBPath.h"
#include "World\IBInt.h"
#include "NavDijkstra.h"

IBFactDef_PosIsFree::IBFactDef_PosIsFree(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 1, pPlanner)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	BLBot* pBot = static_cast<BLBot*>(pOwner);
	const BLWorld& oWorld = pBot->GetWorld();
	pNav = new NavDijkstra<BLSquare>(oWorld.GetGrid());

}

IBFactDef_PosIsFree::~IBFactDef_PosIsFree()
{
	delete pNav;
}

IBF_Result IBFactDef_PosIsFree::Test(const vector<IBObject*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == GetDegree());

	BLBot* pBot = static_cast<BLBot*>(pOwner);
	IBVector2* pPos = reinterpret_cast<IBVector2*>(aUserData[0]);

	if (pPos == NULL)
		return IBF_UNKNOW;

	BLSquare& sq = pBot->GetWorld().GetGrid().GetCase(*pPos);

	return ((sq.IsFree()) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_PosIsFree::ResolveVariable(vector<IBObject*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);

	IBVector2* pPos = reinterpret_cast<IBVector2*>(aUserData[0]);

	if (pPos == NULL)
	{
		pPos = new IBVector2("free", 0, 0, true);
		BLBot* pBot = static_cast<BLBot*>(pOwner);

		Path oPath;
		Cond_Free oCondFree;
		pNav->FindPath(pBot->GetPos(), oCondFree, oPath);
		*pPos = oPath.GetTarget();
		aUserData[0] = pPos;
	}
}



