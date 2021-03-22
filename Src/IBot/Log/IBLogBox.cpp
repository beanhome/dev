#include "IBLogBox.h"

#include "Canvas.h"
#include "Color.h"
#include "Utils.h"


IBLogBox::IBLogBox()
	: m_bExtended(false)
	, m_bFolded(false)
	, m_iWidth(0)
	, m_iHeight(0)
{

}

IBLogBox::~IBLogBox()
{

}

void IBLogBox::Refresh(Canvas& oCanvas)
{
	Size(oCanvas, m_iWidth, m_iHeight);
}

