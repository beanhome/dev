#include "Utils.h"
#include "BLApp.h"
#include "MapViewApp.h"
#include "TilesViewApp.h"



int main(int argc, char *argv[])
{
	InitLog(argc, argv);

	//GAppBase* pApp = new BLApp(800, 600, 0.54f);
	GAppBase* pApp = new MapViewApp(1600, 800, "wintertiles");
	//GAppBase* pApp = new TilesViewApp(800, 800, "wintertiles");

	int res = pApp->Loop();

	delete pApp;

	return res;
}

