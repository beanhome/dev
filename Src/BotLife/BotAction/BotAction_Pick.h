#ifndef __BOTACTION_PICK_H__
#define __BOTACTION_PICK_H__

#include "BotAction_Work.h"
#include "Vector2.h"

class BotAction_Pick : public BotAction_Work
{
public:
	BotAction_Pick(class BLBot* pBot, class BLProp* pProp, float fDuration);

protected:
	virtual void OnFinish(bool bInterrupted) override;

private:
	class BLProp* m_pProp;
};

#endif