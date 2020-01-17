#include "Utils.h"
#include "IBotTestApp.h"
#include "Timer.h"
#include "Alloc.h"
#include "GEngine_SDL.h"
#include "GApp.h"

// -a MapViewApp -t summertiles -w 1400 -h 1000 -x 64 -y 48

#if 1

extern "C" int SDL_main(int argc, char *argv[])
{
	// Force include IBotTestApp to AppList because is an external lib
	int iDummy = IBotTestApp::s_iDummy;

	InitLog(argc, argv);

	int w = GAppBase::GetArgAsInt('w', 920, argc, argv);
	int h = GAppBase::GetArgAsInt('h', 800, argc, argv);
	const char* sApp = GAppBase::GetArgAsString('a', "BLApp", argc, argv);
	const char* path = GAppBase::GetArgAsString('p', ".", argc, argv);
	int seed = GAppBase::GetArgAsInt('s', 0, argc, argv);

	if (seed == 0)
		seed = (int)GetClock();
	LOG("Seed : %d\n", seed);
	srand(seed);

	if (sApp == nullptr)
	{
		LOG("Error: Bad App\n");
		return -1;
	}

	GEngine_SDL oEngine(w, h, 32, path);

	GAppBase* pApp = GAppBase::InstanciateApp(sApp, &oEngine, argc, argv);
	if (pApp == nullptr)
		return -1;

	pApp->Init(argc, argv);

	int res = pApp->Loop();

	delete pApp;

	return res;
}



#else

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
#endif


