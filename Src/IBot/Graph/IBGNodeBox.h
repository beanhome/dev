#ifndef __IBGNODEBOX_H__
#define __IBGNODEBOX_H__

#include "IBGBoxBase.h"
#include "Types.h"

class IBGNodeBox : public IBGBoxBase
{
public:
	IBGNodeBox(class Canvas& parent, const class IBNode* pNode);
	~IBGNodeBox();

	void					Init();
	virtual void			Resize();
	virtual void			Draw() const;

	const class IBNode* GetNode() const { return m_pNode; }

	const class IBGFactBox* GetFactBox(const class IBFact* pFact) const;

private:
	const class IBNode* m_pNode;

	vector<class IBGFactBox*> m_aFactBox;
};

#endif
