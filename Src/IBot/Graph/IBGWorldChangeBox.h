#ifndef __IBGFACTPACKBOX_H__
#define __IBGFACTPACKBOX_H__

#include "IBGBoxBase.h"
#include "Types.h"

class IBGWorldChangeBox : public IBGBoxBase
{
public:
	IBGWorldChangeBox(class Canvas& parent, const class IBWorldChange* pWorldChange);
	~IBGWorldChangeBox();

	void					Init();
	virtual void			Resize();
	virtual void			Draw() const;

	const class IBWorldChange* GetWorldChange() const { return m_pWorldChange; }

	const class IBGFactBox* GetFactBox(const class IBFact* pFact) const;
	
private:
	const class IBWorldChange* m_pWorldChange;

	vector<class IBGFactBox*> m_aFactBox;
};

#endif
