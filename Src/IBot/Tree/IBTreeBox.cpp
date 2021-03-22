#include "IBTreeBox.h"

#include "Canvas.h"
#include "Color.h"
#include "Utils.h"


IBTreeBox::IBTreeBox()
	: m_bExtended(false)
	, m_bFolded(false)
	, m_iWidth(0)
	, m_iHeight(0)
{

}

IBTreeBox::~IBTreeBox()
{

}

void IBTreeBox::Refresh(Canvas& oCanvas)
{
	Size(oCanvas, m_iWidth, m_iHeight);
}

