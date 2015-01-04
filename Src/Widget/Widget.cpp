// Widget.cpp


#include "Widget.h"
#include "Utils.h"
#include "Color.h"

Widget::Widget(CanvasBase& oParent, sint32 id, const string& sName)
	: Canvas(oParent)
	, m_pWidgetParent(NULL)
	, m_id(id)
	, m_sName(sName)
	, m_eDimState(WidgetDimState::Unknown)
{
	Init();
}

Widget::Widget(Widget& oParent, sint32 id, const string& sName)
	: Canvas((CanvasBase&)oParent)
	, m_pWidgetParent(&oParent)
	, m_id(id)
	, m_sName(sName)
	, m_eDimState(WidgetDimState::Unknown)
{
	Init();
}

void Widget::Init()
{
	m_iMinWidth = 0;
	m_iMaxWidth = 0xFFFF;
	m_iMinHeight = 0;
	m_iMaxHeight = 0xFFFF;

	for (uint32 i=0 ; i<SideEnum::Num ; ++i)
	{
		m_oSide[i].m_pWidget = this;
		m_oSide[i].m_eDesignation = (SideEnum::Type)i;

		m_oSide[i].m_eReference = WidgetReference::Parent;

		switch (m_oSide[i].m_eDesignation)
		{
			case SideEnum::Left:	m_oSide[i].m_oParentRefProp.m_fRelativePos = 0.f;	break;
			case SideEnum::Right:	m_oSide[i].m_oParentRefProp.m_fRelativePos = 1.f;	break;
			case SideEnum::Top:		m_oSide[i].m_oParentRefProp.m_fRelativePos = 0.f;	break;
			case SideEnum::Bottom:	m_oSide[i].m_oParentRefProp.m_fRelativePos = 1.f;	break;
		}
	}
}

Widget::~Widget()
{
	for (ChildrenList::const_iterator it = m_vChildren.begin() ; it != m_vChildren.end() ; ++it)
		delete *it;
}

void Widget::InsertChild(Widget* pChild)
{
	m_vChildren.push_back(pChild);
}


sint32 Widget::GetSideDimension(SideEnum::Type eType, WidgetDimState::Type& eState)
{
	m_oSide[eType].DetermineDimension();
	eState = m_oSide[eType].m_eState;
	return m_oSide[eType].m_iPixelPos;
}

sint32 Widget::GetSidePosition(SideEnum::Type eType, WidgetDimState::Type& eState)
{
	sint32 pos = GetSideDimension(eType, eState);

	if (eState != WidgetDimState::Valid)
		return pos;

	switch (eType)
	{
		case SideEnum::Left:
		case SideEnum::Right:
			if (m_oHorizOffset.m_fSizeCoeff != 0.f)
				pos += (sint32)(GetWidgetWidth(eState) * m_oHorizOffset.m_fSizeCoeff);
			pos += m_oHorizOffset.m_iFixPixel;
			break;

		case SideEnum::Top:
		case SideEnum::Bottom:
			if (m_oVertiOffset.m_fSizeCoeff != 0.f)
				pos += (sint32)(GetWidgetHeight(eState) * m_oVertiOffset.m_fSizeCoeff);
			pos += m_oVertiOffset.m_iFixPixel;
			break;
	}

	return pos;
}


uint16 Widget::GetWidgetWidth(WidgetDimState::Type& eState)
{
	switch (m_eDimState)
	{
		case WidgetDimState::Unknown:
			m_oSide[SideEnum::Left].DetermineDimension();
			m_oSide[SideEnum::Right].DetermineDimension();
			if (m_oSide[SideEnum::Left].m_eState == WidgetDimState::Valid
			 && m_oSide[SideEnum::Right].m_eState == WidgetDimState::Valid)
			{
				eState = WidgetDimState::Valid;
				ASSERT(m_oSide[SideEnum::Right].m_iPixelPos - m_oSide[SideEnum::Left].m_iPixelPos > 0);
				return (uint16)(m_oSide[SideEnum::Right].m_iPixelPos - m_oSide[SideEnum::Left].m_iPixelPos);
			}
			else
			{
				eState = WidgetDimState::Invalid;
				return 0;
			}
			break;

		case WidgetDimState::Invalid:
		case WidgetDimState::Process:
			eState = WidgetDimState::Invalid;
			return 0;

		case WidgetDimState::Valid:
			eState = WidgetDimState::Valid; 
			ASSERT(m_oSide[SideEnum::Right].m_iPixelPos - m_oSide[SideEnum::Left].m_iPixelPos > 0);
			return (uint16)(m_oSide[SideEnum::Right].m_iPixelPos - m_oSide[SideEnum::Left].m_iPixelPos);
	}

	return 0;
}

