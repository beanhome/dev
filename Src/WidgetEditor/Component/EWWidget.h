// EWWidget.h

#ifndef __EWWIDGET_H__
#define __EWWIDGET_H__

#include "Widget.h"
#include "EditableWidget.h"

class EWWidget : virtual public Widget, public EditableWidget
{
public:
	EWWidget(CanvasBase& oParent, sint32 id = -1, const string& sName = "unknow");
	EWWidget(Widget& oParent, sint32 id = -1, const string& sName = "unknow");
	EWWidget(CanvasBase& oParent, const Desc& oDesc, sint32 id = -1, const string& sName = "unknow");
	EWWidget(Widget& oParent, const Desc& oDesc, sint32 id = -1, const string& sName = "unknow");
	virtual ~EWWidget();

	virtual void CreateProperties(Widget* pRoot) override;
};


#endif /* __EWWIDGET_H__ */

