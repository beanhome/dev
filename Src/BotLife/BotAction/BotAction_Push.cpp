#include "BotAction_Push.h"
#include "GUtils.h"
#include "ImageFlipBook.h"
#include "BLBot.h"
#include "GEngine.h"
#include "Canvas.h"
#include "Vector2.h"
#include "World/BLProp.h"

BotAction_Push::BotAction_Push(class BLBot* pBot, class BLProp* pProp, float fDuration)
	: BotAction_Move(pBot, pProp->GetPos(), fDuration)
{
	m_pProp = pProp;
	m_vPropTarget = m_vTarget + (m_vTarget - m_pBot->GetPos());
}

void BotAction_Push::OnStart()
{
	BotAction_Move::OnStart();

	m_pBot->SetState(BLBot::Push);
}

void BotAction_Push::OnUpdate(float dt)
{
	BotAction_Move::OnUpdate(dt);

	float t = m_fTime / m_fDuration;
	float s = (float)m_pBot->GetWorld().GetGridSize();

	Vector2 sp = m_vTarget;
	Vector2 tp = m_vPropTarget;

	m_pProp->SetLoc((s / 2 + s * Lerp((float)sp.x, (float)tp.x, t)), (s / 2 + s * Lerp((float)sp.y, (float)tp.y, t)));
}

void BotAction_Push::OnFinish(bool bInterrupted)
{
	BotAction_Move::OnFinish(bInterrupted);
	
	m_pProp->SetPos(m_vPropTarget);
}
