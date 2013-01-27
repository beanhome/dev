#include "Utils.h"

#include "GEngine_SDL.h"
#include "InputEvent_SDL.h"
#include "Canvas.h"
#include "Timer.h"

#include "Map/BLMap.h"
#include "Map/BLTiles.h"


int main(int argc, char *argv[])
{
	InitLog(argc, argv);

	GEngine_SDL ge(1600, 800, 32);
	ge.SetPrintFont(FONT_PATH);
	ge.Clear();

	int seed = (int)GetClock();
	LOG("Seed : %d\n", seed);
	srand(seed);

	BLTiles oTiles(ge, "summertiles");
	BLMap oMap(ge.GetWidth()/oTiles.GetTilesWidth(), ge.GetHeight()/oTiles.GetTilesHeight(), oTiles);

	//oMap.Debug();
	oMap.Display(ge);

	ge.Flip();

	bool bQuit = false;
	bool bRun = false;

	for (uint i=0 ; i<20 ; ++i)
	{
		ge.Clear();

		oMap.Step(i);
		//oMap.Debug();
		oMap.Display(ge);

		ge.Flip();
	}

	while (!bQuit)
	{
		ge.SaveEvent();
		if (ge.PollEvent())
		{
			if (ge.GetInputEvent().IsQuit()
				|| ge.GetInputEvent().IsKeyboard() && ge.GetInputEvent().GetKeyboardKey() == KEY_ESC)
				bQuit = true;

			/*
			if (!bRun && ge.GetInputEvent().IsKeyboard() && ge.GetInputEvent().GetKeyboardEvent() == KeyDown && ge.GetInputEvent().GetKeyboardKey() == KEY_SPACE)
				bRun = true;

			else if (bRun && ge.GetInputEvent().IsKeyboard() && ge.GetInputEvent().GetKeyboardEvent() == KeyDown && ge.GetInputEvent().GetKeyboardKey() == KEY_SPACE)
				bRun = false;
				*/
		}
	}

	return 0;
}

