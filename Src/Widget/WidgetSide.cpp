// WidgetSide.cpp

#include "WidgetSide.h"
#include "Widget.h"

WidgetSide::WidgetSide()
	: m_eDesignation(SideEnum::Left)
	, m_eState(WidgetDimState::Unknown)
	, m_eReference(WidgetReference::Self)
{
}

WidgetSide::~WidgetSide()
{
}

void WidgetSide::DetermineDimension()
{
	switch (m_eState)
	{
		case WidgetDimState::Unknown:
		case WidgetDimState::Invalid:
			break;

		case WidgetDimState::Process:
		case WidgetDimState::Valid:
			return;
	}

	m_eState = WidgetDimState::Process;

	switch (m_eReference)
	{
		case WidgetReference::Parent:
			DetermineDimension_Parent();
			break;

		case WidgetReference::Self:
			DetermineDimension_Self();
			break;

		case WidgetReference::Brother:
			DetermineDimension_Brother();
			break;

		case WidgetReference::Child:
			DetermineDimension_Child();
			break;
	}

	if (m_eState == WidgetDimState::Valid)
	{
		switch (m_eDesignation)
		{
		case SideEnum::Left:
			if (m_pWidget->GetSide(SideEnum::Right).m_eState == WidgetDimState::Valid)
				m_iPixelPos = Clamp(m_iPixelPos, m_pWidget->GetSide(SideEnum::Right).m_iPixelPos - m_pWidget->GetMaxWidth(), m_pWidget->GetSide(SideEnum::Right).m_iPixelPos - m_pWidget->GetMinWidth());
			break;

		case SideEnum::Right:
			if (m_pWidget->GetSide(SideEnum::Left).m_eState == WidgetDimState::Valid)
				m_iPixelPos = Clamp(m_iPixelPos, m_pWidget->GetSide(SideEnum::Left).m_iPixelPos + m_pWidget->GetMinWidth(), m_pWidget->GetSide(SideEnum::Left).m_iPixelPos + m_pWidget->GetMaxWidth());
			break;

		case SideEnum::Top:
			if (m_pWidget->GetSide(SideEnum::Bottom).m_eState == WidgetDimState::Valid)
				m_iPixelPos = Clamp(m_iPixelPos, m_pWidget->GetSide(SideEnum::Bottom).m_iPixelPos - m_pWidget->GetMaxHeight(), m_pWidget->GetSide(SideEnum::Bottom).m_iPixelPos - m_pWidget->GetMinHeight());
			break;

		case SideEnum::Bottom:
			if (m_pWidget->GetSide(SideEnum::Top).m_eState == WidgetDimState::Valid)
				m_iPixelPos = Clamp(m_iPixelPos, m_pWidget->GetSide(SideEnum::Top).m_iPixelPos + m_pWidget->GetMinHeight(), m_pWidget->GetSide(SideEnum::Top).m_iPixelPos + m_pWidget->GetMaxHeight());
			break;
		}
	}
}


void WidgetSide::DetermineDimension_Parent()
{
	m_iPixelPos = 0;

	switch (m_eDesignation)
	{
		case SideEnum::Left:
		case SideEnum::Right:
		{
			m_eState = WidgetDimState::Valid;
			if (m_oParentRefProp.m_fRelativePos != 0.f)
			{
				uint16 iWidth = (m_pWidget->GetWidgetParent() == NULL ? m_pWidget->GetParent().GetWidth() : m_pWidget->GetWidgetParent()->GetWidgetWidth(m_eState));
				m_iPixelPos = (sint32)(iWidth * m_oParentRefProp.m_fRelativePos);
			}
			m_iPixelPos += m_oParentRefProp.m_iPixOffset;
			break;
		}

		case SideEnum::Top:
		case SideEnum::Bottom:
		{
			m_eState = WidgetDimState::Valid;
			if (m_oParentRefProp.m_fRelativePos != 0.f)
			{
				uint16 iHeight = (m_pWidget->GetWidgetParent() == NULL ? m_pWidget->GetParent().GetHeight() : m_pWidget->GetWidgetParent()->GetWidgetHeight(m_eState));
				m_iPixelPos = (sint32)(iHeight * m_oParentRefProp.m_fRelativePos);
			}
			m_iPixelPos += m_oParentRefProp.m_iPixOffset;
			break;
		}
	}
}

void WidgetSide::DetermineDimension_Self()
{
	switch (m_oSelfRefProp.m_eType)
	{
		case WidgetSelfReference::Auto:
			// selon le contenu
			m_iPixelPos = 0;
			m_eState = WidgetDimState::Valid;
			break;

		case WidgetSelfReference::Fix:
			switch (m_eDesignation)
			{
				case SideEnum::Left:	m_iPixelPos = m_pWidget->GetSideDimension(SideEnum::Right, m_eState) - m_oSelfRefProp.m_iFixSize;	break;
				case SideEnum::Right:	m_iPixelPos = m_pWidget->GetSideDimension(SideEnum::Left, m_eState) + m_oSelfRefProp.m_iFixSize;	break;
				case SideEnum::Top:		m_iPixelPos = m_pWidget->GetSideDimension(SideEnum::Bottom, m_eState) - m_oSelfRefProp.m_iFixSize;	break;
				case SideEnum::Bottom:	m_iPixelPos = m_pWidget->GetSideDimension(SideEnum::Top, m_eState) + m_oSelfRefProp.m_iFixSize;	break;
			}
			break;
	}
}

