#ifndef __IMAGEFLIPBOOK_H__
#define __IMAGEFLIPBOOK_H__

#include "Utils.h"
#include "Image.h"

class ImageFlipBook : public Image
{
	public:
		ImageFlipBook(const CanvasBase& oCanvas, ImageResource* pImageResource, uint16 row, uint16 col);
		//ImageFlipBook(CanvasBase& oCanvas, const char* path, uint16 row, uint16 col);
		virtual ~ImageFlipBook();

		int							GetCurrent() const { return m_iCurrent; }
		void						SetCurrent(int cur);

		uint16						GetRowCount() const { return m_iRowCount; }
		uint16						GetColCount() const { return m_iColCount; }

		virtual void				Draw() const;
		void						Draw(float fZoom) const;

	protected:
		uint16						m_iRowCount;
		uint16						m_iColCount;
		int							m_iCurrent;
};


#endif // __IMAGEFLIPBOOK_H__

