#ifndef __COLOR_H__
#define __COLOR_H__

#include "Utils.h"

class Color
{
	public:
		Color(uint8 _r, uint8 _g, uint8 _b) : r(_r), g(_g), b(_b) {}
		Color(int _r, int _g, int _b) : r((uint8)_r), g((uint8)_g), b((uint8)_b) {}

	public:
		uint8 r, g, b;
};


#endif // __COLOR_H__

