// WWindow.cpp


#include "GEngine.h"
#include "WWindow.h"
#include "Image.h"
#include "WDebug.h"

WWindow::WWindow(CanvasBase& oParent, WWindow::Desc oDesc, sint32 id, const string& sName)
	: Widget(oParent, id, sName)
	, m_oDesc(oDesc)
{
	Init();
}

WWindow::WWindow(Widget& oParent, WWindow::Desc oDesc, sint32 id, const string& sName)
	: Widget(oParent, id, sName)
	, m_oDesc(oDesc)
{
	Init();
}

void WWindow::Init()
{
	for (uint32 i=0 ; i<WinPart::Num ; ++i)
	{
		string sPath= FormatString("%s%s%s.%s", DATA_DIR, m_oDesc.sBasePath, WinPart::ToString[i], m_oDesc.sExt);
		m_pImageResource[i] = GetGEngine()->GetImageResource(sPath.c_str());
	}

	m_pChildArea = new WDebug(*this, WDebug::Desc(), 0, m_sName + "_Area");
	m_vChildren.push_back(m_pChildArea);
	m_pChildArea->SetSideProp(SideEnum::Left, WidgetSide::ParentRef(m_oDesc.m_iChildArea_LeftMargin));
	m_pChildArea->SetSideProp(SideEnum::Right, WidgetSide::ParentRef(1.f, -m_oDesc.m_iChildArea_RightMargin));
	m_pChildArea->SetSideProp(SideEnum::Top, WidgetSide::ParentRef(m_oDesc.m_iChildArea_TopMargin));
	m_pChildArea->SetSideProp(SideEnum::Bottom, WidgetSide::ParentRef(1.f, -m_oDesc.m_iChildArea_BottomMargin));
}


WWindow::~WWindow()
{
}

void WWindow::InsertChild(Widget* pChild)
{
	m_pChildArea->InsertChild(pChild);
}

Widget* WWindow::GetChild(uint32 id)
{
	return m_pChildArea->GetChild(id);
}

const Widget* WWindow::GetChild(uint32 id) const
{
	return m_pChildArea->GetChild(id);
}


void WWindow::DrawPart(ImageResource* res, sint32 x, sint32 y, uint16 w, uint16 h) const
{
	DrawImage(*res, x + w/2, y + h/2, w, h, 0, 0, res->GetWidth(), res->GetHeight());
}

void WWindow::Draw() const
{
	uint16 w = GetWidth();
	uint16 h = GetHeight();
	uint16 lm = m_pImageResource[WinPart::TL]->GetWidth();
	uint16 tm = m_pImageResource[WinPart::TL]->GetHeight();
	uint16 rm = m_pImageResource[WinPart::BR]->GetWidth();
	uint16 bm = m_pImageResource[WinPart::BR]->GetHeight();

	DrawPart(m_pImageResource[WinPart::TL], 0,		0,		lm,			tm);
	DrawPart(m_pImageResource[WinPart::TC], lm,		0,		w-lm-rm,	tm);
	DrawPart(m_pImageResource[WinPart::TR], w-rm,	0,		rm,			tm);
	DrawPart(m_pImageResource[WinPart::CL], 0,		tm,		lm,			h-tm-bm);
	DrawPart(m_pImageResource[WinPart::CC], lm,		tm,		w-lm-rm,	h-tm-bm);
	DrawPart(m_pImageResource[WinPart::CR], w-rm,	tm,		rm,			h-tm-bm);
	DrawPart(m_pImageResource[WinPart::BL], 0,		h-bm,	lm,			bm);
	DrawPart(m_pImageResource[WinPart::BC], lm,		h-bm,	w-lm-rm,	bm);
	DrawPart(m_pImageResource[WinPart::BR], w-rm,	h-bm,	rm,			bm);

	Widget::Draw();
}

sint32 WWindow::GetAutoWidth()
{
	return m_pImageResource[0]->GetWidth();
}

sint32 WWindow::GetAutoHeight()
{
	return m_pImageResource[0]->GetHeight();
}
