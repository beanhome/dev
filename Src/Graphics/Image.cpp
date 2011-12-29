#include "Image.h"
#include "CanvasBase.h"
#include "GEngine.h"
#include "ImageResource.h"

Image::Image(CanvasBase& oCanvas, ImageResource* pImageResource)
	: m_oCanvas(oCanvas)
	, m_iPosX(0)
	, m_iPosY(0)
	, m_pImageResource(pImageResource)
{

}

Image::Image(CanvasBase& oCanvas, const char* path)
	: m_oCanvas(oCanvas)
	, m_iPosX(0)
	, m_iPosY(0)
	, m_pImageResource(NULL)
{
	m_pImageResource = m_oCanvas.GetGEngine()->GetImageResource(path);
}

Image::~Image()
{
}


void Image::SetPos(sint16 x, sint16 y)
{
	m_iPosX = x;
	m_iPosY = y;
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
	m_oCanvas.DrawImage(*m_pImageResource, m_iPosX, m_iPosY);
}
