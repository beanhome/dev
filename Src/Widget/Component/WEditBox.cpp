// WEditBox.cpp


#include "GEngine.h"
#include "WEditBox.h"
#include "Image.h"
#include "WEditText.h"

WEditBox::WEditBox(CanvasBase& oParent, WEditBox::Desc oDesc, sint32 id, const string& sName)
	: WSimpleWindow(oParent, oDesc, id, sName)
	, Widget(oParent, id, sName)
	, m_oDesc(oDesc)
{
	Init();
}

WEditBox::WEditBox(Widget& oParent, WEditBox::Desc oDesc, sint32 id, const string& sName)
	: WSimpleWindow(oParent, oDesc, id, sName)
	, Widget(oParent, id, sName)
	, m_oDesc(oDesc)
{
	Init();
}

void WEditBox::Init()
{
	m_pChildArea = new WEditText(*this, m_oDesc.oTextDesc, 0, m_sName + "_Text");

	m_vChildren.push_back(m_pChildArea);
	m_pChildArea->SetSideProp(SideEnum::Left,	WidgetSide::ParentRef(0.f, +m_oDesc.iChildArea_Margin));
	m_pChildArea->SetSideProp(SideEnum::Right,	WidgetSide::ParentRef(1.f, -m_oDesc.iChildArea_Margin));
	m_pChildArea->SetSideProp(SideEnum::Top,	WidgetSide::ParentRef(0.f, +m_oDesc.iChildArea_Margin));
	m_pChildArea->SetSideProp(SideEnum::Bottom,	WidgetSide::ParentRef(1.f, -m_oDesc.iChildArea_Margin));

	m_iIndex = m_oDesc.oTextDesc.sText.length();
}


WEditBox::~WEditBox()
{
}

void WEditBox::SetText(const string& text)
{
	if (m_pChildArea != NULL)
		static_cast<WEditText*>(m_pChildArea)->SetText(text);
}

/*
sint32 WEditBox::GetAutoWidth()
{
	return 
	m_oDesc.iChildArea_Margin
}

sint32 WEditBox::GetAutoHeight()
{

}
*/


