#include "BotAction_Move.h"
#include "GUtils.h"
#include "ImageFlipBook.h"
#include "BLBot.h"
#include "GEngine.h"
#include "Canvas.h"
#include "Vector2.h"

BotAction_Move::BotAction_Move(class BLBot* pBot, const Vector2& vTarget, float fDuration)
	: BotAction(pBot)
	, m_vTarget(vTarget)
	, m_fDuration(fDuration)
{
}

void BotAction_Move::OnStart()
{
	m_pBot->SetState(BLBot::Walk);
	m_pBot->SetDir(m_vTarget);
}

void BotAction_Move::OnUpdate(float dt)
{
	float t = min(m_fTime / m_fDuration, 1.f);
	float s = (float)m_pBot->GetWorld().GetGridSize();

	Vector2 sp = m_pBot->GetPos();
	Vector2 tp = m_vTarget;

	m_pBot->SetLoc(s*Lerp((float)sp.x, (float)tp.x, t), s*Lerp((float)sp.y, (float)tp.y, t));

	if (m_fTime > m_fDuration)
		Finish(true);
}

void BotAction_Move::OnInterrupt()
{
}

void BotAction_Move::OnFinish(bool bInterrupted)
{
	m_pBot->SetPos(m_vTarget);
	m_pBot->SetState(BLBot::Idle);
}

float BotAction_Move::GetProgression() const
{
	return min(m_fTime / m_fDuration, 1.f);
}