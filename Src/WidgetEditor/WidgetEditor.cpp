// WidgetEditor.cpp

#include "WidgetEditor.h"

#include "GEngine.h"
#include "Widget.h"
#include "Event.h"
#include "EventManager.h"
#include "Component/WDebug.h"
#include "Component/WImage.h"
#include "Component/WText.h"
#include "Component/WWindow.h"
#include "Component/WBackground.h"
#include "Component/WButton.h"
#include "Component/WSimpleWindow.h"
#include "Component/WEditBox.h"
#include "Functor.h"

WidgetEditor::WidgetEditor(int w, int h, const char* rootpath)
	: GApp<GEngine_SDL>(w, h, rootpath)
{
	m_pMainWin = new WBackground(*m_pEngine, WBackground::Desc("bg.png"), 0, "main");
	//m_pMainWin = new WDebug(m_oGEngine, WDebug::Desc(), 0, "main");
	//m_pMainWin->SetOrigX(50);
	//m_pMainWin->SetOrigY(50);

	m_pEngine->SetPrintFont("Arial.ttf", 14);
	m_pMainWin->SetSideProp(SideEnum::Left,		WidgetSide::ParentRef(0.f, 10));
	m_pMainWin->SetSideProp(SideEnum::Right,	WidgetSide::ParentRef(1.f, -10));
	m_pMainWin->SetSideProp(SideEnum::Top,		WidgetSide::ParentRef(0.f, 10));
	m_pMainWin->SetSideProp(SideEnum::Bottom,	WidgetSide::ParentRef(1.f, -10));

	/*
	Widget* pWin = m_pMainWin->AddNewChild<WDebug>(WDebug::Desc(), 0, "sub");
	pWin->SetSideProp(SideEnum::Left,	WidgetSide::ParentRef(0.f, 100));
	pWin->SetSideProp(SideEnum::Right,	WidgetSide::SelfRef(500));
	pWin->SetSideProp(SideEnum::Top,	WidgetSide::ParentRef(0.f, 100));
	pWin->SetSideProp(SideEnum::Bottom,	WidgetSide::SelfRef(500));
	*/

	InitBase();
}

WidgetEditor::~WidgetEditor()
{
	delete m_pMainWin;
}

