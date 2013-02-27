#ifndef __IBGACTIONBOX_H__
#define __IBGACTIONBOX_H__

#include "IBGBoxBase.h"
#include "IBGFactBox.h"

class IBFact;
class IBAction;
class IBGFactBox;
class IBGBox;

class CanvasBase;

class IBGActionBox : public IBGBoxBase
{
public:
	IBGActionBox(Canvas& parent, IBAction* pAction);

	IBAction*		GetAction() { return m_pAction; }
	void			SetAction(IBAction* pAction) { m_pAction = pAction; }

	virtual void	Resize();
	virtual void	Draw() const;

private:
	IBAction* m_pAction;
};

#endif
