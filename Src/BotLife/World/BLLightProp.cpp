#include "BLLightProp.h"


BLLightProp::BLLightProp(BLWorld& oWorld, const string& name, const char* img, const Vector2& pos)
	: BLProp_SI(oWorld, name, img, pos)
{
}

BLLightProp::~BLLightProp()
{
}

