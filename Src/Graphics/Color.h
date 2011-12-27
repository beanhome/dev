#ifndef __COLOR_H__
#define __COLOR_H__

#include "Utils.h"

class Color
{
	public:
		Color(uint8 _r, uint8 _g, uint8 _b) : r(_r), g(_g), b(_b) {}

	public:
		uint8 r, g, b;
};


#endif // __COLOR_H__

