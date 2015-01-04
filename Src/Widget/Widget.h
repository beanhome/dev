
#ifndef __WIDGET_H__
#define __WIDGET_H__

#include "Canvas.h"
#include "WidgetSide.h"
#include "Utils.h"
#include "WidgetCommon.h"
#include "Color.h"


class Widget : public Canvas
{
public:
	Widget(CanvasBase& oParent, sint32 id = -1, const string& sName = "unknow");
	Widget(Widget& oParent, sint32 id = -1, const string& sName = "unknow");
	void Init();

	~Widget();

public:
	struct WidgetOffset
	{
		float m_fSizeCoeff;
		sint32 m_iFixPixel;
		WidgetOffset() : m_fSizeCoeff(0.f), m_iFixPixel(0) {}
	};

public:
	template<typename T>
	Widget* AddNewChild(typename T::Desc oDesc, sint32 id = -1, const string& sName = "unknow");

	Widget* GetWidgetParent() { return m_pWidgetParent; }
	const Widget* GetWidgetParent() const { return m_pWidgetParent; }
	virtual Widget* GetChild(uint32 id);
	virtual const Widget* GetChild(uint32 id) const;

	void SetSideProp(SideEnum::Type eType, const WidgetSide::ParentRef& oParentRef)		{ m_oSide[eType].SetProp(oParentRef); }
	void SetSideProp(SideEnum::Type eType, const WidgetSide::SelfRef& oSelfRef)			{ m_oSide[eType].SetProp(oSelfRef); }
	void SetSideProp(SideEnum::Type eType, const WidgetSide::BrotherRef& oBrotherRef)	{ m_oSide[eType].SetProp(oBrotherRef); }
	void SetSideProp(SideEnum::Type eType, const WidgetSide::ChildRef& oChildRef)		{ m_oSide[eType].SetProp(oChildRef); }

	void SetMinWidth(sint32 iMinWidth) { m_iMinWidth = iMinWidth; }
	void SetMaxWidth(sint32 iMaxWidth) { m_iMaxWidth = iMaxWidth; }
	void SetMinHeight(sint32 iMinHeight) { m_iMinHeight = iMinHeight; }
	void SetMaxHeight(sint32 iMaxHeight) { m_iMaxHeight = iMaxHeight; }

	void SetDirtySide(SideEnum::Type eSide);
	void NotifyChildDirty(Widget* pChild, SideEnum::Type eSide);
	void NotifyParentDirty(SideEnum::Type eSide);

	sint32 GetMinWidth() const { return m_iMinWidth; }
	sint32 GetMaxWidth() const { return m_iMaxWidth; }
	sint32 GetMinHeight() const { return m_iMinHeight; }
	sint32 GetMaxHeight() const { return m_iMaxHeight; }

	const WidgetOffset& GetHorizOffset() const { return m_oHorizOffset; }
	const WidgetOffset& GetVertiOffset() const { return m_oVertiOffset; }
	void SetHorizOffset(float fSizeCoeff, sint32 iFixPixel) { m_oHorizOffset.m_fSizeCoeff = fSizeCoeff; m_oHorizOffset.m_iFixPixel = iFixPixel; }
	void SetVertiOffset(float fSizeCoeff, sint32 iFixPixel) { m_oVertiOffset.m_fSizeCoeff = fSizeCoeff; m_oVertiOffset.m_iFixPixel = iFixPixel; }

	sint32 GetSideDimension(SideEnum::Type eType, WidgetDimState::Type& eState);
	sint32 GetSidePosition(SideEnum::Type eType, WidgetDimState::Type& eState);
	uint16 GetWidgetWidth(WidgetDimState::Type& eState);
	uint16 GetWidgetHeight(WidgetDimState::Type& eState);

	const WidgetSide& GetSide(SideEnum::Type eType) const { return m_oSide[eType]; }

	virtual sint32 GetAutoWidth() { return 0; }
	virtual sint32 GetAutoHeight() { return 0; }

	sint32 GetChildWidth();
	sint32 GetChildHeight();

	bool IsNear(sint32 x, sint32 y, sint32 m=10) const { return (x>=m_iOrigX-m && x<m_iOrigX+m_iWidth+m && y>=m_iOrigY-m && y<m_iOrigY+m_iHeight+m); }
	bool IsMouseNear(sint32 m=10) const { return IsNear(GetMouseX(), GetMouseY(), m); }

	Widget* GetWidgetHover(sint32 m=10);
	void GetWidgetHover(vector<Widget*>& aWidget, sint32 m=10);
	WidgetSide* GetSideHover(sint32 m=10);

	virtual void Draw() const;

public:
	typedef list<Widget*> ChildrenList;
	void DetermineDimension();
	virtual void OnDimensionChanged(SideEnum::Type eSide) {};
	virtual Widget* GetParentRef() { return this; }
	virtual void InsertChild(Widget* pChild);

protected:
	WidgetDimState::Type m_eDimState;
	sint32 m_id;
	string m_sName;
	WidgetSide m_oSide[SideEnum::Num];
	ChildrenList m_vChildren;

private:
	Widget* m_pWidgetParent;

	WidgetOffset m_oHorizOffset;
	WidgetOffset m_oVertiOffset;

	sint32 m_iMinWidth;
	sint32 m_iMaxWidth;
	sint32 m_iMinHeight;
	sint32 m_iMaxHeight;
};


template<typename T>
Widget* Widget::AddNewChild(typename T::Desc oDesc, sint32 id, const string& sName)
{
	Widget* pWidget = new T(*GetParentRef(), oDesc, id, sName);
	InsertChild(pWidget);
	return pWidget;	
}

#endif

