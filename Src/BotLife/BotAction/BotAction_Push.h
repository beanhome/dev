#ifndef __BOTACTION_PUSH_H__
#define __BOTACTION_PUSH_H__

#include "BotAction_Move.h"
#include "Vector2.h"

class BotAction_Push : public BotAction_Move
{
public:
	BotAction_Push(class BLBot* pBot, class BLProp* pProp, float fDuration);

protected:
	virtual void OnStart() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnFinish(bool bInterrupted) override;

public:

private:
	class BLProp* m_pProp;

	Vector2 m_vPropTarget;
};

#endif