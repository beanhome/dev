#include "ImageFlipBook.h"
#include "GEngine.h"
#include "ImageResource.h"

ImageFlipBook::ImageFlipBook(CanvasBase& oCanvas, ImageResource* pImageResource, uint16 row, uint16 col)
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
	sint16 w = m_pImageResource->GetWidth() / m_iColCount;
	sint16 h = m_pImageResource->GetHeight() / m_iRowCount;
	sint16 x = w * (m_iCurrent % m_iColCount);
	sint16 y = h * (m_iCurrent / m_iColCount);

	m_oCanvas.DrawImage(*m_pImageResource, m_iPosX, m_iPosY, x, y, w, h);
}
