#include "ImageRotoZoom.h"
#include "GEngine.h"

ImageRotoZoom::ImageRotoZoom(CanvasBase* pCanvas, ImageResource* pImageResource)
	: Image(pCanvas, pImageResource)
	, m_fZoom(1.f)
	, m_fAngle(0.f)
{

}

ImageRotoZoom::ImageRotoZoom(CanvasBase* pCanvas, const char* path)
	: Image(pCanvas, path)
	, m_fZoom(1.f)
	, m_fAngle(0.f)
{
}

ImageRotoZoom::~ImageRotoZoom()
{
}


void ImageRotoZoom::SetZoom(float zoom)
{
	m_fZoom = zoom;
}

void ImageRotoZoom::SetRotation(float angle)
{
	m_fAngle = angle;
}


void ImageRotoZoom::Draw() const
{
	m_pCanvas->DrawImage(*m_pImageResource, m_iPosX, m_iPosY, m_fAngle, m_fZoom);
}
