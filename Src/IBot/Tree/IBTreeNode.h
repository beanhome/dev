#ifndef __IBTreeNODE_H__
#define __IBTreeNODE_H__

#include "IBTreeBox.h"
#include "Utils.h"
#include "Display/IBPlannerDisplay.h"
#include "Color.h"
#include "Canvas.h"

class IBTreeNode : public IBTreeBox
{
	public:
		IBTreeNode(const class IBNode* pNode);
		virtual ~IBTreeNode();

	public:
		virtual void		Refresh(Canvas& oCanvas) override;
		virtual void		Draw(Canvas& oCanvas, sint32 x, sint32 y) override;

	protected:
		virtual void		Size(Canvas& oCanvas, sint32& Width, sint32& Height) override;

	private:
		const class IBNode* m_pNode;

		vector<class IBTreeFact*> m_aLogFacts;
};

#endif
