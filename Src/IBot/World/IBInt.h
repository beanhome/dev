#ifndef __IBINT_H__
#define __IBINT_H__

#include "Utils.h"
#include "IBObject.h"

class IBInt : public IBObject
{
	public:
		IBInt(const string& name, int i=0);

		IBInt& operator=(int v);

		int GetValue() const { return m_iValue; }

		virtual void FormatData() const;
		virtual void Print() const;

	private:
		int m_iValue;
};

#endif
