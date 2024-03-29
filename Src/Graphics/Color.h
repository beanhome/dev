#ifndef __COLOR_H__
#define __COLOR_H__

#include "Utils.h"

class Color
{
	public:
		Color(uint8 _r, uint8 _g, uint8 _b) : r(_r), g(_g), b(_b) {}
		Color(int _r, int _g, int _b) : r((uint8)_r), g((uint8)_g), b((uint8)_b) {}

		Color& operator=(const Color& c) { r=c.r; g=c.g; b=c.b; return *this; }

	public:
		uint8 r, g, b;

	public:
		static Color White;
		static Color Black;
		static Color Red;
		static Color Green;
		static Color Blue;
		static Color Cyan;
		static Color Magenta;
		static Color Yellow;

};


#endif // __COLOR_H__
