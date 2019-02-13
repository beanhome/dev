#ifndef __IBGPLANBOX_H__
#define __IBGPLANBOX_H__

#include "IBGBoxBase.h"
#include "Types.h"

class IBGPlanBox : public IBGBoxBase
{
public:
	IBGPlanBox(class Canvas& parent, const class IBWorldChange* pWorldChange);
	~IBGPlanBox();

	void					Init();

	const class IBWorldChange* GetWorldChange() const { return m_pWorldChange; }
	const class IBGWorldChangeBox* GetWorldChangeBox(const class IBWorldChange* pWorldChange) const;

	virtual void			Resize();
	virtual void			Draw() const;
	
private:
	const class IBWorldChange* m_pWorldChange;

	class IBGWorldChangeBox* m_pWorldChangeBox;
	vector<class IBGActionPlanBox*> m_aActionPlanBox;
};

#endif
