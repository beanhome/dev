#include "BotAction_Drop.h"
#include "BLBot.h"
#include "World/BLProp.h"

BotAction_Drop::BotAction_Drop(class BLBot* pBot, class BLProp* pProp, const Vector2& vPropTarget, float fDuration)
	: BotAction_Work(pBot, pProp->GetPos(), fDuration)
	, m_pProp(pProp)
	, m_vPropTarget(vPropTarget)
{
}

void BotAction_Drop::OnFinish(bool bInterrupted)
{
	BotAction_Work::OnFinish(bInterrupted);
	
	if (!bInterrupted)
		m_pBot->DropObject(m_pProp, m_vPropTarget);
}
