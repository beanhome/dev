// EWWidget.cpp

#include "Component/EWWidget.h"
#include "Widget.h"
#include "Component/WEditBox.h"

EWWidget::EWWidget(CanvasBase& oParent, sint32 id, const string& sName)
	: Widget(oParent, id, sName)
{
}

EWWidget::EWWidget(Widget& oParent, sint32 id, const string& sName)
	: Widget(oParent, id, sName)
{
}

EWWidget::EWWidget(CanvasBase& oParent, const Desc& oDesc, sint32 id, const string& sName)
	: Widget(oParent, oDesc, id, sName)
{
}

EWWidget::EWWidget(Widget& oParent, const Desc& oDesc, sint32 id, const string& sName)
	: Widget(oParent, oDesc, id, sName)
{
}

EWWidget::~EWWidget()
{
}

void EWWidget::CreateProperties(Widget* pRoot)
{
	string id = FormatString("%d", m_id);
	WEditBox* pId = pRoot->AddNewChild<WEditBox>(WEditBox::Desc("editbox.png", 8, id, 12, LeftTop, 128, 128, 128, "calibrib.ttf"), 0, "id");
	pId->SetSideProp(SideEnum::Top,			WidgetSide::ParentRef(0.f, 0));
	pId->SetSideProp(SideEnum::Bottom,		WidgetSide::SelfRef());
	pId->SetSideProp(SideEnum::Left,		WidgetSide::ParentRef(0.f, 0));
	pId->SetSideProp(SideEnum::Right,		WidgetSide::ParentRef(1.f, 0));
	//pId->SetText(FormatString("%d", id));

	WEditBox* pName = pRoot->AddNewChild<WEditBox>(WEditBox::Desc("editbox.png", 8, m_sName, 12, LeftTop, 128, 128, 128, "calibrib.ttf"), 1, "name");
	pName->SetSideProp(SideEnum::Top,		WidgetSide::BrotherRef(0, 1.f, 5));
	pName->SetSideProp(SideEnum::Bottom,	WidgetSide::SelfRef());
	pName->SetSideProp(SideEnum::Left,		WidgetSide::ParentRef(0.f, 0));
	pName->SetSideProp(SideEnum::Right,		WidgetSide::ParentRef(1.f, 0));

	//pName->SetText(m_sName);
}








