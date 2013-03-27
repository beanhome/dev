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

IBF_Result IBFactDef_BotAtPos::Test(const vector<IBObject*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 1);

	BLBot* pBot = static_cast<BLBot*>(pOwner);
	Vector2* pPos = ((IBVector2*)aUserData[0]);

	if (pPos == NULL)
		return IBF_UNKNOW;

	return ((pBot->GetPos() == *pPos) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_BotAtPos::ResolveVariable(vector<IBObject*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 1);

	BLBot* pBot = static_cast<BLBot*>(pOwner);

	if (aUserData[0] == NULL)
		aUserData[0] = pBot->GetIBPosAd();

	ASSERT(aUserData[0] != NULL);
}



