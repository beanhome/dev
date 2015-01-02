#include "ImageFlipBook.h"
#include "GEngine.h"
#include "ImageResource.h"

ImageFlipBook::ImageFlipBook(const CanvasBase& oCanvas, ImageResource* pImageResource, uint16 row, uint16 col)
	: Image(oCanvas, pImageResource)
	, m_iRowCount(row)
	, m_iColCount(col)
	, m_iCurrent(-1)
{
	assert(row > 0);
	assert(col > 0);
}

//ImageFlipBook::ImageFlipBook(CanvasBase& oCanvas, const char* path, uint16 row, uint16 col)
//	: Image(oCanvas, path)
//	, m_iRowCount(row)
//	, m_iColCount(col)
//	, m_iCurrent(-1)
//{
//	assert(row > 0);
//	assert(col > 0);
//}

ImageFlipBook::~ImageFlipBook()
{
}


void ImageFlipBook::SetCurrent(int cur)
{
	m_iCurrent = cur % (m_iRowCount * m_iColCount);
}


void ImageFlipBook::Draw() const
{
	if (m_iCurrent != -1)
	{
		uint16 w = m_pImageResource->GetWidth() / m_iColCount;
		uint16 h = m_pImageResource->GetHeight() / m_iRowCount;
		sint32 x = w * (m_iCurrent % m_iColCount);
		sint32 y = h * (m_iCurrent / m_iColCount);

		m_oCanvas.DrawImage(*m_pImageResource, m_iPosX, m_iPosY, x, y, w, h);
	}
}

void ImageFlipBook::Draw(float fZoom) const
{
	if (m_iCurrent != -1)
	{
		uint16 sw = m_pImageResource->GetWidth() / m_iColCount;
		uint16 sh = m_pImageResource->GetHeight() / m_iRowCount;
		uint16 dw = (uint16)(sw * fZoom);
		uint16 dh = (uint16)(sh * fZoom);
		sint32 sx = sw * (m_iCurrent % m_iColCount);
		sint32 sy = sh * (m_iCurrent / m_iColCount);

		m_oCanvas.DrawImage(*m_pImageResource, m_iPosX, m_iPosY, dw, dh, sx, sy, sw, sh);
	}
}
