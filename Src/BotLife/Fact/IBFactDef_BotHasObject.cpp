#include "IBFactDef_BotHasObject.h"
#include "Utils.h"
#include "BLBot.h"
#include "Vector2.h"
#include "IBPlanner.h"
#include "World/BLObject.h"
#include "World/BLProp.h"

IBFactDef_BotHasObject::IBFactDef_BotHasObject(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 1, pPlanner)
{
}

IBFactDef_BotHasObject::~IBFactDef_BotHasObject()
{
}

IBF_Result IBFactDef_BotHasObject::Test(const vector<IBObject*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == GetDegree());

	BLBot* pBot = static_cast<BLBot*>(pOwner);
	ASSERT(pBot != NULL);
	BLProp* pObj = reinterpret_cast<BLProp*>(aUserData[0]);
	
	if (pObj == NULL)
		return IBF_UNKNOW;

	return ((pBot->HasObject(pObj)) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_BotHasObject::ResolveVariable(vector<IBObject*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == GetDegree());

	BLBot* pBot = static_cast<BLBot*>(pOwner);

	if (aUserData[0] == NULL)
		aUserData[0] = pBot->GetFirstObject();
}

