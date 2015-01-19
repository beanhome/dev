
#ifndef __WIDGETEDITOR_H__
#define __WIDGETEDITOR_H__

#include "Utils.h"
#include "GApp.h"
#include "GEngine_SDL.h"
#include "Functor.h"

class GEngine;
class Widget;
class WidgetSide;
class CanvasBase;
class Event;
class Functor_Base;

class WidgetEditor : public GApp<GEngine_SDL>
{
public:
	WidgetEditor(int w, int h, const char* rootpath);
	~WidgetEditor();

	virtual int Update(float dt);
	virtual int Draw();

private:
	void InitBase();
	Widget* FindHoverWidget(sint32 m=10);
	void FindHoverWidget(vector<Widget*>& aWidget, sint32 m=10);

	void DrawWidget(const Widget* pWidget, bool bReal, uint8 r, uint8 g, uint8 b);

	void DrawSide(WidgetSide* pHoverSide);
	void DrawSide_ParentRef(WidgetSide* pSide);
	void DrawSide_SelfRef(WidgetSide* pSide);
	void DrawSide_SelfRef_Auto(WidgetSide* pSide);
	void DrawSide_SelfRef_Fix(WidgetSide* pSide);
	void DrawSide_BrotherRef(WidgetSide* pSide);
	void DrawSide_ChildRef(WidgetSide* pSide);
	void DrawSide_Offset(WidgetSide* pSide);

	enum Orient { Horiz, Verti };
	void DrawLerpArrow(const CanvasBase& oParent, sint32 x1, sint32 y1, sint32 x2, sint32 y2, float fRatio, Orient eOrient, uint8 r, uint8 g, uint8 b);
	void DrawPixArrow(const CanvasBase& oParent, sint32 x1, sint32 y1, sint32 x2, sint32 y2, Orient eOrient, uint8 r, uint8 g, uint8 b);
	void DrawCoeffArrow(const CanvasBase& oParent, sint32 x1, sint32 y1, sint32 x2, sint32 y2, float fCoeff, Orient eOrient, uint8 r, uint8 g, uint8 b);

	virtual void CatchEvent(Event* pEvent);
	void UpateFocus();
	void ForwardEvent(Event* pEvent);

	void OnClick(Widget* pWidget);
	void OnEnter(Widget* pWidget);
	void OnExit(Widget* pWidget);

private:
	Widget* m_pMainWin;
	WidgetSide* m_pNearestSide;
};
#endif