void WidgetEditor::InitBase()
{
	//Widget* pWin1 = m_pMainWin->AddNewChild<WWindow>(WWindow::Desc("win_", "png", 6, 7, 6, 8), 0, "sub1");
	Widget* pWin1 = m_pMainWin->AddNewChild<WSimpleWindow>(WSimpleWindow::Desc("window.png", 12), 0, "sub1");
	pWin1->SetMinWidth(50);
	pWin1->SetSideProp(SideEnum::Left,		WidgetSide::ParentRef(0.5f));
	pWin1->SetSideProp(SideEnum::Right,		WidgetSide::ChildRef(1, 0.f, 55));
	pWin1->SetSideProp(SideEnum::Top,		WidgetSide::ParentRef(0.25f, 30));
	pWin1->SetSideProp(SideEnum::Bottom,	WidgetSide::ParentRef(0.75f, -30));
	pWin1->SetHorizOffset(-0.5f, 0);

	Widget* pWin11 = pWin1->AddNewChild<WEditBox>(WEditBox::Desc("editbox.png", 8, "Lorem ipsum dolor sit amet", 12, LeftTop, 128, 128, 128, "calibrib.ttf"), 0, "sub11");
	pWin11->SetSideProp(SideEnum::Left,		WidgetSide::ParentRef(0.f, 5));
	pWin11->SetSideProp(SideEnum::Right,	WidgetSide::SelfRef(100));
	pWin11->SetSideProp(SideEnum::Top,		WidgetSide::ParentRef(0.f, 5));
	pWin11->SetSideProp(SideEnum::Bottom,	WidgetSide::SelfRef(100));

	Widget* pWin12 = pWin1->AddNewChild<WDebug>(WDebug::Desc(), 1, "sub12");
	pWin12->SetSideProp(SideEnum::Left,		WidgetSide::BrotherRef(0, 1.f, 25));
	pWin12->SetSideProp(SideEnum::Right,	WidgetSide::SelfRef(100));
	pWin12->SetSideProp(SideEnum::Top,		WidgetSide::ParentRef(0.f, 5));
	pWin12->SetSideProp(SideEnum::Bottom,	WidgetSide::SelfRef(100));

	Widget* pWin2 = m_pMainWin->AddNewChild<WText>(WText::Desc("Lorem ipsum dolor sit amet", 12, LeftTop, 128, 128, 128, "calibrib.ttf"), 1, "sub2");
	pWin2->SetSideProp(SideEnum::Left,		WidgetSide::BrotherRef(0, 1.f, 10));
	pWin2->SetSideProp(SideEnum::Right,		WidgetSide::SelfRef(100));
	pWin2->SetSideProp(SideEnum::Top,		WidgetSide::BrotherRef(0, 0.f, 40));
	pWin2->SetSideProp(SideEnum::Bottom,	WidgetSide::SelfRef());

	WButton* pWin3 = (WButton*) m_pMainWin->AddNewChild<WButton>(WButton::Desc("button_", ".png", 8), 2, "sub3");
	pWin3->SetSideProp(SideEnum::Left,		WidgetSide::BrotherRef(0, 1.f, 10));
	pWin3->SetSideProp(SideEnum::Right,		WidgetSide::SelfRef());
	pWin3->SetSideProp(SideEnum::Top,		WidgetSide::BrotherRef(1, 1.f, 10));
	pWin3->SetSideProp(SideEnum::Bottom,	WidgetSide::SelfRef());
	pWin3->SetOnFocusEnterEvent<WidgetEditor>(this, &WidgetEditor::OnEnter);
	pWin3->SetOnFocusExitEvent<WidgetEditor>(this, &WidgetEditor::OnExit);
	pWin3->SetOnClickEvent<WidgetEditor>(this, &WidgetEditor::OnClick);

	Widget* pWin31 = pWin3->AddNewChild<WText>(WText::Desc("Button", 12, Center, 128, 128, 128, "calibrib.ttf"), 0, "sub31");

	/*
	Widget* pWin4 = m_pMainWin->AddNewChild<WImage>(WImage::Desc("Test/small_01.png"), 3, "sub4");
	pWin4->SetSideProp(SideEnum::Left,		WidgetSide::SelfRef());
	pWin4->SetSideProp(SideEnum::Right,		WidgetSide::ParentRef(1.f, -10));
	pWin4->SetSideProp(SideEnum::Top,		WidgetSide::ParentRef(0.5f));
	pWin4->SetSideProp(SideEnum::Bottom,	WidgetSide::SelfRef());
	pWin4->SetVertiOffset(-0.5f, 0);
	*/
}

void WidgetEditor::OnClick(Widget* pWidget)
{
	LOG("OnClick : %s\n", pWidget->GetName().c_str());
}

void WidgetEditor::OnEnter(Widget* pWidget)
{
	LOG("OnEnter : %s\n", pWidget->GetName().c_str());
}

void WidgetEditor::OnExit(Widget* pWidget)
{
	LOG("OnExit : %s\n", pWidget->GetName().c_str());
}


int WidgetEditor::Update(float dt)
{
	m_pMainWin->DetermineDimension();

	sint32 iMargin = 20;
	vector<Widget*> aWidget;
	aWidget.clear();

	FindHoverWidget(aWidget, iMargin);

	m_pNearestSide = NULL;
	sint32 iBestDist = 0x7FFFFFFF;
	for (uint32 i=0 ; i<aWidget.size() ; ++i)
	{
		WidgetSide* pSide = aWidget[i]->GetSideHover(iMargin);
		if (pSide == NULL)
			continue;

		sint32 iDist = pSide->GetMouseDist();
		if (m_pNearestSide == NULL || iDist < iBestDist)
		{
			m_pNearestSide = pSide;
			iBestDist = iDist;
		}
	}

	return 0;
}

int WidgetEditor::Draw()
{
	m_pMainWin->Draw();

	/*
	if (m_pNearestSide != NULL)
	{
		DrawWidget(m_pNearestSide->GetWidget(), false, 192, 192, 192);
		DrawWidget(m_pNearestSide->GetWidget(), true, 96, 96, 96);
		DrawSide(m_pNearestSide);
	}
	*/

	return 0;
}

