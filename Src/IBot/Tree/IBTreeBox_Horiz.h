#ifndef __IBTREEBOX_HORIZ_H__
#define __IBTREEBOX_HORIZ_H__

#include "IBTreeBox_Container.h"
#include "IBTreeBox.h"
#include "Utils.h"
#include "Canvas.h"

class IBTreeBox_Horiz : public IBTreeBox_Container
{
	public:
		IBTreeBox_Horiz(Canvas& oCanvas, IBTreeBox* pParent);
		virtual ~IBTreeBox_Horiz();

	protected:
		virtual void		ComputeSize() override;
		virtual void		UpdatePos() override;
};

#endif
