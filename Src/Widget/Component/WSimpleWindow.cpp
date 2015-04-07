// WSimpleWindow.cpp


#include "GEngine.h"
#include "WSimpleWindow.h"
#include "Image.h"
#include "WDebug.h"

WSimpleWindow::WSimpleWindow(CanvasBase& oParent, WSimpleWindow::Desc oDesc, sint32 id, const string& sName)
	: Widget(oParent, id, sName)
	, m_oDesc(oDesc)
	, m_pChildArea(NULL)
{
	Init();
}

WSimpleWindow::WSimpleWindow(Widget& oParent, WSimpleWindow::Desc oDesc, sint32 id, const string& sName)
	: Widget(oParent, id, sName)
	, m_oDesc(oDesc)
	, m_pChildArea(NULL)
{
	Init();
}

void WSimpleWindow::Init()
{
	m_pImageResource = GetGEngine()->GetImageResource(m_oDesc.sPath);

	if (m_oDesc.iChildArea_Margin != 0)
	{
		m_pChildArea = new Widget(*this, Widget::Desc(), 0, m_sName + "_Area");

		m_vChildren.push_back(m_pChildArea);
		m_pChildArea->SetSideProp(SideEnum::Left,	WidgetSide::ParentRef(0.f, +m_oDesc.iChildArea_Margin));
		m_pChildArea->SetSideProp(SideEnum::Right,	WidgetSide::ParentRef(1.f, -m_oDesc.iChildArea_Margin));
		m_pChildArea->SetSideProp(SideEnum::Top,	WidgetSide::ParentRef(0.f, +m_oDesc.iChildArea_Margin));
		m_pChildArea->SetSideProp(SideEnum::Bottom,	WidgetSide::ParentRef(1.f, -m_oDesc.iChildArea_Margin));
	}
}


WSimpleWindow::~WSimpleWindow()
{
}

void WSimpleWindow::InsertChild(Widget* pChild)
{
	if (m_pChildArea != NULL)
		m_pChildArea->InsertChild(pChild);
	else
		Widget::InsertChild(pChild);
}

Widget* WSimpleWindow::GetChild(uint32 id)
{
	if (m_pChildArea != NULL)
		return m_pChildArea->GetChild(id);
	else
		return Widget::GetChild(id);
}

const Widget* WSimpleWindow::GetChild(uint32 id) const
{
	if (m_pChildArea != NULL)
		return m_pChildArea->GetChild(id);
	else
		return Widget::GetChild(id);
}

void WSimpleWindow::DrawPart(ImageResource* res, sint32 x, sint32 y, uint16 w, uint16 h) const
{
	DrawImage(*res, x + w/2, y + h/2, w, h, 0, 0, res->GetWidth(), res->GetHeight());
}

void WSimpleWindow::Draw() const
{
	uint16 w = GetWidth();
	uint16 h = GetHeight();

	uint16 rw = m_pImageResource->GetWidth() / 3;
	uint16 rh = m_pImageResource->GetHeight() / 3;

	DrawImage(*m_pImageResource, 0,		0,		rw,		rh,		0,		0,		rw,	rh);
	DrawImage(*m_pImageResource, rw,	0,		w-rw*2,	rh,		rw,		0,		rw, rh);
	DrawImage(*m_pImageResource, w-rw,	0,		rw,		rh,		2*rw,	0,		rw, rh);

	// @tofix +1 for linux
	DrawImage(*m_pImageResource, 0,		rh,		rw,		h-rh*2+1, 0,		rh,		rw, rh);
	DrawImage(*m_pImageResource, rw,	rh,		w-rw*2,	h-rh*2+1, rw,		rh,		rw, rh);
	DrawImage(*m_pImageResource, w-rw,	rh,		rw,		h-rh*2+1, 2*rw,	rh,		rw, rh);

	DrawImage(*m_pImageResource, 0,		h-rh,	rw,		rh,		0,		2*rh,	rw, rh);
	DrawImage(*m_pImageResource, rw,	h-rh,	w-rw*2,	rh,		rw,		2*rh,	rw, rh);
	DrawImage(*m_pImageResource, w-rw,	h-rh,	rw,		rh,		2*rw,	2*rh,	rw, rh);

	Widget::Draw();
}

sint32 WSimpleWindow::GetAutoWidth()
{
	return m_pImageResource->GetWidth();
}

sint32 WSimpleWindow::GetAutoHeight()
{
	return m_pImageResource->GetHeight();
}
