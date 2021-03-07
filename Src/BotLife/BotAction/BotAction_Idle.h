#ifndef __BOTACTION_IDLE_H__
#define __BOTACTION_IDLE_H__

#include "BotAction.h"

class BotAction_Idle : public BotAction
{
public:
	BotAction_Idle(class BLBot* pBot);

protected:
	virtual void OnStart();
	virtual void OnInterrupt();
	virtual void OnFinish(bool bInterrupted);
};

#endif