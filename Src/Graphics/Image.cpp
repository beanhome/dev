#include "Image.h"
#include "CanvasBase.h"
#include "GEngine.h"
#include "ImageResource.h"

Image::Image(const CanvasBase& oCanvas, ImageResource* pImageResource)
	: m_oCanvas(oCanvas)
	, m_iPosX(0)
	, m_iPosY(0)
	, m_iCenterX(0)
	, m_iCenterY(0)
	, m_pImageResource(pImageResource)
{
	m_iCenterX = m_pImageResource->GetWidth() / 2;
	m_iCenterY = m_pImageResource->GetHeight() / 2;
}

//Image::Image(CanvasBase& oCanvas, const char* path)
//	: m_oCanvas(oCanvas)
//	, m_iPosX(0)
//	, m_iPosY(0)
//	, m_pImageResource(NULL)
//{
//	m_pImageResource = m_oCanvas.GetGEngine()->GetImageResource(path);
//}

Image::~Image()
{
}


void Image::SetPos(sint16 x, sint16 y)
{
	m_iPosX = x;
	m_iPosY = y;
}


void Image::SetCenter(sint16 x, sint16 y)
{
	m_iCenterX = x;
	m_iCenterY = y;
}


uint16 Image::GetWidth() const
{
	return m_pImageResource->GetWidth();
}

uint16 Image::GetHeight() const
{
	return m_pImageResource->GetHeight();
}

void Image::Draw() const
{
	m_oCanvas.DrawImage(*m_pImageResource, m_iPosX - (m_iCenterX - m_pImageResource->GetWidth()/2), m_iPosY - m_pImageResource->GetHeight()/2 + (m_pImageResource->GetHeight() - m_iCenterY));
}
