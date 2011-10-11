#include "Vector2.h"

Vector2::Vector2()
	: x(0)
	, y(0)
{
}

Vector2::Vector2(int _x, int _y)
	: x(_x)
	, y(_y)
{
}

bool operator==(const Vector2& a, const Vector2& b)
{
	return (a.x == b.x && a.y == b.y);
}

bool operator<(const Vector2& a, const Vector2& b)
{
	return (a.x < b.x || (a.x == b.x && a.y < b.y));
}

bool operator<=(const Vector2& a, const Vector2& b)
{
	return (operator==(a, b) || operator<(a, b));
}

bool operator>(const Vector2& a, const Vector2& b)
{
	return !operator<=(a, b);
}

bool operator>=(const Vector2& a, const Vector2& b)
{
	return !operator<(a, b);
}

