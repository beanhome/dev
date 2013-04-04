#include "IBFactDef_PropIsPickable.h"
#include "Utils.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "World/BLProp.h"

IBFactDef_PropIsPickable::IBFactDef_PropIsPickable(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 1, pPlanner)
{
}

IBFactDef_PropIsPickable::~IBFactDef_PropIsPickable()
{
}

IBF_Result IBFactDef_PropIsPickable::Test(const vector<IBObject*>& aUserData)
{
	ASSERT(aUserData.size() == GetDegree());

	BLProp* pProp = reinterpret_cast<BLProp*>(aUserData[0]);
	
	if (pProp == NULL)
		return IBF_UNKNOW;

	return (pProp->IsPickable() ? IBF_OK : IBF_FAIL);
}

void IBFactDef_PropIsPickable::ResolveVariable(vector<IBObject*>& aUserData)
{
}
