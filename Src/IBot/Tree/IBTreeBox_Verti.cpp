#include "IBTreeBox_Verti.h"

#include "GEngine.h"
#include "Canvas.h"
#include "Color.h"
#include "Utils.h"

IBTreeBox_Verti::IBTreeBox_Verti(Canvas& oCanvas, IBTreeBox* pParent)
	: IBTreeBox_Container(oCanvas, pParent)
{
}

IBTreeBox_Verti::~IBTreeBox_Verti()
{
}

void IBTreeBox_Verti::ComputeSize()
{
	m_iWidth = 0;
	m_iHeight = 0;

	for (IBTreeBox* pTreeBox : m_aChildren)
	{
		sint32 iBoxWidth, iBoxHeight;
		pTreeBox->GetSize(iBoxWidth, iBoxHeight);

		m_iWidth = std::max(m_iWidth, iBoxWidth);
		m_iHeight += iBoxHeight;
	}
}

void IBTreeBox_Verti::UpdatePos()
{
	sint32 y = m_iPosY;

	for (IBTreeBox* pTreeBox : m_aChildren)
	{
		pTreeBox->SetPos(m_iPosX, y);
		y += pTreeBox->GetHeight();
	}
}

