#include "IBTreeBox.h"

#include "Canvas.h"
#include "Color.h"
#include "Utils.h"


IBTreeBox::IBTreeBox(Canvas& oCanvas, IBTreeBox* pParent)
	: m_oCanvas(oCanvas)
	, m_pParent(pParent)
	, m_bMouseIsOver(false)
	, m_iPosX(0)
	, m_iPosY(0)
	, m_iWidth(0)
	, m_iHeight(0)
{

}

IBTreeBox::~IBTreeBox()
{

}

void IBTreeBox::UpdateSize()
{
	sint32 Width = m_iWidth;
	sint32 Height = m_iHeight;

	ComputeSize();

	if (m_pParent != nullptr && (Width != m_iWidth || Height != m_iHeight))
		m_pParent->UpdateSize();
}

void IBTreeBox::Update(float dt, sint32 iMouseX, sint32 iMouseY)
{
	bool bMouseIsOver = iMouseX > m_iPosX && iMouseX < m_iPosX+m_iWidth && iMouseY > m_iPosY && iMouseY < m_iPosY+m_iHeight;

	if (!m_bMouseIsOver && bMouseIsOver)
	{
		m_bMouseIsOver = true;
		OnMouseIn();
	}

	if (m_bMouseIsOver && !bMouseIsOver)
	{
		m_bMouseIsOver = false;
		OnMouseOut();
	}
}

void IBTreeBox::MouseClick(sint32 iMouseX, sint32 iMouseY)
{
	if (m_bMouseIsOver)
	{
		OnMouseClick(iMouseX, iMouseY);
		OnMouseClickDelegate.Broadcast(iMouseX, iMouseY);
	}
}

