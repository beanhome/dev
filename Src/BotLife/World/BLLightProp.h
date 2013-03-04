#ifndef __BLLIGHTPROP_H__
#define __BLLIGHTPROP_H__

#include "Utils.h"
#include "BLProp_SI.h"

class BLLightProp : public BLProp_SI
{
	public:
		BLLightProp(BLWorld& oWorld, const string& name, const char* img, const Vector2& pos = Vector2(0,0));
		virtual ~BLLightProp();

		virtual bool			IsTempBlock() const { return false; }

	protected:
};

#endif