void WidgetSide::DetermineDimension_Brother()
{
	Widget* pRefWin = m_pWidget->GetWidgetParent()->GetChild(m_oBrotherRefProp.m_id);
	sint32 iMin = 0;
	sint32 iMax = 0;

	switch (m_eDesignation)
	{
		case SideEnum::Left:
		case SideEnum::Right:
			iMin = pRefWin->GetSidePosition(SideEnum::Left, m_eState);
			if (m_eState != WidgetDimState::Valid)
				break;
			iMax = pRefWin->GetSidePosition(SideEnum::Right, m_eState);
			break;

		case SideEnum::Top:
		case SideEnum::Bottom:
			iMin = pRefWin->GetSidePosition(SideEnum::Top, m_eState);
			if (m_eState != WidgetDimState::Valid)
				break;
			iMax = pRefWin->GetSidePosition(SideEnum::Bottom, m_eState);
			break;
	}

	m_iPixelPos = (sint32)(iMin + (iMax - iMin) * m_oBrotherRefProp.m_fRelativePos) + m_oBrotherRefProp.m_iPixOffset;
}

void WidgetSide::DetermineDimension_Child()
{
	Widget* pChild = m_pWidget->GetChild(m_oChildRefProp.m_id);

	if (pChild == NULL)
	{
		m_eState = WidgetDimState::Invalid;
		return;
	}

	switch (m_eDesignation)
	{
		case SideEnum::Left:	m_oChildRefProp.m_fRelativePos = 0.f;	break;
		case SideEnum::Right:	m_oChildRefProp.m_fRelativePos = 1.f;	break;
		case SideEnum::Top:		m_oChildRefProp.m_fRelativePos = 0.f;	break;
		case SideEnum::Bottom:	m_oChildRefProp.m_fRelativePos = 1.f;	break;
	}

	sint32 iOpposite;
	switch (m_eDesignation)
	{
		case SideEnum::Left:	iOpposite = m_pWidget->GetSideDimension(SideEnum::Right, m_eState);		break;
		case SideEnum::Right:	iOpposite = m_pWidget->GetSideDimension(SideEnum::Left, m_eState);		break;
		case SideEnum::Top:		iOpposite = m_pWidget->GetSideDimension(SideEnum::Bottom, m_eState);	break;
		case SideEnum::Bottom:	iOpposite = m_pWidget->GetSideDimension(SideEnum::Top, m_eState);		break;
	}

	if (m_eState != WidgetDimState::Valid)
		return;

	switch (m_eDesignation)
	{
		case SideEnum::Left:	m_iPixelPos = iOpposite - pChild->GetSidePosition(SideEnum::Left, m_eState) + m_oChildRefProp.m_iPixOffset;		break;
		case SideEnum::Right:	m_iPixelPos = iOpposite + pChild->GetSidePosition(SideEnum::Right, m_eState) + m_oChildRefProp.m_iPixOffset;	break;
		case SideEnum::Top:		m_iPixelPos = iOpposite - pChild->GetSidePosition(SideEnum::Top, m_eState) + m_oChildRefProp.m_iPixOffset;		break;
		case SideEnum::Bottom:	m_iPixelPos = iOpposite + pChild->GetSidePosition(SideEnum::Bottom, m_eState) + m_oChildRefProp.m_iPixOffset;	break;
	}
}

sint32 WidgetSide::GetMouseDist()
{
	sint32 iDist = 0;

	switch (m_eDesignation)
	{
		case SideEnum::Left:	iDist = abs(m_pWidget->GetMouseX());							break;
		case SideEnum::Right:	iDist = abs(m_pWidget->GetWidth() - m_pWidget->GetMouseX());	break;
		case SideEnum::Top:		iDist = abs(m_pWidget->GetMouseY());							break;
		case SideEnum::Bottom:	iDist = abs(m_pWidget->GetHeight() - m_pWidget->GetMouseY());	break;
	}

	return iDist;
}

void WidgetSide::GetLineCoord(sint32& x1, sint32& y1, sint32& x2, sint32& y2) const
{
	uint16 w = m_pWidget->GetWidth()-1;
	uint16 h = m_pWidget->GetHeight()-1;

	x1 = y1 = x2 = y2 = 0;

	switch (m_eDesignation)
	{
		case SideEnum::Left:	x1=0; y1=0; x2=0; y2=h;	break;
		case SideEnum::Right:	x1=w; y1=0; x2=w; y2=h;	break;
		case SideEnum::Top:		x1=0; y1=0; x2=w; y2=0;	break;
		case SideEnum::Bottom:	x1=0; y1=h; x2=w; y2=h;	break;
	}
}

void WidgetSide::GetLineCoord(sint32& x1, sint32& y1, sint32& x2, sint32& y2, sint32 ox, sint32 oy) const
{
	GetLineCoord(x1, y1, x2, y2);
	x1 += ox;
	x2 += ox;
	y1 += oy;
	y2 += oy;
}