uint16 Widget::GetWidgetHeight(WidgetDimState::Type& eState)
{
	switch (m_eDimState)
	{
		case WidgetDimState::Unknown:
			m_oSide[SideEnum::Top].DetermineDimension();
			m_oSide[SideEnum::Bottom].DetermineDimension();
			if (m_oSide[SideEnum::Top].m_eState == WidgetDimState::Valid
			 && m_oSide[SideEnum::Bottom].m_eState == WidgetDimState::Valid)
			{
				eState = WidgetDimState::Valid;
				ASSERT(m_oSide[SideEnum::Bottom].m_iPixelPos - m_oSide[SideEnum::Top].m_iPixelPos > 0);
				return (uint16)(m_oSide[SideEnum::Bottom].m_iPixelPos - m_oSide[SideEnum::Top].m_iPixelPos);
			}
			else
			{
				eState = WidgetDimState::Invalid;
				return 0;
			}
			break;

		case WidgetDimState::Invalid:
		case WidgetDimState::Process:
			eState = WidgetDimState::Invalid;
			return 0;

		case WidgetDimState::Valid:
			eState = WidgetDimState::Valid;
			ASSERT(m_oSide[SideEnum::Bottom].m_iPixelPos - m_oSide[SideEnum::Top].m_iPixelPos > 0);
			return (uint16)(m_oSide[SideEnum::Bottom].m_iPixelPos - m_oSide[SideEnum::Top].m_iPixelPos);
	}

	return 0;
}

sint32 Widget::GetChildWidth()
{
	sint32 iMin = (sint32)0x7FFF;
	sint32 iMax = (sint32)0xFFFF;
	sint32 iPos = 0;

	WidgetDimState::Type eState;

	for (ChildrenList::iterator it = m_vChildren.begin() ; it != m_vChildren.end() ; ++it)
	{
		Widget* pWin = *it;

		iPos = pWin->GetSidePosition(SideEnum::Left, eState);
		if (eState == WidgetDimState::Valid)
		{
			if (iPos < iMin) iMin = iPos;
			if (iPos > iMax) iMax = iPos;
		}

		iPos = pWin->GetSidePosition(SideEnum::Right, eState);
		if (eState == WidgetDimState::Valid)
		{
			if (iPos < iMin) iMin = iPos;
			if (iPos > iMax) iMax = iPos;
		}
	}

	return iMax - iMin;
}

sint32 Widget::GetChildHeight()
{
	sint32 iMin = (sint32)0x7FFF;
	sint32 iMax = (sint32)0xFFFF;
	sint32 iPos = 0;

	WidgetDimState::Type eState;

	for (ChildrenList::iterator it = m_vChildren.begin() ; it != m_vChildren.end() ; ++it)
	{
		Widget* pWin = *it;

		iPos = pWin->GetSidePosition(SideEnum::Top, eState);
		if (eState == WidgetDimState::Valid)
		{
			if (iPos < iMin) iMin = iPos;
			if (iPos > iMax) iMax = iPos;
		}

		iPos = pWin->GetSidePosition(SideEnum::Bottom, eState);
		if (eState == WidgetDimState::Valid)
		{
			if (iPos < iMin) iMin = iPos;
			if (iPos > iMax) iMax = iPos;
		}
	}

	return iMax - iMin;
}

