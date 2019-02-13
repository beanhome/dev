#include "Utils.h"
#include "IBotTestApp.h"
#include "Timer.h"
#include "Alloc.h"

extern "C" int SDL_main(int argc, char *argv[])
{
	InitLog(argc, argv);

	int w = 920;
	int h = 800;
	int sx = 32;
	int sy = 32;
	float r = 0.3f;

	for (int i=1 ; i<argc ; ++i)
	{
		if (argv[i][0] == '-')
		{
			//ASSERT(argc > i+1);
			switch (argv[i][1])
			{
				case 'w':		w = atoi(argv[i+1]);			break;
				case 'h':		h = atoi(argv[i+1]);			break;
				case 'x':		sx = atoi(argv[i+1]);		break;
				case 'y':		sy = atoi(argv[i+1]);		break;
				case 'r':		r = (float)atof(argv[i + 1]);	break;
			}
		}
	}

	GAppBase* pApp = new IBotTestApp(w, h, sx, sy, r, ".");
	
	if (pApp == NULL)
		return -1;

	pApp->Init();

	int res = pApp->Loop();

	delete pApp;

	return res;
}


