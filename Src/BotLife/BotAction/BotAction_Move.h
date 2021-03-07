#ifndef __BOTACTION_MOVE_H__
#define __BOTACTION_MOVE_H__

#include "BotAction.h"
#include "Vector2.h"

class BotAction_Move : public BotAction
{
public:
	BotAction_Move(class BLBot* pBot, const Vector2& vTarget, float fDuration);

protected:
	virtual void OnStart() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnInterrupt() override;
	virtual void OnFinish(bool bInterrupted) override;

	virtual float GetProgression() const override;

public:

protected:
	Vector2 m_vTarget;

	float m_fDuration;
};

#endif