#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2
{
	int x, y;

	Vector2();
	Vector2(int _x, int _y);
	Vector2(const Vector2& v);
	
	Vector2& operator=(const Vector2& v);
	Vector2& operator+=(const Vector2& v);

	void Set(int _x, int _y);
	void Set(const Vector2& pos);
};

bool operator==(const Vector2& a, const Vector2& b);
bool operator!=(const Vector2& a, const Vector2& b);
bool operator<(const Vector2& a, const Vector2& b);
bool operator<=(const Vector2& a, const Vector2& b);
bool operator>(const Vector2& a, const Vector2& b);
bool operator>=(const Vector2& a, const Vector2& b);
Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& a, const float& t);
Vector2 operator/(const Vector2& a, const float& t);

#endif //VECTOR2_H
