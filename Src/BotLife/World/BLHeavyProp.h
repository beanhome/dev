#ifndef __BLHEAVYPROP_H__
#define __BLHEAVYPROP_H__

#include "Utils.h"
#include "BLProp_SI.h"

class BLHeavyProp : public BLProp_SI
{
	public:
		BLHeavyProp(BLWorld& oWorld, const string& name, const char* img, const Vector2& pos = Vector2(0,0));
		virtual ~BLHeavyProp();

		virtual bool			IsBlock() const { return true; }
		virtual bool			IsMovable() const { return true; }

	protected:
};

#endif
