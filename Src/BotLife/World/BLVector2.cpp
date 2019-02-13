#include "BLVector2.h"

BLVector2::BLVector2(const string& name)
	: BLObject(name)
{}

BLVector2::BLVector2(const string& name, int _x, int _y)
	: BLObject(name)
	, Vector2(_x, _y)
{}

BLVector2::BLVector2(const string& name, const Vector2& v)
	: BLObject(name)
	, Vector2(v)
{}

BLVector2::BLVector2(int _x, int _y)
	: BLObject("xy")
	, Vector2(_x, _y)
{
	m_sName = FormatString("%d,%d", x, y);
}

BLVector2::BLVector2(const Vector2& v)
	: BLObject("xy")
	, Vector2(v)
{
	m_sName = FormatString("%d,%d", v.x, v.y);
}


BLVector2& BLVector2::operator=(const Vector2& v)
{
	x = v.x;
	y = v.y;

	return *this;
}

void BLVector2::Print() const
{
	if (m_sName.length() > 0)
		LOG("Vector2 : %s (%d %d)", m_sName.c_str(), x, y);
	else
		LOG("Vector2 (%d %d)", x, y);

	LOG("\n");
}
