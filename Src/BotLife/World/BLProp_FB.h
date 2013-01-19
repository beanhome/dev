#ifndef __BLPROP_FB_H__
#define __BLPROP_FB_H__

#include "Utils.h"
#include "BLProp.h"

class BLWorld;
class Image;
class ImageResource;

class BLProp_FB : public BLProp
{
	public:
		BLProp_FB(BLWorld& oWorld, const string& name, const char* img, uint16 row, uint16 col, const Vector2& pos = Vector2(0,0));
		virtual ~BLProp_FB();

		void SetCurrent(sint16 i);

	protected:
};

#endif
