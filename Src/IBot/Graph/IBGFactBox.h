#ifndef __IBGFACTBOX_H__
#define __IBGFACTBOX_H__

#include "IBGBoxBase.h"
#include "Types.h"

class IBFact;
class IBAction;
class IBGBox;
class CanvasBase;
class IBObject;

class IBGFactBox : public IBGBoxBase
{
public:
	IBGFactBox(Canvas& parent, IBFact* pFact);
	~IBGFactBox();

	IBFact*				GetFact() { return m_pFact; }

	virtual void			Resize();
	virtual void			Draw() const;

private:
	string				GetVarText(const string& name, const IBObject& obj) const;

private:
	IBFact* m_pFact;
};

#endif
