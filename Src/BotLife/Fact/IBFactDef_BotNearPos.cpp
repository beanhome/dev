#include "IBFactDef_BotNearPos.h"
#include "Utils.h"
#include "BLBot.h"
#include "Vector2.h"
#include "IBPlanner.h"
#include "World\BLObject.h"
#include "World\IBInt.h"

IBFactDef_BotNearPos::IBFactDef_BotNearPos(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 2, pPlanner)
{
}

IBFactDef_BotNearPos::~IBFactDef_BotNearPos()
{
}

IBF_Result IBFactDef_BotNearPos::Test(const vector<IBObject*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 2);

	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	IBVector2* pPos = (IBVector2*)aUserData[0];
	IBInt* pDist = (IBInt*)aUserData[1];

	return ((pPos != NULL && pDist != NULL && pBot->GetWorld().GetGrid().DistanceSq(pBot->GetPos(), *pPos) <= pDist->GetValue() * pDist->GetValue()) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_BotNearPos::ResolveVariable(vector<IBObject*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 2);

}

void IBFactDef_BotNearPos::Print(const vector<IBObject*>& aUserData, int tab) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 2);

	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	IBVector2* pPos = (IBVector2*)aUserData[0];
	ASSERT(pPos != NULL);
	IBInt* pDist = (IBInt*)aUserData[1];
	ASSERT(pDist != NULL);

	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s %s (%d %d) at %d\n", GetName().c_str(), pPos->x, pPos->y, pDist);
}


