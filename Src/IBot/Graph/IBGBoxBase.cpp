#include "IBGBoxBase.h"
#include "CanvasBase.h"

IBGBoxBase::IBGBoxBase(CanvasBase& parent)
	: m_oCanvas(parent)
{
}

void IBGBoxBase::DrawFrame(const Color& color) const
{
	m_oCanvas.CanvasBase::DrawRect(0, 0, m_oCanvas.GetWidth()-1, m_oCanvas.GetHeight()-1, color);
}

