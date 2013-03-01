#include "IBVector2.h"


//IBVector2::IBVector2()
//{}

IBVector2::IBVector2(const string& name, bool bInstance)
	: IBObject(name, bInstance)
{}

//IBVector2::IBVector2(int _x, int _y, bool bInstance)
//	: Vector2(_x, _y)
//{}

IBVector2::IBVector2(const string& name, int _x, int _y, bool bInstance)
	: IBObject(name, bInstance)
	, Vector2(_x, _y)
{}

IBVector2::IBVector2(const string& name, const Vector2& v, bool bInstance)
	: IBObject(name, bInstance)
	, Vector2(v)
{}


IBVector2& IBVector2::operator=(const Vector2& v)
{
	x = v.x;
	y = v.y;

	return *this;
}

void IBVector2::FormatData() const
{
	m_sData = FormatString("(%d, %d)", x, y);
}


void IBVector2::Print() const
{
	if (m_sName.length() > 0)
		LOG("Vector2 : %s (%d %d)", m_sName.c_str(), x, y);
	else
		LOG("Vector2 (%d %d)", x, y);

	LOG("\n");
}
