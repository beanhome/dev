#include "IBInt.h"

IBInt::IBInt(const string& name, int i)
	: m_sName(name)
	, m_iValue(i)
{}

IBInt& IBInt::operator=(int v)
{
	m_iValue = v;

	return *this;
}
