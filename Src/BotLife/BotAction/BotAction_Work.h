#ifndef __BOTACTION_WORK_H__
#define __BOTACTION_WORK_H__

#include "BotAction.h"
#include "Vector2.h"
#include "BLBot.h"

class BotAction_Work : public BotAction
{
public:
	BotAction_Work(class BLBot* pBot, const Vector2& vTarget, float fDuration);
	BotAction_Work(class BLBot* pBot, BLBot::BotDir eDir, float fDuration);

protected:
	virtual void OnStart() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnInterrupt() override;
	virtual void OnFinish(bool bInterrupted) override;

	virtual float GetProgression() const override;

public:

private:
	float m_fDuration;

	BLBot::BotDir m_eDir;
};

#endif