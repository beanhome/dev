#include "IBTreeBox_Horiz.h"

#include "GEngine.h"
#include "Canvas.h"
#include "Color.h"
#include "Utils.h"

IBTreeBox_Horiz::IBTreeBox_Horiz(Canvas& oCanvas, IBTreeBox* pParent)
	: IBTreeBox_Container(oCanvas, pParent)
{
}

IBTreeBox_Horiz::~IBTreeBox_Horiz()
{
}

void IBTreeBox_Horiz::ComputeSize()
{
	m_iWidth = 0;
	m_iHeight = 0;

	for (IBTreeBox* pTreeBox : m_aChildren)
	{
		sint32 iBoxWidth, iBoxHeight;
		pTreeBox->GetSize(iBoxWidth, iBoxHeight);

		m_iWidth += iBoxWidth;
		m_iHeight = std::max(m_iHeight, iBoxHeight);
	}
}

void IBTreeBox_Horiz::UpdatePos()
{
	sint32 x = m_iPosX;

	for (IBTreeBox* pTreeBox : m_aChildren)
	{
		pTreeBox->SetPos(x, m_iPosY);
		x += pTreeBox->GetWidth();
	}
}

