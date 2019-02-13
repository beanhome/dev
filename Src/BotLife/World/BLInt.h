#ifndef __BLINT_H__
#define __BLINT_H__

#include "Utils.h"
#include "BLObject.h"
#include "Vector2.h"

class BLInt : public BLObject
{
	public:
		BLInt(const string& name, int i = 0);
		BLInt(int i = 0);

		virtual BLObject* Clone() const { return new BLInt(*this); }

		BLInt& operator=(int v);

		int GetValue() const { return m_iValue; }

		void  Print() const;

	protected:
		int m_iValue;
};

#endif
