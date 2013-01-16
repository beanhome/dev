#ifndef __IBGFACTBOX_H__
#define __IBGFACTBOX_H__

#include "IBGBoxBase.h"

class IBFact;
class IBAction;
class IBGBox;
class CanvasBase;

class IBGFactBox : public IBGBoxBase
{
public:
	IBGFactBox(Canvas& parent, IBFact* pFact);

	IBFact*				GetFact() { return m_pFact; }

	virtual void		Resize();
	virtual void		Draw() const;

private:
	IBFact* m_pFact;
};

#endif
