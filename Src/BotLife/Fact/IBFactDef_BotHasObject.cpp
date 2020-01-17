#include "IBFactDef_BotHasObject.h"
#include "Utils.h"
#include "BLBot.h"
#include "Vector2.h"
#include "IBPlanner.h"
#include "World/BLObject.h"
#include "World/BLProp.h"

IBFactDef_BotHasObject::IBFactDef_BotHasObject(const string& name, IBPlanner* pPlanner)
	: IBFactDef(name, pPlanner)
{
	AddVariable("Var");
}

IBFactDef_BotHasObject::~IBFactDef_BotHasObject()
{
}

IBF_Result IBFactDef_BotHasObject::Test(const class IBFact* pFact) const
{
	BLBot* pBot = static_cast<BLBot*>(m_pPlanner->GetOwner());

	BLProp* pObj = pFact->GetVariable<BLProp>();
	
	if (pObj == NULL)
		return IBF_UNKNOW;

	return ((pBot->HasObject(pObj)) ? IBF_OK : IBF_FAIL);
}
