#include "IBFactDef_BotIsEmpty.h"
#include "Utils.h"
#include "BLBot.h"
#include "IBPlanner.h"

IBFactDef_BotIsEmpty::IBFactDef_BotIsEmpty(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 0, pPlanner)
{
}

IBFactDef_BotIsEmpty::~IBFactDef_BotIsEmpty()
{
}

IBF_Result IBFactDef_BotIsEmpty::Test(const vector<void*>& aUserData)
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 0);

	BLBot* pBot = static_cast<BLBot*>(pOwner);

	return ((pBot->GetFirstObject() == NULL) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_BotIsEmpty::ResolveVariable(vector<void*>& aUserData)
{
}

void IBFactDef_BotIsEmpty::Print(const vector<void*>& aUserData, int tab) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 0);

	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s\n", GetName().c_str());
}


