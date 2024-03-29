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

Vector2::Vector2(const Vector2& v)
	: x(v.x)
	, y(v.y)
{
}

void Vector2::Set(int _x, int _y)
{
	x = _x;
	y = _y;
}

void Vector2::Set(const Vector2& pos)
{
	x = pos.x;
	y = pos.y;
}


Vector2& Vector2::operator=(const Vector2& v)
{
	x = v.x;
	y = v.y;

	return *this;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;

	return *this;
}


bool operator==(const Vector2& a, const Vector2& b)
{
	return (a.x == b.x && a.y == b.y);
}

bool operator!=(const Vector2& a, const Vector2& b)
{
	return !operator==(a, b);
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

Vector2 operator+(const Vector2& a, const Vector2& b)
{
	Vector2 res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;

	return res;
}

Vector2 operator-(const Vector2& a, const Vector2& b)
{
	Vector2 res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;

	return res;
}

Vector2 operator*(const Vector2& a, const float& t)
{
	Vector2 res;

	res.x = (int)((float)a.x * t);
	res.y = (int)((float)a.y * t);

	return a;
}

Vector2 operator/(const Vector2& a, const float& t)
{
	Vector2 res;

	res.x = (int)((float)a.x / t);
	res.y = (int)((float)a.y / t);

	return a;
}

