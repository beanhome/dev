#ifndef __BLPROP_H__
#define __BLPROP_H__

#include "Utils.h"
#include "BLObject.h"

class BLWorld;
class Image;
class ImageResource;

class BLProp : public BLObject
{
	public:
		BLProp(BLWorld& oWorld, const string& name, const Vector2& pos = Vector2(0,0));
		virtual ~BLProp();

		void SetVisible(bool bVisible = true) { m_bVisible = bVisible; }

		const ImageResource* GetImageResource() const;

		void Draw();

	protected:
		BLWorld&		m_oWorld;
		Image*			m_pImage;
		bool			m_bVisible;
};

#endif
