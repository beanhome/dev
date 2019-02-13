#ifndef __IBINT_H__
#define __IBINT_H__

#include "Utils.h"

class IBInt
{
	public:
		IBInt(const string& name, int i=0);

		IBInt& operator=(int v);

		const string& GetName() const { return m_sName; }
		int GetValue() const { return m_iValue; }

	private:
		string m_sName;
		int m_iValue;
};

#endif
