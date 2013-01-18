#include "IBFactDef_BotHasObject.h"
#include "Utils.h"
#include "BLBot.h"
#include "Vector2.h"
#include "IBPlanner.h"

IBFactDef_BotHasObject::IBFactDef_BotHasObject(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 1, pPlanner)
{
}

IBFactDef_BotHasObject::~IBFactDef_BotHasObject()
{
}

IBF_Result IBFactDef_BotHasObject::Test(const vector<void*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 1);

	BLBot* pBot = static_cast<BLBot*>(pOwner);
	BLProp* pObj = (BLProp*)aUserData[0];

	return ((pBot->HasObject(pObj)) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_BotHasObject::ResolveVariable(vector<void*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 1);

	BLBot* pBot = static_cast<BLBot*>(pOwner);

	if (aUserData[0] == NULL)
		aUserData[0] = (void*)(pBot->GetFirstObject());
}

void IBFactDef_BotHasObject::Print(const vector<void*>& aUserData, int tab) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 1);

	IBObject* pObj = (IBObject*)aUserData[0];

	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s %s\n", GetName().c_str(), pObj->GetName().c_str());
}


