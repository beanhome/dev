#include "Image.h"
#include "CanvasBase.h"
#include "GEngine.h"
#include "ImageResource.h"

Image::Image(CanvasBase* pCanvas, ImageResource* pImageResource)
	: m_pCanvas(pCanvas)
	, m_iPosX(0)
	, m_iPosY(0)
	, m_pImageResource(pImageResource)
{

}

Image::Image(CanvasBase* pCanvas, const char* path)
	: m_pCanvas(pCanvas)
	, m_iPosX(0)
	, m_iPosY(0)
	, m_pImageResource(NULL)
{
	m_pImageResource = pCanvas->GetGEngine()->CreateImageResource(path);
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
	m_pCanvas->DrawImage(*m_pImageResource, m_iPosX, m_iPosY);
}
