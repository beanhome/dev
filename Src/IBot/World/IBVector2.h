#ifndef __IBVECTOR2_H__
#define __IBVECTOR2_H__

#include "Utils.h"
#include "IBObject.h"
#include "Vector2.h"

class IBVector2 : public IBObject, public Vector2
{
	public:
		//IBVector2();
		IBVector2(const string& name, bool bInstance = false);
		//IBVector2(int _x, int _y, bool bInstance = false);
		IBVector2(const string& name, int _x, int _y, bool bInstance = false);
		IBVector2(const string& name, const Vector2& v, bool bInstance = false);

		IBVector2& operator=(const Vector2& v);

		IBObject* Clone() const { return new IBVector2(*this); }

		virtual void FormatData() const;
		virtual void Print() const;
};

#endif