void WidgetEditor::CatchEvent(Event* pEvent)
{
	GAppBase::CatchEvent(pEvent);

	if (pEvent->IsResize())
	{
		m_pMainWin->SetDirtySide(SideEnum::Right);
		m_pMainWin->SetDirtySide(SideEnum::Bottom);
	}

	if (pEvent->IsMouse())
	{
		if (pEvent->GetMouseEvent() == MouseMove)
			UpateFocus();
		else
			ForwardEvent(pEvent);
	}

	if (pEvent->IsKeyboard())
	{
		ForwardEvent(pEvent);
	}
}


void WidgetEditor::UpateFocus()
{
	m_pMainWin->UpdateFocus();
}

void WidgetEditor::ForwardEvent(Event* pEvent)
{
	if (m_pMainWin->HasFocus())
		m_pMainWin->CatchEvent(pEvent);
}


Widget* WidgetEditor::FindHoverWidget(sint32 m)
{
	return m_pMainWin->GetWidgetHover(m);
}

void WidgetEditor::FindHoverWidget(vector<Widget*>& aWidget, sint32 m)
{
	m_pMainWin->GetWidgetHover(aWidget, m);

}

void WidgetEditor::DrawWidget(const Widget* pWidget, bool bReal, uint8 r, uint8 g, uint8 b)
{
	if (bReal)
	{
		pWidget->GetParent().DrawRect(pWidget->GetPosX(), pWidget->GetPosY(), pWidget->GetWidth(), pWidget->GetHeight(), r, g, b);
	}
	else
	{
		sint32 L = pWidget->GetSide(SideEnum::Left).GetDimension();
		sint32 R = pWidget->GetSide(SideEnum::Right).GetDimension();
		sint32 T = pWidget->GetSide(SideEnum::Top).GetDimension();
		sint32 B = pWidget->GetSide(SideEnum::Bottom).GetDimension();

		pWidget->GetParent().DrawRect(L, T, R-L, B-T, r, g, b);
	}
}

void WidgetEditor::DrawSide(WidgetSide* pSide)
{
	sint32 x1, y1, x2, y2;
	uint8 r = 192;
	uint8 g = 192;
	uint8 b = 0;

	switch (pSide->GetReference())
	{
		case WidgetReference::Parent:		DrawSide_ParentRef(pSide);			break;
		case WidgetReference::Self:			DrawSide_SelfRef(pSide);			break;
		case WidgetReference::Brother:		DrawSide_BrotherRef(pSide);			break;
		case WidgetReference::Child:		DrawSide_ChildRef(pSide);			break;
	}

	DrawSide_Offset(pSide);

	pSide->GetLineCoord(x1, y1, x2, y2, pSide->GetWidget()->GetPosX(), pSide->GetWidget()->GetPosY());
	pSide->GetWidget()->GetParent().DrawLine(x1, y1, x2, y2, r, g, b);
}

