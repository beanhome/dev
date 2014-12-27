// Widget.cpp


#include "Widget.h"
#include "Utils.h"
#include "Color.h"

Color Widget::s_oStateColor[] =
{
	Color(128, 128, 128), // Unknown
	Color(0,   0,   255), // Process
	Color(255, 255, 255), // Valid
	Color(255, 0,   0)    // Invalid
};

Widget::Widget(CanvasBase& oParent)
	: Canvas(oParent)
	, m_pWidgetParent(NULL)
	, m_id(-1)
	, m_sName("unknown")
	, m_eDimState(WidgetDimState::Unknown)
{
	Init();
}

Widget::Widget(CanvasBase& oParent, sint32 id, const string& sName)
	: Canvas(oParent)
	, m_pWidgetParent(NULL)
	, m_id(id)
	, m_sName(sName)
	, m_eDimState(WidgetDimState::Unknown)
{
	Init();
}

Widget::Widget(CanvasBase& oParent, const string& sName)
	: Canvas(oParent)
	, m_pWidgetParent(NULL)
	, m_id(-1)
	, m_sName(sName)
	, m_eDimState(WidgetDimState::Unknown)
{
	Init();
}

Widget::Widget(CanvasBase& oParent, sint32 id)
	: Canvas(oParent)
	, m_pWidgetParent(NULL)
	, m_id(-id)
	, m_sName("unknown")
	, m_eDimState(WidgetDimState::Unknown)
{
	Init();
}

Widget::Widget(Widget& oParent)
	: Canvas((CanvasBase&)oParent)
	, m_pWidgetParent(&oParent)
	, m_id(-1)
	, m_sName("unknown")
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

Widget::Widget(Widget& oParent, const string& sName)
	: Canvas((CanvasBase&)oParent)
	, m_pWidgetParent(&oParent)
	, m_id(-1)
	, m_sName(sName)
	, m_eDimState(WidgetDimState::Unknown)
{
	Init();
}

Widget::Widget(Widget& oParent, sint32 id)
	: Canvas((CanvasBase&)oParent)
	, m_pWidgetParent(&oParent)
	, m_id(-id)
	, m_sName("unknown")
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
				pos += (sint32)(GetWidth(eState) * m_oHorizOffset.m_fSizeCoeff);
			pos += m_oHorizOffset.m_iFixPixel;
			break;

		case SideEnum::Top:
		case SideEnum::Bottom:
			if (m_oVertiOffset.m_fSizeCoeff != 0.f)
				pos += (sint32)(GetHeight(eState) * m_oVertiOffset.m_fSizeCoeff);
			pos += m_oVertiOffset.m_iFixPixel;
			break;
	}

	return pos;
}


uint16 Widget::GetWidth(WidgetDimState::Type& eState)
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

uint16 Widget::GetHeight(WidgetDimState::Type& eState)
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


/*
uint16 Widget::GetSize(SideEnum::Type eSide)
{
	switch (eSide)
	{
		case SideEnum::Left:
		case SideEnum::Right:
			return GetWidth();

		case SideEnum::Top:
		case SideEnum::Bottom:
			return GetHeight();
	}

	return 0;
}
*/


Widget* Widget::AddNewChild(sint32 id, const string& sName)
{
	Widget* pWidget = new Widget(*this, id, sName);
	m_vChildren.push_back(pWidget);
	return pWidget;
}

Widget* Widget::AddNewChild(const string& sName)
{
	Widget* pWidget = new Widget(*this, sName);
	m_vChildren.push_back(pWidget);
	return pWidget;
}

Widget* Widget::AddNewChild(sint32 id)
{
	Widget* pWidget = new Widget(*this, id);
	m_vChildren.push_back(pWidget);
	return pWidget;
}

Widget* Widget::AddNewChild()
{
	Widget* pWidget = new Widget(*this);
	m_vChildren.push_back(pWidget);
	return pWidget;
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

				SetPosX((sint16)(iLeft + iHorizOffset));
				SetPosY((sint16)(iTop + iVertiOffset));
				ASSERT(iRight - iLeft > 0);
				SetWidth((uint16)(iRight - iLeft));
				ASSERT(iBottom - iTop > 0);
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


void Widget::Draw() const
{
	DrawRect(0, 0, m_iWidth-1, m_iHeight-1, s_oStateColor[m_eDimState].r, s_oStateColor[m_eDimState].g, s_oStateColor[m_eDimState].b);
	Print(2, 2, GetPrintFont(), 15, LeftTop, 255, 255, 255, m_sName.c_str());

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
}
