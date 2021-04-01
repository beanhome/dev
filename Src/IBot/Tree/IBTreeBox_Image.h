#ifndef __IBTREEBOX_IMAGE_H__
#define __IBTREEBOX_IMAGE_H__

#include "IBTreeBox.h"
#include "Utils.h"
#include "Color.h"
#include "Canvas.h"

class IBTreeBox_Image : public IBTreeBox
{
	public:
		IBTreeBox_Image(Canvas& oCanvas, IBTreeBox* pParent);
		virtual ~IBTreeBox_Image();

	public:
		void				SetImage(ImageResource* pImage) { m_pImage = pImage; UpdateSize(); }
		ImageResource*		GetImage() const { return m_pImage; }

		virtual void		Draw() const override;

	protected:
		virtual void		ComputeSize() override;

	protected:
		class ImageResource* m_pImage;
};

#endif
