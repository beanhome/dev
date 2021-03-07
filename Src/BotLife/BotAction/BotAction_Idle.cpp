#include "BotAction_Idle.h"
#include "GUtils.h"
#include "ImageFlipBook.h"
#include "BLBot.h"
#include "GEngine.h"
#include "Canvas.h"

BotAction_Idle::BotAction_Idle(class BLBot* pBot)
	: BotAction(pBot)
{
}

void BotAction_Idle::OnStart()
{
	m_pBot->SetState(BLBot::Idle);
}

void BotAction_Idle::OnInterrupt()
{
	Finish(false);
}

void BotAction_Idle::OnFinish(bool bInterrupted)
{
}
