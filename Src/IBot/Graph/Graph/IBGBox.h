#ifndef __IBGBOX_H__
#define __IBGBOX_H__

#include "IBGBoxBase.h"

class IBAction;
class IBFact;
class IBGActionBox;
class IBGFactBox;
class Canvas;

class IBGBox : public IBGBoxBase
{
	public:
		IBGBox(CanvasBase& parent, IBFact* pFact);
		~IBGBox();

		IBGActionBox*	GetActionBox() { return m_pActionBox; }
		IBGFactBox*		GetFactBox() { return m_pFactBox; }

		virtual void	Resize();
		virtual void	Draw() const;

	protected:
		IBGFactBox*			m_pFactBox;
		IBGActionBox*		m_pActionBox;
		vector<IBGBox*>		m_aPreBox;
};

#endif