#include "IBInt.h"

IBInt::IBInt(const string& name, int i)
	: IBObject(name)
	, m_iValue(i)
{}

IBInt& IBInt::operator=(int v)
{
	m_iValue = v;

	return *this;
}

void IBInt::FormatData() const
{
	m_sData = FormatString("%d", m_iValue);
}

void IBInt::Print() const
{
	if (m_sName.length() > 0)
		LOG("Int : %s (%d)", m_sName.c_str(), m_iValue);
	else
		LOG("Int (%d)", m_iValue);

	LOG("\n");
}