Widget* Widget::GetChild(uint32 id)
{
	for (ChildrenList::const_iterator it = m_vChildren.begin() ; it != m_vChildren.end() ; ++it)
	{
		Widget* pChild = *it;
		if (pChild->m_id == id)
			return pChild;
	}

	return NULL;
}

const Widget* Widget::GetChild(uint32 id) const
{
	for (ChildrenList::const_iterator it = m_vChildren.begin() ; it != m_vChildren.end() ; ++it)
	{
		Widget* pChild = *it;
		if (pChild->m_id == id)
			return pChild;
	}

	return NULL;
}


void Widget::DetermineDimension()
{
	// may ignore
	switch (m_eDimState)
	{
		case WidgetDimState::Unknown:
		{
			// set in progress
			m_eDimState = WidgetDimState::Process;

			// update each side
			for (uint32 i=0 ; i<SideEnum::Num ; ++i)
			{
				m_oSide[i].DetermineDimension();
			}

			// determine state
			m_eDimState = WidgetDimState::Valid;
			for (uint32 i=0 ; i<SideEnum::Num ; ++i)
			{
				switch (m_oSide[i].m_eState)
				{
					case WidgetDimState::Unknown:	m_eDimState = WidgetDimState::Unknown;	break;
					case WidgetDimState::Invalid:	m_eDimState = WidgetDimState::Invalid;	return;
					case WidgetDimState::Valid:		break;
				}
			}

			// Set to Canvas Size
			if (m_eDimState == WidgetDimState::Valid)
			{
				sint32 iLeft	= m_oSide[SideEnum::Left].m_iPixelPos;
				sint32 iRight	= m_oSide[SideEnum::Right].m_iPixelPos;
				sint32 iTop		= m_oSide[SideEnum::Top].m_iPixelPos;
				sint32 iBottom	= m_oSide[SideEnum::Bottom].m_iPixelPos;

				sint32 iHorizOffset	= (sint32)((iRight - iLeft) * m_oHorizOffset.m_fSizeCoeff) + m_oHorizOffset.m_iFixPixel;
				sint32 iVertiOffset	= (sint32)((iBottom - iTop) * m_oVertiOffset.m_fSizeCoeff) + m_oVertiOffset.m_iFixPixel;

				SetPosX((sint32)(iLeft + iHorizOffset));
				SetPosY((sint32)(iTop + iVertiOffset));
				ASSERT(iRight - iLeft >= 0);
				SetWidth((uint16)(iRight - iLeft));
				ASSERT(iBottom - iTop >= 0);
				SetHeight((uint16)(iBottom - iTop));
			}

			break;
		}

		case WidgetDimState::Process:
			return;

		case WidgetDimState::Invalid:
		case WidgetDimState::Valid:
			break;
	}

	// call for children
	for (ChildrenList::const_iterator it = m_vChildren.begin() ; it != m_vChildren.end() ; ++it)
	{
		Widget* pChild = *it;
		pChild->DetermineDimension();
	}
}

void Widget::SetDirtySide(SideEnum::Type eSide)
{
	m_eDimState = WidgetDimState::Unknown;
	m_oSide[eSide].m_eState = WidgetDimState::Unknown;

	for (uint i=0 ; i<SideEnum::Num ; ++i)
	{
		if (i != eSide
		 && m_oSide[i].m_eState == WidgetDimState::Valid
		 && m_oSide[i].m_eReference == WidgetReference::Self)
		{
			SetDirtySide((SideEnum::Type)i);
		}
	}

	if (m_pWidgetParent != NULL)
		m_pWidgetParent->NotifyChildDirty(this, eSide);

	for (ChildrenList::const_iterator it = m_vChildren.begin() ; it != m_vChildren.end() ; ++it)
	{
		Widget* pChild = *it;
		pChild->NotifyParentDirty(eSide);
	}
}

