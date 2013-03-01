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
}

IBFactDef_PosIsFree::~IBFactDef_PosIsFree()
{
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

	return ((sq.IsBlock() || sq.IsTempBlock()) ? IBF_FAIL : IBF_OK);
}

void IBFactDef_PosIsFree::ResolveVariable(vector<IBObject*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);

	IBVector2* pPos = reinterpret_cast<IBVector2*>(aUserData[0]);

	if (pPos == NULL)
	{
		BLBot* pBot = static_cast<BLBot*>(pOwner);
		const BLWorld& oWorld = pBot->GetWorld();
		NavDijkstra<BLSquare>* pNav = new NavDijkstra<BLSquare>(oWorld.GetGrid());

		Path oPath;
		Cond_Free oCondFree;
		pNav->FindPath(pBot->GetPos(), oCondFree, oPath);

		// TODO : Fix delete
		pPos = new IBVector2("free", oPath.GetTarget(), true);
		aUserData[0] = pPos;

		delete pNav;
	}
}

void IBFactDef_PosIsFree::Print(const vector<IBObject*>& aUserData, int tab) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == GetDegree());

	Vector2* pPos = reinterpret_cast<IBVector2*>(aUserData[0]);

	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s\n", GetName().c_str());
}


