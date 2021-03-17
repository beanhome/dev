#ifndef __IBGACTIONPLANBOX_H__
#define __IBGACTIONPLANBOX_H__

#include "IBGBoxBase.h"
#include "Types.h"

class IBGActionPlanBox : public IBGBoxBase
{
public:
	IBGActionPlanBox(class Canvas& parent, const class IBAction* pAction);
	~IBGActionPlanBox();

	virtual void			Resize();
	virtual void			Draw() const;
	
	const class IBAction* GetAction() const { return m_pAction; }
	const class IBGActionBox* GetGActionBox() const { return m_pActionBox; }
	const class IBGPlanBox* GetGPreCondBox() const { return m_pPreCondBox; }

private:
	void					DrawNode	() const;

private:
	const class IBAction* m_pAction;

	class IBGActionBox* m_pActionBox;
	class IBGPlanBox* m_pPreCondBox;
};

#endif