void Widget::NotifyChildDirty(Widget* pChild, SideEnum::Type eSide)
{
	for (uint i=0 ; i<SideEnum::Num ; ++i)
	{
		if (m_oSide[i].m_eState == WidgetDimState::Valid
		 && m_oSide[i].m_eReference == WidgetReference::Child)
		{
			SetDirtySide((SideEnum::Type)i);
		}
	}

	for (ChildrenList::const_iterator it = m_vChildren.begin() ; it != m_vChildren.end() ; ++it)
	{
		Widget* pOtherChild = *it;

		for (uint i=0 ; i<SideEnum::Num ; ++i)
		{
			if (pOtherChild != pChild
			 && pOtherChild->m_oSide[i].m_eState == WidgetDimState::Valid
			 && pOtherChild->m_oSide[i].m_eReference == WidgetReference::Brother
			 && pOtherChild->m_oSide[i].m_oBrotherRefProp.m_id == pChild->m_id)
				pOtherChild->SetDirtySide((SideEnum::Type)i);
		}
	}
}

void Widget::NotifyParentDirty(SideEnum::Type eSide)
{
	for (uint i=0 ; i<SideEnum::Num ; ++i)
	{
		if (m_oSide[i].m_eState == WidgetDimState::Valid && m_oSide[i].m_eReference == WidgetReference::Parent)
			SetDirtySide((SideEnum::Type)i);
	}
}

Widget* Widget::GetWidgetHover(sint32 m)
{
	if (IsMouseNear(m))
	{
		for (ChildrenList::const_iterator it = m_vChildren.begin() ; it != m_vChildren.end() ; ++it)
		{
			Widget* pChild = *it;
			Widget* pHover = pChild->GetWidgetHover(m);
			if (pHover != NULL)
				return pHover;
		}

		return this;
	}

	return NULL;
}

void Widget::GetWidgetHover(vector<Widget*>& aWidget, sint32 m)
{
	if (IsMouseNear(m))
	{
		aWidget.push_back(this);

		for (ChildrenList::const_iterator it = m_vChildren.begin() ; it != m_vChildren.end() ; ++it)
		{
			Widget* pChild = *it;
			pChild->GetWidgetHover(aWidget, m);
		}
	}
}

WidgetSide* Widget::GetSideHover(sint32 m)
{
	if (!IsMouseNear(m))
		return NULL;

	sint32 x = GetMouseX() - GetOrigX();
	sint32 y = GetMouseY() - GetOrigY();
	uint16 w = GetWidth();
	uint16 h = GetHeight();

	if (x < m	&& y > 0 && y < h)	return &m_oSide[SideEnum::Left];
	if (x > w-m	&& y > 0 && y < h)	return &m_oSide[SideEnum::Right];
	if (y < m	&& x > 0 && x < w)	return &m_oSide[SideEnum::Top];
	if (y > h-m	&& x > 0 && x < w)	return &m_oSide[SideEnum::Bottom];

	return NULL;
}

void Widget::Draw() const
{
	for (ChildrenList::const_iterator it = m_vChildren.begin() ; it != m_vChildren.end() ; ++it)
	{
		Widget* pChild = *it;
		switch (pChild->m_eDimState)
		{
			case WidgetDimState::Unknown:
				//DetermineDimension();
				break;

			case WidgetDimState::Valid:
				pChild->Draw();
				break;

			case WidgetDimState::Invalid:
				break;
		}
	}

	/*
	Print(GetOrigX() + 20, GetOrigY() + 8, GetPrintFont(), 12, LeftTop, 255, 255, 255,  "Pos        : %d - %d", GetPosX(), GetPosY());
	Print(GetOrigX() + 20, GetOrigY() + 20, GetPrintFont(), 12, LeftTop, 255, 255, 255, "Orig       : %d - %d", GetOrigX(), GetOrigY());
	Print(GetOrigX() + 20, GetOrigY() + 32, GetPrintFont(), 12, LeftTop, 255, 255, 255, "Screen Pos : %d - %d", GetScreenPosX(), GetScreenPosY());
	*/
	
	//Print(GetOrigX() + 200, GetOrigY() + 8, GetPrintFont(), 12, LeftTop, 255, 255, 255, "Mouse : %d - %d", GetMouseX(), GetMouseY());
}

