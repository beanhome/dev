#include "IBTreeBox_Image.h"

#include "Canvas.h"
#include "Color.h"
#include "Utils.h"
#include "ImageResource.h"


IBTreeBox_Image::IBTreeBox_Image(Canvas& oCanvas, IBTreeBox* pParent)
	: IBTreeBox(oCanvas, pParent)
	, m_pImage(nullptr)
{
}

IBTreeBox_Image::~IBTreeBox_Image()
{
}

void IBTreeBox_Image::Draw() const
{
	if (m_pImage)
		m_oCanvas.DrawImage(*m_pImage, m_iPosX, m_iPosY);
}

void IBTreeBox_Image::ComputeSize()
{
	m_iWidth = (m_pImage != nullptr ? m_pImage->GetWidth() : 0);
	m_iHeight = (m_pImage != nullptr ? m_pImage->GetHeight() : 0);
}