void WidgetEditor::DrawSide_ParentRef(WidgetSide* pSide)
{
	sint32 x1, y1, x2, y2;
	sint32 ax1, ay1, ax2, ay2;
	sint32 bx1, by1, bx2, by2;

	const CanvasBase& oParent = pSide->GetWidget()->GetParent();
	const Widget* pWidgetParent = pSide->GetWidget()->GetWidgetParent();

	switch (pSide->GetDesignation())
	{
		case SideEnum::Left:
		case SideEnum::Right:
			if (pWidgetParent != NULL)
			{
				pWidgetParent->GetSide(SideEnum::Left).GetLineCoord(ax1, ay1, ax2, ay2);
				pWidgetParent->GetSide(SideEnum::Right).GetLineCoord(bx1, by1, bx2, by2);
			}
			else
			{
				ax1 = ax2 = 0;
				ay1 = by1 = 0;
				ay2 = by2 = oParent.GetHeight()-1;
				bx1 = bx2 = oParent.GetWidth()-1;
			}

			// Parent Relative
			x1 = x2 = (sint32)Lerp((float)ax1, (float)bx1, pSide->GetParentRefProp().m_fRelativePos);
			y1 = ay1;
			y2 = ay2;
			if (pSide->GetParentRefProp().m_fRelativePos != 0.f && pSide->GetParentRefProp().m_fRelativePos != 1.f)
			{
				oParent.DrawLine(x1, y1, x2, y2, 255, 0, 0);
				DrawLerpArrow(oParent, ax1, ay1, bx2, by2, pSide->GetParentRefProp().m_fRelativePos, Horiz, 255, 0, 0);
			}

			// Parent Offset
			if (pSide->GetParentRefProp().m_iPixOffset != 0)
			{
				DrawPixArrow(oParent, x1, y1, x1 + pSide->GetParentRefProp().m_iPixOffset, y2, Horiz, 0, 255, 0);
				x1 += pSide->GetParentRefProp().m_iPixOffset;
				x2 += pSide->GetParentRefProp().m_iPixOffset;
				oParent.DrawLine(x1, y1, x2, y2, 0, 255, 0);
			}
			break;

		case SideEnum::Top:
		case SideEnum::Bottom:
			if (pWidgetParent != NULL)
			{
				pWidgetParent->GetSide(SideEnum::Top).GetLineCoord(ax1, ay1, ax2, ay2);
				pWidgetParent->GetSide(SideEnum::Bottom).GetLineCoord(bx1, by1, bx2, by2);
			}
			else
			{
				ay1 = ay2 = 0;
				ax1 = bx1 = 0;
				ax2 = bx2 = oParent.GetWidth()-1;
				by1 = by2 = oParent.GetHeight()-1;
			}

			// Parent Relative
			y1 = y2 = (sint32)Lerp((float)ay1, (float)by1, pSide->GetParentRefProp().m_fRelativePos);
			x1 = ax1;
			x2 = ax2;
			if (pSide->GetParentRefProp().m_fRelativePos != 0.f && pSide->GetParentRefProp().m_fRelativePos != 1.f)
			{
				oParent.DrawLine(x1, y1, x2, y2, 255, 0, 0);
				DrawLerpArrow(oParent, ax1, ay1, bx2, by2, pSide->GetParentRefProp().m_fRelativePos, Verti, 255, 0, 0);
			}

			// Parent Offset
			if (pSide->GetParentRefProp().m_iPixOffset != 0)
			{
				DrawPixArrow(oParent, bx1, y1, bx2, y1 + pSide->GetParentRefProp().m_iPixOffset, Verti, 0, 255, 0);
				y1 += pSide->GetParentRefProp().m_iPixOffset;
				y2 += pSide->GetParentRefProp().m_iPixOffset;
				oParent.DrawLine(x1, y1, x2, y2, 0, 255, 0);
			}

			break;
	}
}

void WidgetEditor::DrawSide_SelfRef(WidgetSide* pSide)
{
	switch (pSide->GetSelfRefProp().m_eType)
	{
		case WidgetSelfReference::Auto:	DrawSide_SelfRef_Auto(pSide);		break;
		case WidgetSelfReference::Fix:	DrawSide_SelfRef_Fix(pSide);		break;
	}
}

void WidgetEditor::DrawSide_SelfRef_Auto(WidgetSide* pSide)
{
	switch (pSide->GetDesignation())
	{
		case SideEnum::Left:
		case SideEnum::Right:
		{
			break;
		}

		case SideEnum::Top:
		case SideEnum::Bottom:
		{
			break;
		}
	}
}

void WidgetEditor::DrawSide_SelfRef_Fix(WidgetSide* pSide)
{
	const CanvasBase& oCanvas = *pSide->GetWidget();

	switch (pSide->GetDesignation())
	{
		case SideEnum::Left:
		{
			DrawPixArrow(oCanvas, oCanvas.GetWidth(), 0, 0, oCanvas.GetHeight(), Horiz, 128, 255, 0);
			break;
		}

		case SideEnum::Right:
		{
			DrawPixArrow(oCanvas, 0, 0, oCanvas.GetWidth(), oCanvas.GetHeight(), Horiz, 128, 255, 0);
			break;
		}

		case SideEnum::Top:
		{
			DrawPixArrow(oCanvas, 0, oCanvas.GetHeight(), oCanvas.GetWidth(), 0, Verti, 128, 255, 0);
			break;
		}

		case SideEnum::Bottom:
		{
			DrawPixArrow(oCanvas, 0, 0, oCanvas.GetWidth(), oCanvas.GetHeight(), Verti, 128, 255, 0);
			break;
		}
	}
}

