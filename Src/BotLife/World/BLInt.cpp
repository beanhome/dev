#include "BLInt.h"
#include "Vector2.h"

BLInt::BLInt(const string& name, int i)
	: BLObject(name)
	, m_iValue(i)
{
}

BLInt::BLInt(int i)
	: BLObject("")
	, m_iValue(i)
{
	m_sName = FormatString("%d", m_iValue);
}

BLInt& BLInt::operator=(int v)
{
	m_iValue = v;

	return *this;
}

void BLInt::Print() const
{
	LOG("Object : %s (%d)", GetName().c_str(), m_iValue);
	LOG("\n");
}
