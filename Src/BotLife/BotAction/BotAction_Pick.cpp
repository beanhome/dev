#include "BotAction_Pick.h"
#include "BLBot.h"
#include "World/BLProp.h"

BotAction_Pick::BotAction_Pick(class BLBot* pBot, class BLProp* pProp, float fDuration)
	: BotAction_Work(pBot, pProp->GetPos(), fDuration)
	, m_pProp(pProp)
{
}

void BotAction_Pick::OnFinish(bool bInterrupted)
{
	BotAction_Work::OnFinish(bInterrupted);
	
	if (!bInterrupted)
		m_pBot->PickProp(m_pProp);
}
