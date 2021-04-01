#ifndef __IBTREEACTIONNODE_H__
#define __IBTREEACTIONNODE_H__

#include "IBTreeBox_Container.h"
#include "Utils.h"
#include "Color.h"
#include "Canvas.h"

class IBTreeActionNode : public IBTreeBox_Container
{
	public:
		friend class IBTreeFact;
		friend class IBTreeNode;

		IBTreeActionNode(Canvas& oCanvas, IBTreeBox* pParent, const class IBAction* pAction);
		virtual ~IBTreeActionNode();

	public:
		void				RefreshTree();
		virtual void		ComputeSize() override;
		virtual void		Draw() const override;

	protected:
		virtual void		UpdatePos() override;
		virtual void		OnMouseClick(sint32 iMouseX, sint32 iMouseY) override;

	private:
		const class IBAction* m_pAction;

		class IBTreeAction* m_pTreeAction;
		class IBTreeNode* m_pPreTreeNode;

		bool m_bFolded;
};

#endif
