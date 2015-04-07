// EditableWidget.h

#ifndef __EDITABLEWIDGET_H__
#define __EDITABLEWIDGET_H__


class Widget;

class EditableWidget
{
public:
	EditableWidget() {}
	virtual ~EditableWidget() {}

	virtual void CreateProperties(Widget* pRoot) = 0;
};


#endif /* __EDITABLEWIDGET_H__ */
