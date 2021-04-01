#ifndef __IBTREEACTION_H__
#define __IBTREEACTION_H__

#include "IBTreeBox_Horiz.h"
#include "Utils.h"
#include "Canvas.h"

class IBTreeAction : public IBTreeBox_Horiz
{
	public:
		friend class IBTreeFact;
		friend class IBTreeNode;

		IBTreeAction(Canvas& oCanvas, IBTreeBox* pParent, const class IBAction* pAction);
		virtual ~IBTreeAction();

	public:
		void				RefreshTree();
		virtual void		Draw() const override;

	protected:
		void				Construct();

		virtual void		OnMouseClick(sint32 iMouseX, sint32 iMouseY) override;

		string				GetFullName() const;

	private:
		const class IBAction* m_pAction;

		class IBTreeBox_Image* m_pExtendArrow;

		bool m_bExtended;

		FontResource* m_pActionTitleFont;
		FontResource* m_pActionVarFont;
		class ImageResource* m_pRightArrowImage;
		class ImageResource* m_pDownArrowImage;
};

#endif
