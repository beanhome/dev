#include "IBFactDef_PropIsUnblock.h"
#include "Utils.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "World\BLProp.h"

IBFactDef_PropIsUnblock::IBFactDef_PropIsUnblock(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 1, pPlanner)
{
}

IBFactDef_PropIsUnblock::~IBFactDef_PropIsUnblock()
{
}

IBF_Result IBFactDef_PropIsUnblock::Test(const vector<void*>& aUserData)
{
	ASSERT(aUserData.size() == GetDegree());

	BLProp* pProp = static_cast<BLProp*>(aUserData[0]);
	ASSERT(pProp != NULL);

	return ((!pProp->IsTempBlock()) ? IBF_OK : IBF_FAIL);
}

void IBFactDef_PropIsUnblock::ResolveVariable(vector<void*>& aUserData)
{
}

void IBFactDef_PropIsUnblock::Print(const vector<void*>& aUserData, int tab) const
{
	void* pOwner = m_pPlanner->GetOwner();
	ASSERT(pOwner != NULL);
	ASSERT(aUserData.size() == 0);

	for (int i=0 ; i<tab ; ++i)
		LOG("\t");

	LOG("%s\n", GetName().c_str());
}


