#ifndef __IBLOGBOX_H__
#define __IBLOGBOX_H__

#include "Utils.h"
#include "Color.h"
#include "Canvas.h"

class IBLogBox
{
	public:
		IBLogBox();
		virtual ~IBLogBox();

	public:
		virtual void		Refresh(Canvas& oCanvas);
		virtual void		Draw(Canvas& oCanvas, sint32 x, sint32 y) = 0;

		void				GetSize(sint32& Width, sint32& Height) const { Width = m_iWidth; Height = m_iHeight; }
		sint32				GetWidth() const { return m_iWidth; }
		sint32				GetHeight() const { return m_iHeight; }

	protected:
		virtual void		Size(Canvas& oCanvas, sint32& Width, sint32& Height) = 0;

	private:
		bool m_bExtended;
		bool m_bFolded;

		sint32 m_iWidth;
		sint32 m_iHeight;
};

#endif
