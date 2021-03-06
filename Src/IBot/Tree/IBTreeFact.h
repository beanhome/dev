#ifndef __IBTREEFACT_H__
#define __IBTREEFACT_H__

#include "IBTreeBox_Horiz.h"
#include "Utils.h"
#include "Canvas.h"

class IBTreeFact : public IBTreeBox_Horiz
{
	public:
		friend class IBTreeNode;

		IBTreeFact(Canvas& oCanvas, IBTreeBox* pParent, const class IBFact* pFact);
		virtual ~IBTreeFact();

	public:
		void				RefreshTree();
		virtual void		Draw() const override;

	protected:
		void				Construct();

		virtual void		OnMouseClick(sint32 iMouseX, sint32 iMouseY) override;

		string				GetFullName() const;

	private:
		const class IBFact* m_pFact;

		class IBTreeBox_Image* m_pExtendArrow;
		class IBTreeBox_Image* m_pFoldArrow;

		bool m_bExtended;
		bool m_bFolded;

		list<class IBTreeActionNode*> m_aTreeActionNodes; // used by IBTreeNode


		class FontResource* m_pFactTitleFont;
		class FontResource* m_pFactVarFont;
		class ImageResource* m_pRightArrowImage;
		class ImageResource* m_pDownArrowImage;
};

#endif