void WidgetEditor::DrawSide_BrotherRef(WidgetSide* pSide)
{
	const Canvas& oCanvas = *pSide->GetWidget();
	const CanvasBase& oParent = oCanvas.GetParent();
	const Widget* pWidget = pSide->GetWidget();
	const Widget* pBrother = pWidget->GetWidgetParent()->GetChild(pSide->GetBrotherRefProp().m_id);
	sint32 ax1, ay1, ax2, ay2;
	sint32 bx1, by1, bx2, by2;

	switch (pSide->GetDesignation())
	{
		case SideEnum::Left:
		case SideEnum::Right:
		{
			pBrother->GetSide(SideEnum::Left).GetLineCoord(ax1, ay1, ax2, ay2, pBrother->GetPosX(), pBrother->GetPosY());
			pBrother->GetSide(SideEnum::Right).GetLineCoord(bx1, by1, bx2, by2, pBrother->GetPosX(), pBrother->GetPosY());

			// Brother Relative
			sint32 x = (sint32)Lerp((float)ax1, (float)bx1, pSide->GetBrotherRefProp().m_fRelativePos);
			if (pSide->GetBrotherRefProp().m_fRelativePos != 0.f && pSide->GetBrotherRefProp().m_fRelativePos != 1.f
			 || pSide->GetBrotherRefProp().m_iPixOffset == 0)
			{
				oParent.DrawLine(x, ay1, x, ay2, 255, 0, 0);
				DrawLerpArrow(oParent, ax1, ay1, bx2, by2, pSide->GetBrotherRefProp().m_fRelativePos, Horiz, 255, 0, 0);
			}

			// Brother Offset
			if (pSide->GetBrotherRefProp().m_iPixOffset != 0)
			{
				DrawPixArrow(oParent, x, ay1, x + pSide->GetBrotherRefProp().m_iPixOffset, ay2, Horiz, 0, 255, 0);
				x += pSide->GetBrotherRefProp().m_iPixOffset;
				oParent.DrawLine(x, ay1, x, ay2, 0, 255, 0);
			}

			break;
		}

		case SideEnum::Top:
		case SideEnum::Bottom:
		{
			pBrother->GetSide(SideEnum::Top).GetLineCoord(ax1, ay1, ax2, ay2, pBrother->GetPosX(), pBrother->GetPosY());
			pBrother->GetSide(SideEnum::Bottom).GetLineCoord(bx1, by1, bx2, by2, pBrother->GetPosX(), pBrother->GetPosY());

			// Brother Relative
			sint32 y = (sint32)Lerp((float)ay1, (float)by1, pSide->GetBrotherRefProp().m_fRelativePos);
			if (pSide->GetBrotherRefProp().m_fRelativePos != 0.f && pSide->GetBrotherRefProp().m_fRelativePos != 1.f
			 || pSide->GetBrotherRefProp().m_iPixOffset == 0)
			{
				oParent.DrawLine(ax1, y, ax2, y, 255, 0, 0);
				DrawLerpArrow(oParent, ax1, ay1, bx2, by2, pSide->GetBrotherRefProp().m_fRelativePos, Verti, 255, 0, 0);
			}

			// Brother Offset
			if (pSide->GetBrotherRefProp().m_iPixOffset != 0)
			{
				DrawPixArrow(oParent, ax1, y, ax2, y + pSide->GetBrotherRefProp().m_iPixOffset, Verti, 0, 255, 0);
				y += pSide->GetBrotherRefProp().m_iPixOffset;
				oParent.DrawLine(ax1, y, ax2, y, 0, 255, 0);
			}
			break;
		}
	}
}

