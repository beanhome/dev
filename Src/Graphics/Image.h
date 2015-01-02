#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Utils.h"

class CanvasBase;
class ImageResource;

class Image
{
	public:
		Image(const CanvasBase& oCanvas, ImageResource* pImageResource);
		//Image(CanvasBase& oCanvas, const char* path);
		virtual ~Image();

		void						SetPos(sint32 x, sint32 y);
		void						SetCenter(sint32 x, sint32 y);

		uint16						GetWidth() const;
		uint16						GetHeight() const;

		virtual void				Draw() const;

		const ImageResource*		GetResource() const { return m_pImageResource; }

	protected:
		const CanvasBase&			m_oCanvas;
		sint32						m_iPosX;
		sint32						m_iPosY;
		sint32						m_iCenterX;
		sint32						m_iCenterY;

		ImageResource*				m_pImageResource;
};


#endif // __IMAGE_H__

