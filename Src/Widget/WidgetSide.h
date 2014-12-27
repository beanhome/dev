
#ifndef __WIDGETSIDE_H__
#define __WIDGETSIDE_H__

#include "Utils.h"
#include "WidgetCommon.h"


class WidgetSide
{
public:
	WidgetSide();
	~WidgetSide();

	friend class Widget;

public:
	struct ParentRef
	{
		float m_fRelativePos;
		sint32 m_iPixOffset;
		ParentRef() : m_fRelativePos(0.f), m_iPixOffset(0) {}
		ParentRef(float fRelPos, sint32 iPixOffset) : m_fRelativePos(fRelPos), m_iPixOffset(iPixOffset) {}
		ParentRef(float fRelPos) : m_fRelativePos(fRelPos), m_iPixOffset(0) {}
		ParentRef(sint32 iPixOffset) : m_fRelativePos(0.f), m_iPixOffset(iPixOffset) {}
	};

	struct SelfRef
	{
		WidgetSelfReference::Type m_eType;
		sint32 m_iFixSize;
		SelfRef() : m_eType(WidgetSelfReference::Auto), m_iFixSize(0) {}
		SelfRef(sint32 iSize) : m_eType(WidgetSelfReference::Fix), m_iFixSize(iSize) {}
	};

	struct BrotherRef
	{
		uint32 m_id;
		float m_fRelativePos;
		sint32 m_iPixOffset;
		BrotherRef() : m_id(0), m_fRelativePos(0.f), m_iPixOffset(0) {}
		BrotherRef(uint32 id, float fRelPos, sint32 iPixOffset) : m_id(id), m_fRelativePos(fRelPos), m_iPixOffset(iPixOffset) {}
		BrotherRef(uint32 id, float fRelPos) : m_id(id), m_fRelativePos(fRelPos), m_iPixOffset(0) {}
		BrotherRef(uint32 id, sint32 iPixOffset) : m_id(id), m_fRelativePos(0.f), m_iPixOffset(iPixOffset) {}
	};

	struct ChildRef
	{
		uint32 m_id;
		float m_fRelativePos;
		sint32 m_iPixOffset;
		ChildRef() : m_id(0), m_fRelativePos(0.f), m_iPixOffset(0) {}
		ChildRef(uint32 id, float fRelPos, sint32 iPixOffset) : m_id(id), m_fRelativePos(fRelPos), m_iPixOffset(iPixOffset) {}
		ChildRef(uint32 id, float fRelPos) : m_id(id), m_fRelativePos(fRelPos), m_iPixOffset(0) {}
		ChildRef(uint32 id, sint32 iPixOffset) : m_id(id), m_fRelativePos(0.f), m_iPixOffset(iPixOffset) {}
	};

public:
	void SetProp(const WidgetSide::ParentRef& oParentRef)	{ m_eReference = WidgetReference::Parent;	m_oParentRefProp = oParentRef; }
	void SetProp(const WidgetSide::SelfRef& oSelfRef)		{ m_eReference = WidgetReference::Self;		m_oSelfRefProp = oSelfRef; }
	void SetProp(const WidgetSide::BrotherRef& oBrotherRef)	{ m_eReference = WidgetReference::Brother;	m_oBrotherRefProp = oBrotherRef; }
	void SetProp(const WidgetSide::ChildRef& oChildRef)		{ m_eReference = WidgetReference::Child;	m_oChildRefProp = oChildRef; }

private:
	void DetermineDimension();
	void DetermineDimension_Parent();
	void DetermineDimension_Self();
	void DetermineDimension_Brother();
	void DetermineDimension_Child();
private:
	sint32 m_iPixelPos;

	SideEnum::Type m_eDesignation;
	WidgetDimState::Type m_eState;
	WidgetReference::Type m_eReference;

	Widget* m_pWidget;

	ParentRef m_oParentRefProp;
	SelfRef m_oSelfRefProp;
	BrotherRef m_oBrotherRefProp;
	ChildRef m_oChildRefProp;
};

#endif


