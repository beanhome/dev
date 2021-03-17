#ifndef __IBGPLANBOX_H__
#define __IBGPLANBOX_H__

#include "IBGBoxBase.h"
#include "Types.h"

class IBGPlanBox : public IBGBoxBase
{
public:
	IBGPlanBox(class Canvas& parent, const class IBNode* pNode);
	~IBGPlanBox();

	void					Init();

	const class IBNode* GetNode() const { return m_pNode; }
	const class IBGNodeBox* GetNodeBox(const class IBNode* pNode) const;

	virtual void			Resize();
	virtual void			Draw() const;
	
private:
	const class IBNode* m_pNode;

	class IBGNodeBox* m_pNodeBox;
	vector<class IBGActionPlanBox*> m_aActionPlanBox;
};

#endif
