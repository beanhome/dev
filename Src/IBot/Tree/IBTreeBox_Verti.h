#ifndef __IBTREEBOX_VERTI_H__
#define __IBTREEBOX_VERTI_H__

#include "IBTreeBox_Container.h"
#include "IBTreeBox.h"
#include "Utils.h"
#include "Canvas.h"

class IBTreeBox_Verti : public IBTreeBox_Container
{
	public:
		IBTreeBox_Verti(Canvas& oCanvas, IBTreeBox* pParent);
		virtual ~IBTreeBox_Verti();

	protected:
		virtual void		ComputeSize() override;
		virtual void		UpdatePos() override;
};

#endif
