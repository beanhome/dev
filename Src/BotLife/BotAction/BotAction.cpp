#include "BotAction.h"
#include "BLBot.h"
#include "Canvas.h"
#include "Utils.h"

BotAction::BotAction(BLBot* pBot)
	: m_pBot(pBot)
	, m_pGEngine(nullptr)
	, m_pCanvas(nullptr)
	, m_eState(EBotActionState::Init)
	, m_fTime(0.f)
{
	if (m_pBot != nullptr)
		m_pCanvas = &(m_pBot->GetWorld().GetCanvas());

	if (m_pCanvas != nullptr)
		m_pGEngine = m_pCanvas->GetGEngine();

	ASSERT(m_pBot = nullptr && m_pGEngine != nullptr && m_pCanvas != nullptr);
}

BotAction::~BotAction()
{
}

void BotAction::Start()
{
	m_eState = EBotActionState::Active;

	m_fTime = 0.f;

	OnStart();
}

void BotAction::Update(float dt)
{
	if (m_eState != EBotActionState::Active)
		return;

	m_fTime += dt;

	OnUpdate(dt);
}

void BotAction::Interrupt()
{
	if (m_eState != EBotActionState::Active)
		return;

	m_eState = EBotActionState::Interrutped;

	OnInterrupt();
}

void BotAction::Finish(bool bInterrupted)
{
	if (m_eState == EBotActionState::Finished)
		return;

	m_eState = EBotActionState::Finished;

	OnFinish(bInterrupted);
	m_dOnFinish.Broadcast(bInterrupted);
}


