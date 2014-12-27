
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
	Widget(CanvasBase& oParent);
	Widget(CanvasBase& oParent, sint32 id, const string& sName);
	Widget(CanvasBase& oParent, const string& sName);
	Widget(CanvasBase& oParent, sint32 id);
	Widget(Widget& oParent);
	Widget(Widget& oParent, sint32 id, const string& sName);
	Widget(Widget& oParent, const string& sName);
	Widget(Widget& oParent, sint32 id);
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
	Widget* AddNewChild(sint32 id, const string& sName);
	Widget* AddNewChild(const string& sName);
	Widget* AddNewChild(sint32 id);
	Widget* AddNewChild();

	Widget* GetWidgetParent() { return m_pWidgetParent; }
	Widget* GetChild(uint32 id);

	void SetSideProp(SideEnum::Type eType, const WidgetSide::ParentRef& oParentRef)		{ m_oSide[eType].SetProp(oParentRef); }
	void SetSideProp(SideEnum::Type eType, const WidgetSide::SelfRef& oSelfRef)			{ m_oSide[eType].SetProp(oSelfRef); }
	void SetSideProp(SideEnum::Type eType, const WidgetSide::BrotherRef& oBrotherRef)	{ m_oSide[eType].SetProp(oBrotherRef); }
	void SetSideProp(SideEnum::Type eType, const WidgetSide::ChildRef& oChildRef)		{ m_oSide[eType].SetProp(oChildRef); }

	void SetMinWidth(sint32 iMinWidth) { m_iMinWidth = iMinWidth; }
	void SetMaxWidth(sint32 iMaxWidth) { m_iMaxWidth = iMaxWidth; }
	void SetMinHeight(sint32 iMinHeight) { m_iMinHeight = iMinHeight; }
	void SetMaxHeight(sint32 iMaxHeight) { m_iMaxHeight = iMaxHeight; }

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
	uint16 GetWidth(WidgetDimState::Type& eState);
	uint16 GetHeight(WidgetDimState::Type& eState);

	const WidgetSide& GetSide(SideEnum::Type eType) const { return m_oSide[eType]; }

	sint32 GetChildWidth();
	sint32 GetChildHeight();

	//uint16 GetSize(SideEnum::Type);

	virtual void Draw() const;

public:
	typedef list<Widget*> ChildrenList;
	void DetermineDimension();

private:
	Widget* m_pWidgetParent;
	sint32 m_id;
	string m_sName;
	WidgetSide m_oSide[SideEnum::Num];

	WidgetOffset m_oHorizOffset;
	WidgetOffset m_oVertiOffset;

	sint32 m_iMinWidth;
	sint32 m_iMaxWidth;
	sint32 m_iMinHeight;
	sint32 m_iMaxHeight;

	WidgetDimState::Type m_eDimState;

	ChildrenList m_vChildren;

	static Color s_oStateColor[WidgetDimState::Num];
};

#endif

