#ifndef __IBTreeBOX_H__
#define __IBTreeBOX_H__

#include "Utils.h"
#include "Color.h"
#include "Canvas.h"
#include "Delegate.h"

class IBTreeBox
{
	public:
		IBTreeBox(Canvas& oCanvas, IBTreeBox* pParent);
		virtual ~IBTreeBox();

	public:
		virtual void		Update(float dt, sint32 iMouseX, sint32 iMouseY);
		void				MouseClick(sint32 iMouseX, sint32 iMouseY);
		void				UpdateSize();

		virtual void		SetPos(sint32 x, sint32 y) { m_iPosX = x; m_iPosY = y; }
		virtual void		Draw() const = 0;

		void				GetSize(sint32& Width, sint32& Height) const { Width = m_iWidth; Height = m_iHeight; }
		sint32				GetPosX() const { return m_iPosX; }
		sint32				GetPosY() const { return m_iPosY; }
		sint32				GetWidth() const { return m_iWidth; }
		sint32				GetHeight() const { return m_iHeight; }

		bool				IsMouseOver() const { return m_bMouseIsOver; }

	protected:
		virtual void		ComputeSize() {}
		virtual void		UpdatePos() {}

		virtual void		OnMouseIn() {}
		virtual void		OnMouseOut() {}
		virtual void		OnMouseClick(sint32 iMouseX, sint32 iMouseY) {}

	public:
		MulticastDelegate<sint32, sint32> OnMouseClickDelegate;

	protected:
		Canvas& m_oCanvas;
		IBTreeBox* m_pParent;

		bool m_bMouseIsOver;

		sint32 m_iPosX;
		sint32 m_iPosY;
		sint32 m_iWidth;
		sint32 m_iHeight;
};

#endif
