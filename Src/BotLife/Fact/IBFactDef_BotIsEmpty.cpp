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

IBF_Result IBFactDef_BotIsEmpty::Test(const class IBFact* pFact) const
{
	BLBot* pBot = static_cast<BLBot*>(m_pPlanner->GetOwner());

	return ((pBot->GetFirstObject() == nullptr) ? IBF_OK : IBF_FAIL);
}
