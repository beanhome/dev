#include "IBFactDef_PropIsMovable.h"
#include "Utils.h"
#include "BLBot.h"
#include "IBPlanner.h"
#include "World\BLProp.h"

IBFactDef_PropIsMovable::IBFactDef_PropIsMovable(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, 1, pPlanner)
{
}

IBFactDef_PropIsMovable::~IBFactDef_PropIsMovable()
{
}

IBF_Result IBFactDef_PropIsMovable::Test(const vector<IBObject*>& aUserData)
{
	ASSERT(aUserData.size() == GetDegree());

	BLProp* pProp = reinterpret_cast<BLProp*>(aUserData[0]);
	
	if (pProp == NULL)
		return IBF_UNKNOW;

	return (pProp->IsMovable() ? IBF_OK : IBF_FAIL);
}

void IBFactDef_PropIsMovable::ResolveVariable(vector<IBObject*>& aUserData)
{
}
