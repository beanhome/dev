#include "Utils.h"
#include "BLApp.h"
#include "MapViewApp.h"
#include "TilesViewApp.h"
#include "SpriteViewApp.h"
#include "Timer.h"
#include "Alloc.h"

// -a MapViewApp -t summertiles -w 1400 -h 1000 -x 64 -y 48

#if 0


class A
{
public:
	A()
	{
		LOG("A Contructor\n");
	}

	~A()
	{
		LOG("A Destructor\n");
	}

private:

};

void Test()
{
	LOG("\n");

	A* pA = new A;
	delete pA;

	LOG("\n");

	A* pATab = new A[2];
	delete[] pATab;
}

int main(int argc, char *argv[])
{
	InitLog(argc, argv);

	Test();

	return 0;
}


#else
extern "C" int SDL_main(int argc, char *argv[])
{
	InitLog(argc, argv);

	int w = 920;
	int h = 800;
	int sx = 32;
	int sy = 32;
	float r = 0.54f;
	const char* sTiles = "summertiles";
	const char* sApp = "BLApp";
	const char* path = ".";
	int seed = 0;

	for (int i=1 ; i<argc ; ++i)
	{
		if (argv[i][0] == '-')
		{
			//ASSERT(argc > i+1);
			switch (argv[i][1])
			{
				case 'a':		sApp = argv[i+1];			break;
				case 'w':		w = atoi(argv[i+1]);			break;
				case 'h':		h = atoi(argv[i+1]);			break;
				case 't':		sTiles = argv[i+1];			break;
				case 'r':		r = (float)atof(argv[i+1]);	break;
				case 'x':		sx = atoi(argv[i+1]);		break;
				case 'y':		sy = atoi(argv[i+1]);		break;
				case 's':		seed = atoi(argv[i+1]);		break;
				case 'p':		path = argv[i+1];			break;
			}
		}
	}

	if (seed == 0)
		seed = (int)GetClock();
	LOG("Seed : %d\n", seed);
	srand(seed);

	if (sApp == NULL)
	{
		LOG("Error: Bad App\n");
		return -1;
	}

	GAppBase* pApp = NULL;

	if (strncmp(sApp, "BLApp", 5) == 0)
		pApp = new BLApp(w, h, path, r, sx, sy, sTiles);
	else if (strncmp(sApp, "MapViewApp", 10) == 0)
		pApp = new MapViewApp(w, h, path, sx, sy, sTiles);
	else if (strncmp(sApp, "TilesViewApp", 12) == 0)
		pApp = new TilesViewApp(w, h, path, sTiles);
	else if (strncmp(sApp, "SpriteViewApp", 14) == 0)
		pApp = new SpriteViewApp(w, h, path);
	
	if (pApp == NULL)
		return -1;

	pApp->Init();

	int res = pApp->Loop();

	delete pApp;

	return res;
}
#endif


