#ifndef __BLVector2_H__
#define __BLVector2_H__

#include "Utils.h"
#include "BLObject.h"
#include "Vector2.h"

class BLVector2 : public BLObject, public Vector2
{
	public:
		BLVector2(const string& name);
		BLVector2(const string& name, int _x, int _y);
		BLVector2(const string& name, const Vector2& v);
		BLVector2(int _x, int _y);
		BLVector2(const Vector2& v);

		virtual BLObject* Clone() const { return new BLVector2(*this); }

		BLVector2& operator=(const Vector2& v);

		virtual void Print() const;
};

#endif
