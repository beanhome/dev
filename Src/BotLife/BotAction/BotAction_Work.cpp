#include "BotAction_Work.h"
#include "GUtils.h"
#include "ImageFlipBook.h"
#include "BLBot.h"
#include "GEngine.h"
#include "Canvas.h"
#include "Vector2.h"

BotAction_Work::BotAction_Work(class BLBot* pBot, const Vector2& vTarget, float fDuration)
	: BotAction(pBot)
	, m_fDuration(fDuration)
	, m_eDir(pBot->ComputeDir(vTarget))
{
}

BotAction_Work::BotAction_Work(class BLBot* pBot, BLBot::BotDir eDir, float fDuration)
	: BotAction(pBot)
	, m_fDuration(fDuration)
	, m_eDir(eDir)
{
}


void BotAction_Work::OnStart()
{
	m_pBot->SetState(BLBot::Action);
	m_pBot->SetDir(m_eDir);
}

void BotAction_Work::OnUpdate(float dt)
{
	if (m_fTime > m_fDuration)
		Finish(true);
}

void BotAction_Work::OnInterrupt()
{
	Finish(false);
}

void BotAction_Work::OnFinish(bool bInterrupted)
{
	m_pBot->SetState(BLBot::Idle);
}

float BotAction_Work::GetProgression() const
{
	return min(m_fTime / m_fDuration, 1.f);
}