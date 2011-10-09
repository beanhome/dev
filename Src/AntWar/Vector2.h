#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2
{
    int x, y;

    Vector2()
		: x(0)
		, y(0)
   {
    };

    Vector2(int _x, int _y)
		: x(_x)
		, y(_y)
    {
    };
};

#endif //VECTOR2_H
