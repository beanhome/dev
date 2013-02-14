#include "Utils.h"
#include "BLApp.h"
#include "MapViewApp.h"
#include "TilesViewApp.h"

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
	float r = 0.5f;
	const char* sTiles = "summertiles";
	const char* sApp = NULL;

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
				case 'r':		r = (float)atof(argv[i+1]);		break;
			}
		}
	}

	if (sApp == NULL)
		return -1;

	GAppBase* pApp = NULL;

	if (_strnicmp(sApp, "BLApp", 5) == 0)
		pApp = new BLApp(w, h, r);
	else if (_strnicmp(sApp, "MapViewApp", 10) == 0)
		pApp = new MapViewApp(w, h, sTiles);
	else if (_strnicmp(sApp, "TilesViewApp", 12) == 0)
		pApp = new TilesViewApp(w, h, sTiles);

	if (pApp == NULL)
		return -1;

	int res = pApp->Loop();

	delete pApp;

	return res;
}

