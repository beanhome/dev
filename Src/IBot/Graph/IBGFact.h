#ifndef __IBGFACT_H__
#define __IBGFACT_H__

#include "IBGBoxBase.h"
#include "Fact\IBFact.h"

class IBAction;
class IBFact;
class IBGActionBox;
class IBGFactBox;
class Canvas;

class IBGFact : public IBFact, public IBGBoxBase
{
	public:
		IBGFact(IBFactDef* pDef, const vector<IBObject*>& aUserData, CanvasBase& oParentCanvas);
		~IBGFact();

		const IBGFactBox*		GetFactBox() const { return m_pFactBox; }
		IBGFactBox*				GetFactBox() { return m_pFactBox; }

		virtual void			Resize();
		virtual void			Draw() const;

	protected:
		IBGFactBox*				m_pFactBox;
};

#endif