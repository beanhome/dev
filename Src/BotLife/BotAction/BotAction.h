#ifndef __BOTACTION_H__
#define __BOTACTION_H__

#include "Delegate.h"

enum class EBotActionState : unsigned char
{
	Init,
	Active,
	Interrutped,
	Finished
};

class BotAction
{
public:

public:
	BotAction(class BLBot* pBot);
	~BotAction();

	void Start();
	void Update(float dt);
	void Interrupt();

	float GetTime() const { return m_fTime; }

	virtual float GetProgression() const { return 0.f; }

protected:
	virtual void OnStart() {}
	virtual void OnUpdate(float dt) {}
	virtual void OnInterrupt() {}
	virtual void OnFinish(bool bInterrupted) {}

protected:
	void Finish(bool bInterrupted);

protected:
	class BLBot* m_pBot;
	class GEngine* m_pGEngine;
	class Canvas* m_pCanvas;

	EBotActionState m_eState;
	float m_fTime;

public:
	MulticastDelegate<bool> m_dOnFinish;

};

#endif