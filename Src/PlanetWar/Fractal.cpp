#define _USE_MATH_DEFINES
#include <cmath>

#include "Utils.h"
#include "Graphic.h"

typedef unsigned int uint;
typedef unsigned char uint8;

FILE* g_MyLog = stdout;
bool g_bVisualDebug = false;

void Fractal(float& x, float& y, float cx, float cy)
{
	float xp = x;
	x = x*x - y*y + cx;
	y = 2.f * xp * y + cy;
}

void GetColor(float x, float y, uint8& r, uint8& g, uint8& b)
{
	/*
	float fLength = sqrt(x*x + y*y);

	uint iLength = (uint)(fLength) % 0x00FFFFFF;

	r = (iLength & 0x000000FF) >> 0;
	g = (iLength & 0x0000FF00) >> 8;
	b = (iLength & 0x00FF0000) >> 16;
	*/

	float fCoeff = 1.f / 1000000000.f;

	r = (uint8)(255.f * (atan(x*fCoeff) / M_PI_2) * 0.5f + 0.5f);
	g = (uint8)(255.f * (atan(y*fCoeff) / M_PI_2) * 0.5f + 0.5f);

	//r = (uint8)(x / 1000000.f);
	//g = (uint8)(y / 1000000.f);
	b = 0;
}


int main(int argc, char* argv[])
{
	uint width = 400;
	uint height = 400;
	GraphicEngine ge(width, height, 32);
	ge.Init();

	float cx = 0.f;
	float cy = 1.f;

	ge.Clear();

	bool bExit = false;
	for (uint i=0 ; i<width && !bExit ; ++i)
	{
		for (uint j=0 ; j<height && !bExit; ++j)
		{
			float x = (float)i / (float)width * 2.f - 1.f;
			float y = (float)j / (float)height * 2.f - 1.f;

			float ln_sq = 0.f;
			uint k;
			for (k=0 ; k<255 && ln_sq < 4.f ; ++k)
			{
				Fractal(x, y, cx, cy);
				ln_sq = x*x + y*y;
			}

			uint8 r, g, b;
			r = g = k;
			b = 0;
			//GetColor(x, y, r, g, b);

			LOG("%d %d : %f %f -> %d %d %d\n", i, j, x, y, r, g, b);
			ge.SetPixel(i, j, r, g, b);

			const SDL_Event& oEvent = ge.PollEvent();
			if (oEvent.type == SDL_QUIT)
				bExit = true;
		}
	}

	ge.Flip();

	while (!bExit)
	{
		const SDL_Event& oEvent = ge.WaitEvent();
		if (oEvent.type == SDL_QUIT)
			bExit = true;
	}

	ge.Close();

	return 0;
}

