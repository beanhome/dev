#ifndef __BOTACTION_DROP_H__
#define __BOTACTION_DROP_H__

#include "BotAction_Work.h"
#include "Vector2.h"

class BotAction_Drop : public BotAction_Work
{
public:
	BotAction_Drop(class BLBot* pBot, class BLProp* pProp, const Vector2& vPropTarget, float fDuration);

protected:
	virtual void OnFinish(bool bInterrupted) override;

private:
	class BLProp* m_pProp;
	Vector2 m_vPropTarget;
};

#endif