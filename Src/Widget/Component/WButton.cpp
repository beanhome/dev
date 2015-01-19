// WButton.cpp

#include "GEngine.h"
#include "WButton.h"
#include "Image.h"
#include "WDebug.h"
#include "Event.h"
#include "Functor.h"

WButton::WButton(CanvasBase& oParent, WButton::Desc oDesc, sint32 id, const string& sName)
	: Widget(oParent, id, sName)
	, m_oDesc(oDesc)
	, m_eButtonState(ButtonState::Default)
	//, m_pApp(NULL)
	//, m_pOnClickEvent(NULL)
	, m_pOnClickFunctor(NULL)
{
	Init();
}

WButton::WButton(Widget& oParent, WButton::Desc oDesc, sint32 id, const string& sName)
	: Widget(oParent, id, sName)
	, m_oDesc(oDesc)
	, m_eButtonState(ButtonState::Default)
	//, m_pApp(NULL)
	//, m_pOnClickEvent(NULL)
	, m_pOnClickFunctor(NULL)
{
	Init();
}

void WButton::Init()
{
	for (uint32 i=0 ; i<ButtonState::Num ; ++i)
	{
		string sPath = FormatString("%s%s%s", m_oDesc.sBasePath, ButtonState::ToSuffix[i], m_oDesc.sExt);
		m_pImageResource[i] = GetGEngine()->GetImageResource(sPath.c_str());
	}

	//m_pChildArea = new WDebug(*this, WDebug::Desc(), 0, m_sName + "_Area");
	m_pChildArea = new Widget(*this, Widget::Desc(), 0, m_sName + "_Area");
	m_vChildren.push_back(m_pChildArea);
	m_pChildArea->SetSideProp(SideEnum::Left, WidgetSide::ParentRef(m_oDesc.iChildArea_Margin));
	m_pChildArea->SetSideProp(SideEnum::Right, WidgetSide::ParentRef(1.f, -m_oDesc.iChildArea_Margin));
	m_pChildArea->SetSideProp(SideEnum::Top, WidgetSide::ParentRef(m_oDesc.iChildArea_Margin));
	m_pChildArea->SetSideProp(SideEnum::Bottom, WidgetSide::ParentRef(1.f, -m_oDesc.iChildArea_Margin));
}


WButton::~WButton()
{
	if (m_pOnClickFunctor != NULL)
		delete m_pOnClickFunctor;
}

void WButton::InsertChild(Widget* pChild)
{
	m_pChildArea->InsertChild(pChild);
}

Widget* WButton::GetChild(uint32 id)
{
	return m_pChildArea->GetChild(id);
}

const Widget* WButton::GetChild(uint32 id) const
{
	return m_pChildArea->GetChild(id);
}

void WButton::Draw() const
{
	ImageResource* pRes = m_pImageResource[m_eButtonState];

	DrawImage(*pRes, 0, 0, GetWidth(), GetHeight(), 0, 0, pRes->GetWidth(), pRes->GetHeight());

	Widget::Draw();
}

sint32 WButton::GetAutoWidth()
{
	return m_pImageResource[m_eButtonState]->GetWidth();
}

sint32 WButton::GetAutoHeight()
{
	return m_pImageResource[m_eButtonState]->GetHeight();
}

void WButton::OnFocusEnter()
{
	Widget::OnFocusEnter();

	m_eButtonState = ButtonState::Focus;
}

void WButton::OnFocusExit()
{
	Widget::OnFocusExit();

	m_eButtonState = ButtonState::Default;
}

void WButton::CatchEvent(Event* pEvent)
{
	if (pEvent->IsMouse())
	{
		if (pEvent->GetMouseEvent() == LeftDown)
		{
			m_eButtonState = ButtonState::Pressed;
		}
		else if (pEvent->GetMouseEvent() == LeftUp)
		{
			m_eButtonState = ButtonState::Focus;
			OnClick();
		}
	}
}
