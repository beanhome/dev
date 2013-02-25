#include "Utils.h"
#include "BLApp.h"
#include "MapViewApp.h"
#include "TilesViewApp.h"
#include "SpriteViewApp.h"
#include "Timer.h"

enum AppType
{
	AT_BLApp,
	AT_MapViewApp,
	AT_TilesViewApp,
};


int main(int argc, char *argv[])
{
	InitLog(argc, argv);

	int w = 800;
	int h = 800;
	int sx = 16;
	int sy = 16;
	float r = 0.5f;
	const char* sTiles = "summertiles";
	const char* sApp = NULL;
	int seed = 0;

	for (int i=1 ; i<argc ; ++i)
	{
		if (argv[i][0] == '-')
		{
			ASSERT(argc > i+1);
			switch (argv[i][1])
			{
				case 'a':		sApp = argv[i+1];			break;
				case 'w':		w = atoi(argv[i+1]);		break;
				case 'h':		h = atoi(argv[i+1]);		break;
				case 't':		sTiles = argv[i+1];			break;
				case 'r':		r = (float)atof(argv[i+1]);	break;
				case 'x':		sx = atoi(argv[i+1]);		break;
				case 'y':		sy = atoi(argv[i+1]);		break;
				case 's':		seed = atoi(argv[i+1]);		break;
			}
		}
	}

	if (seed == 0)
		seed = (int)GetClock();
	LOG("Seed : %d\n", seed);
	srand(seed);

	if (sApp == NULL)
		return -1;

	GAppBase* pApp = NULL;

	if (_strnicmp(sApp, "BLApp", 5) == 0)
		pApp = new BLApp(w, h, r, sx, sy, sTiles);
	else if (_strnicmp(sApp, "MapViewApp", 10) == 0)
		pApp = new MapViewApp(w, h, sTiles);
	else if (_strnicmp(sApp, "TilesViewApp", 12) == 0)
		pApp = new TilesViewApp(w, h, sTiles);
	else if (_strnicmp(sApp, "SpriteViewApp", 14) == 0)
		pApp = new SpriteViewApp(w, h);
	

	if (pApp == NULL)
		return -1;

	int res = pApp->Loop();

	delete pApp;

	return res;
}

