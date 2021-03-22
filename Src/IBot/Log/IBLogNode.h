#ifndef __IBLOGNODE_H__
#define __IBLOGNODE_H__

#include "IBLogBox.h"
#include "Utils.h"
#include "Display/IBPlannerDisplay.h"
#include "Color.h"
#include "Canvas.h"

class IBLogNode : public IBLogBox
{
	public:
		IBLogNode(const class IBNode* pNode);
		virtual ~IBLogNode();

	public:
		virtual void		Refresh(Canvas& oCanvas) override;
		virtual void		Draw(Canvas& oCanvas, sint32 x, sint32 y) override;

	protected:
		virtual void		Size(Canvas& oCanvas, sint32& Width, sint32& Height) override;

	private:
		const class IBNode* m_pNode;

		vector<class IBLogFact*> m_aLogFacts;
};

#endif
