#ifndef __IMAGEROTOZOOM_H__
#define __IMAGEROTOZOOM_H__

#include "Utils.h"
#include "Image.h"

class ImageRotoZoom : public Image
{
	public:
		ImageRotoZoom(CanvasBase& oCanvas, ImageResource* pImageResource);
		ImageRotoZoom(CanvasBase& oCanvas, const char* path);
		virtual ~ImageRotoZoom();

		void						SetZoom(float zoom);
		void						SetRotation(float angle);

		void						Draw() const;

	protected:
		float						m_fZoom;
		float						m_fAngle;
};


#endif // __IMAGEROTOZOOM_H__

