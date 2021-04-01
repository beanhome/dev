#ifndef __IBTREEBOX_CONTAINER_H__
#define __IBTREEBOX_CONTAINER_H__

#include "IBTreeBox.h"
#include "Utils.h"
#include "Canvas.h"

class IBTreeBox_Container : public IBTreeBox
{
	public:
		IBTreeBox_Container(Canvas& oCanvas, IBTreeBox* pParent);
		virtual ~IBTreeBox_Container();

	public:
		void				AddChild(class IBTreeBox* pBox);
		const list<class IBTreeBox*>& GetChildren() const { return m_aChildren; }

		virtual void		SetPos(sint32 x, sint32 y);

		virtual void		Update(float dt, sint32 iMouseX, sint32 iMouseY) override;
		virtual void		Draw() const override;

	protected:
		virtual void		OnMouseClick(sint32 iMouseX, sint32 iMouseY) override;

	protected:
		list<class IBTreeBox*> m_aChildren;
};

#endif
