#ifndef __BLPROP_SI_H__
#define __BLPROP_SI_H__

#include "Utils.h"
#include "BLProp.h"

class BLWorld;
class Image;
class ImageResource;

class BLProp_SI : public BLProp
{
	public:
		BLProp_SI(BLWorld& oWorld, const string& name, const char* img, const Vector2& pos = Vector2(0,0));
		virtual ~BLProp_SI();

	protected:
};

#endif
