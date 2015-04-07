// EWSimpleWindow.h

#ifndef __EWSIMPLEWINDOW_H__
#define __EWSIMPLEWINDOW_H__

#include "Component/WSimpleWindow.h"
#include "Component/EWWidget.h"

class EWSimpleWindow : public WSimpleWindow, public EWWidget
{
public:
	struct Desc : public WSimpleWindow::Desc
	{
		Desc(const char* _sPath, sint32 m)
			: WSimpleWindow::Desc(_sPath, m)
		{}
	};

public:
	EWSimpleWindow(CanvasBase& oParent, const Desc& oDesc, sint32 id = -1, const string& sName = "unknow");
	EWSimpleWindow(Widget& oParent, const Desc& oDesc, sint32 id = -1, const string& sName = "unknow");

};


#endif /* __EWSIMPLEWINDOW_H__ */

