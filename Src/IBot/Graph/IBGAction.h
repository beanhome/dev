#ifndef __IBGACTION_H__
#define __IBGACTION_H__

#include "IBGBoxBase.h"
#include "Action\IBAction.h"

class IBAction;
class IBFact;
class IBGActionBox;
class IBGActionBox;
class Canvas;

class IBGAction : public IBAction, public IBGBoxBase
{
	public:
		IBGAction(IBActionDef* pDef, IBFact* pPostCond1);
		~IBGAction();

		const IBGActionBox*	GetActionBox() const { return m_pActionBox; }

		virtual void	Resize();
		virtual void	Draw() const;

	protected:
		IBGActionBox*	m_pActionBox;
};

#endif