void WidgetEditor::DrawSide_ChildRef(WidgetSide* pSide)
{
	const Canvas& oCanvas = *pSide->GetWidget();
	const Widget* pWidget = pSide->GetWidget();
	const Widget* pChild = pWidget->GetChild(pSide->GetChildRefProp().m_id);
	sint32 ax1, ay1, ax2, ay2;
	sint32 bx1, by1, bx2, by2;

	switch (pSide->GetDesignation())
	{
		case SideEnum::Left:
		case SideEnum::Right:
		{
			pChild->GetSide(SideEnum::Left).GetLineCoord(ax1, ay1, ax2, ay2, pChild->GetPosX(), pChild->GetPosY());
			pChild->GetSide(SideEnum::Right).GetLineCoord(bx1, by1, bx2, by2, pChild->GetPosX(), pChild->GetPosY());

			// Brother Relative
			sint32 x = (sint32)Lerp((float)ax1, (float)bx1, pSide->GetChildRefProp().m_fRelativePos);
			if (pSide->GetChildRefProp().m_fRelativePos != 0.f && pSide->GetChildRefProp().m_fRelativePos != 1.f
			 || pSide->GetChildRefProp().m_iPixOffset == 0)
			{
				oCanvas.DrawLine(x, ay1, x, ay2, 255, 0, 0);
				DrawLerpArrow(oCanvas, ax1, ay1, bx2, by2, pSide->GetChildRefProp().m_fRelativePos, Horiz, 255, 0, 0);
			}

			// Brother Offset
			if (pSide->GetChildRefProp().m_iPixOffset != 0)
			{
				DrawPixArrow(oCanvas, x, ay1, x + pSide->GetChildRefProp().m_iPixOffset, ay2, Horiz, 0, 255, 0);
				x += pSide->GetChildRefProp().m_iPixOffset;
				oCanvas.DrawLine(x, ay1, x, ay2, 0, 255, 0);
			}

			break;
		}

	case SideEnum::Top:
	case SideEnum::Bottom:
		{
			pChild->GetSide(SideEnum::Top).GetLineCoord(ax1, ay1, ax2, ay2, pChild->GetPosX(), pChild->GetPosY());
			pChild->GetSide(SideEnum::Bottom).GetLineCoord(bx1, by1, bx2, by2, pChild->GetPosX(), pChild->GetPosY());

			// Brother Relative
			sint32 y = (sint32)Lerp((float)ay1, (float)by1, pSide->GetChildRefProp().m_fRelativePos);
			if (pSide->GetChildRefProp().m_fRelativePos != 0.f && pSide->GetChildRefProp().m_fRelativePos != 1.f
			 || pSide->GetChildRefProp().m_iPixOffset == 0)
			{
				oCanvas.DrawLine(ax1, y, ax2, y, 255, 0, 0);
				DrawLerpArrow(oCanvas, ax1, ay1, bx2, by2, pSide->GetChildRefProp().m_fRelativePos, Verti, 255, 0, 0);
			}

			// Brother Offset
			if (pSide->GetChildRefProp().m_iPixOffset != 0)
			{
				DrawPixArrow(oCanvas, ax1, y, ax1 + pSide->GetChildRefProp().m_iPixOffset, y, Horiz, 0, 255, 0);
				y += pSide->GetChildRefProp().m_iPixOffset;
				oCanvas.DrawLine(ax1, y, ax2, y, 0, 255, 0);
			}
			break;
		}
	}
}

