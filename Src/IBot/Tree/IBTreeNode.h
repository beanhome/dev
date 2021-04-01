#ifndef __IBTREENODE_H__
#define __IBTREENODE_H__

#include "IBTreeBox.h"
#include "Utils.h"
#include "Canvas.h"

class IBTreeNode : public IBTreeBox
{
	public:
		friend class IBTreeAction;

		IBTreeNode(Canvas& oCanvas, IBTreeBox* pParent, const class IBNode* pNode);
		virtual ~IBTreeNode();

	public:
		void				RefreshTree();
		virtual void		ComputeSize() override;
		virtual void		Draw() const override;
		virtual void		SetPos(sint32 x, sint32 y);
		virtual void		Update(float dt, sint32 iMouseX, sint32 iMouseY) override;

	protected:
		virtual void		UpdatePos() override;
		virtual void		OnMouseClick(sint32 iMouseX, sint32 iMouseY) override;

	private:
		const class IBNode* m_pNode;

		list<class IBTreeFact*> m_aTreeFacts;
};

#endif
