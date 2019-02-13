#ifndef __IBGACTIONBOX_H__
#define __IBGACTIONBOX_H__

#include "IBGBoxBase.h"
#include "IBGFactBox.h"

class IBGActionBox : public IBGBoxBase
{
public:
	IBGActionBox(class Canvas& parent, const class IBAction* pAction);
	virtual ~IBGActionBox();

	const class IBAction*		GetAction() const { return m_pAction; }
	//void					SetAction(class IBAction* pAction) { m_pAction = pAction; }

	virtual void			Resize();
	virtual void			Draw() const;

	sint16 GetActionMidHeight() const;

private:
	const class IBAction*		m_pAction;

	vector<class IBGFactBox*>   m_aAdditionalPostCondBox;
};

#endif