void WidgetEditor::DrawSide_Offset(WidgetSide* pSide)
{
	const Widget* pWidget = pSide->GetWidget();
	const CanvasBase& oParent = pWidget->GetParent();

	switch (pSide->GetDesignation())
	{
		case SideEnum::Left:
		case SideEnum::Right:
		{
			sint32 x, y1, y2;
			x = pSide->GetDimension() + (sint32)(pWidget->GetWidth() * pWidget->GetHorizOffset().m_fSizeCoeff);
			y1 = pWidget->GetSide(SideEnum::Top).GetDimension();
			y2 = pWidget->GetSide(SideEnum::Bottom).GetDimension();
			if (pWidget->GetHorizOffset().m_fSizeCoeff != 0.f)
			{
				if (pWidget->GetHorizOffset().m_iFixPixel != 0)
					oParent.DrawLine(x, y1, x, y2, 0, 255, 255);

				DrawCoeffArrow(oParent, pSide->GetDimension(), y1, x, y2, pWidget->GetHorizOffset().m_fSizeCoeff, Horiz, 0, 255, 255);
			}

			if (pWidget->GetHorizOffset().m_iFixPixel != 0)
			{
				sint32 p = x;
				x += pWidget->GetHorizOffset().m_iFixPixel;

				oParent.DrawLine(x, y1, x, y2, 0, 255, 255);

				DrawPixArrow(oParent, p, y1, x, y2, Horiz, 0, 255, 128);
			}
			break;
		}

		case SideEnum::Top:
		case SideEnum::Bottom:
		{
			sint32 x1, x2, y;
			x1 = pWidget->GetSide(SideEnum::Left).GetDimension();
			x2 = pWidget->GetSide(SideEnum::Right).GetDimension();
			y = pSide->GetDimension() + (sint32)(pWidget->GetHeight() * pWidget->GetVertiOffset().m_fSizeCoeff);
			if (pWidget->GetVertiOffset().m_fSizeCoeff != 0.f)
			{
				if (pWidget->GetVertiOffset().m_iFixPixel != 0)
					oParent.DrawLine(x1, y, x2, y, 0, 255, 255);

				DrawCoeffArrow(oParent, x1, pSide->GetDimension(), x2, y, pWidget->GetVertiOffset().m_fSizeCoeff, Verti, 0, 255, 255);
			}

			if (pWidget->GetVertiOffset().m_iFixPixel != 0)
			{
				sint32 p = y;
				y += pWidget->GetVertiOffset().m_iFixPixel;

				oParent.DrawLine(x1, y, x2, y, 0, 255, 255);

				DrawPixArrow(oParent, x1, p, x2, y, Verti, 0, 255, 128);
			}
			break;
		}
	}
}


void WidgetEditor::DrawLerpArrow( const CanvasBase& oParent, sint32 x1, sint32 y1, sint32 x2, sint32 y2, float fRatio, Orient eOrient, uint8 r, uint8 g, uint8 b)
{
	sint32 iOffset = 0;

	switch (eOrient)
	{
		case Horiz:
			if (fRatio > 0.5f)
			{
				x1 = (sint32)Lerp((float)x1, (float)x2, fRatio);
				fRatio = 1.f - fRatio;
			}
			else
			{
				x2 = (sint32)Lerp((float)x1, (float)x2, fRatio);
			}

			iOffset = (y2 - y1) / 5;

			y2 = y1 += iOffset;
			oParent.DrawLine(x1, y1, x2, y2, r, g, b);

			if (abs(x1-x2) > 10)
			{
				oParent.DrawLine(x1, y1, x1+5, y1+5, r, g, b);
				oParent.DrawLine(x1, y1, x1+5, y1-5, r, g, b);
				oParent.DrawLine(x2, y2, x2-5, y2+5, r, g, b);
				oParent.DrawLine(x2, y2, x2-5, y2-5, r, g, b);
				oParent.Print(x1+8, y1, oParent.GetPrintFont(), 15, LeftTop, r, g, b, "%.1f", fRatio);
			}
			break;

		case Verti:
			if (fRatio > 0.5f)
			{
				y1 = (sint32)Lerp((float)y1, (float)y2, fRatio);
				fRatio = 1.f - fRatio;
			}
			else
			{
				y2 = (sint32)Lerp((float)y1, (float)y2, fRatio);
			}

			iOffset = (x2 - x1) / 5;
			x2 = x1 += iOffset;
			oParent.DrawLine(x1, y1, x2, y2, r, g, b);

			if (abs(y1-y2) > 10)
			{
				oParent.DrawLine(x1, y1, x1+5, y1+5, r, g, b);
				oParent.DrawLine(x1, y1, x1-5, y1+5, r, g, b);
				oParent.DrawLine(x2, y2, x2+5, y2-5, r, g, b);
				oParent.DrawLine(x2, y2, x2-5, y2-5, r, g, b);
				oParent.Print(x1+3, y1+8, oParent.GetPrintFont(), 15, LeftTop, r, g, b, "%.1f", fRatio);
			}
			break;
	}
}

