#include "ImageRotoZoom.h"
#include "GEngine.h"

ImageRotoZoom::ImageRotoZoom(CanvasBase& oCanvas, ImageResource* pImageResource)
	: Image(oCanvas, pImageResource)
	, m_fZoom(1.f)
	, m_fAngle(0.f)
{

}

ImageRotoZoom::ImageRotoZoom(CanvasBase& oCanvas, const char* path)
	: Image(oCanvas, path)
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
	m_oCanvas.DrawImage(*m_pImageResource, m_iPosX, m_iPosY, m_fAngle, m_fZoom);
}
