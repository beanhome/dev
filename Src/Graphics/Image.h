#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Utils.h"

class CanvasBase;
class ImageResource;

class Image
{
	public:
		Image(CanvasBase* pCanvas, ImageResource* pImageResource);
		Image(CanvasBase* pCanvas, const char* path);
		virtual ~Image();

		void						SetPos(sint16 x, sint16 y);

		uint16						GetWidth() const;
		uint16						GetHeight() const;

		void						Draw() const;

	protected:
		CanvasBase*					m_pCanvas;
		sint16						m_iPosX;
		sint16						m_iPosY;

		ImageResource*				m_pImageResource;
};


#endif // __IMAGE_H__