void WidgetEditor::DrawPixArrow( const CanvasBase& oParent, sint32 x1, sint32 y1, sint32 x2, sint32 y2, Orient eOrient, uint8 r, uint8 g, uint8 b )
{
	sint32 iOffset = 0;

	switch (eOrient)
	{
		case Horiz:
			iOffset = (y2 - y1) / 5;

			y2 = y1 += iOffset;
			oParent.DrawLine(x1, y1, x2, y2, r, g, b);

			if (abs(x2 - x1) > 10)
			{
				if (x1 > x2)
				{
					oParent.DrawLine(x2, y2, x2+5, y2+5, r, g, b);
					oParent.DrawLine(x2, y2, x2+5, y2-5, r, g, b);
					oParent.Print(x2+8, y1, oParent.GetPrintFont(), 15, LeftTop, r, g, b, "%d", (x1 - x2));
				}
				else
				{
					oParent.DrawLine(x2, y2, x2-5, y2+5, r, g, b);
					oParent.DrawLine(x2, y2, x2-5, y2-5, r, g, b);
					oParent.Print(x2-8, y1, oParent.GetPrintFont(), 15, RightTop, r, g, b, "%d", (x2 - x1));
				}
			}
			break;

		case Verti:
			iOffset = (x2 - x1) / 5;
			x2 = x1 += iOffset;
			oParent.DrawLine(x1, y1, x2, y2, r, g, b);

			if (abs(y2 - y1) > 10)
			{
				if (y1 > y2)
				{
					oParent.DrawLine(x2, y2, x2+5, y2+5, r, g, b);
					oParent.DrawLine(x2, y2, x2-5, y2+5, r, g, b);
					oParent.Print(x1+3, y2+8, oParent.GetPrintFont(), 15, LeftTop, r, g, b, "%d", (y1 - y2));
				}
				else
				{
					oParent.DrawLine(x2, y2, x2+5, y2-5, r, g, b);
					oParent.DrawLine(x2, y2, x2-5, y2-5, r, g, b);
					oParent.Print(x1+3, y2-8, oParent.GetPrintFont(), 15, LeftBottom, r, g, b, "%d", (y2 - y1));
				}
			}
			break;
	}
}

void WidgetEditor::DrawCoeffArrow( const CanvasBase& oParent, sint32 x1, sint32 y1, sint32 x2, sint32 y2, float fCoeff, Orient eOrient, uint8 r, uint8 g, uint8 b )
{
	sint32 iOffset = 0;

	switch (eOrient)
	{
		case Horiz:
		{
			iOffset = (y2 - y1) / 5;

			y2 = y1 += iOffset;
			oParent.DrawLine(x1, y1, x2, y2, r, g, b);

			if (abs(x2 - x1) > 10)
			{
				if (x1 > x2)
				{
					oParent.DrawLine(x2, y2, x2+5, y2+5, r, g, b);
					oParent.DrawLine(x2, y2, x2+5, y2-5, r, g, b);
					oParent.Print(x2+8, y1, oParent.GetPrintFont(), 15, LeftTop, r, g, b, "%.1f", fCoeff);
				}
				else
				{
					oParent.DrawLine(x2, y2, x2-5, y2+5, r, g, b);
					oParent.DrawLine(x2, y2, x2-5, y2-5, r, g, b);
					oParent.Print(x2-8, y1, oParent.GetPrintFont(), 15, RightTop, r, g, b, "%.1f", fCoeff);
				}
			}
		}
		break;

		case Verti:
		{
			iOffset = (x2 - x1) / 5;
			x2 = x1 += iOffset;
			oParent.DrawLine(x1, y1, x2, y2, r, g, b);

			if (abs(y2 - y1) > 10)
			{
				if (y1 > y2)
				{
					oParent.DrawLine(x2, y2, x2+5, y2+5, r, g, b);
					oParent.DrawLine(x2, y2, x2-5, y2+5, r, g, b);
					oParent.Print(x1+3, y2+8, oParent.GetPrintFont(), 15, LeftTop, r, g, b, "%.1f", fCoeff);
				}
				else
				{
					oParent.DrawLine(x2, y2, x2+5, y2-5, r, g, b);
					oParent.DrawLine(x2, y2, x2-5, y2-5, r, g, b);
					oParent.Print(x1+3, y2-8, oParent.GetPrintFont(), 15, LeftBottom, r, g, b, "%.1f", fCoeff);
				}
			}
		}
		break;
	}
}





