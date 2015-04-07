// EWSimpleWindow.cpp

#include "EWSimpleWindow.h"

EWSimpleWindow::EWSimpleWindow(CanvasBase& oParent, const Desc& oDesc, sint32 id, const string& sName)
	: WSimpleWindow(oParent, oDesc, id, sName)
	, EWWidget(oParent, id, sName)
	, Widget(oParent, id, sName)
{
}

EWSimpleWindow::EWSimpleWindow(Widget& oParent, const Desc& oDesc, sint32 id, const string& sName)
	: WSimpleWindow(oParent, oDesc, id, sName)
	, EWWidget(oParent, id, sName)
	, Widget(oParent, id, sName)
{
}
