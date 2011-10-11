#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2
{
	int x, y;

	Vector2();
	Vector2(int _x, int _y);
};

bool operator==(const Vector2& a, const Vector2& b);
bool operator<(const Vector2& a, const Vector2& b);
bool operator<=(const Vector2& a, const Vector2& b);
bool operator>(const Vector2& a, const Vector2& b);
bool operator>=(const Vector2& a, const Vector2& b);

#endif //VECTOR2_H
