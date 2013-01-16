#include "Utils.h"

#include "GEngine_SDL.h"
#include "InputEvent_SDL.h"
#include "Canvas.h"
#include "Timer.h"

#include "IBPlanner.h"
#include "Graph/IBPlannerGraph.h"
#include "BLBot.h"
#include "BLWorld.h"


int main(int argc, char *argv[])
{
	InitLog(argc, argv);

	float ratio = 0.7f;
	uint w = 900;
	uint h = 600;

	GEngine_SDL ge(w, h, 32);
	Canvas world_canva(ge, 0, 0, w, (uint16)(ratio*(float)h));
	Canvas graph_canva(ge, 0, (sint16)(ratio*(float)h), w, (uint16)((1.f-ratio)*(float)h));
	world_canva.SetPrintFont(FONT_PATH, 14);
	graph_canva.SetPrintFont(FONT_PATH, 14);

	BLWorld oWorld(world_canva, 20);

	IBPlannerDisplay* oPlannerDisplay = new IBPlannerGraph(oWorld.GetBot().GetPlanner(), graph_canva);

	bool bQuit = false;

	double fTime = Timer::Get();
	double fLastTime = fTime;

	while (!bQuit)
	{
		fLastTime = fTime;
		fTime = Timer::Get();
		float dt = (float)(fTime - fLastTime);
		dt = min(dt, 0.1f);

		ge.Clear();

		oWorld.Update(dt);
		oWorld.Draw();
		oPlannerDisplay->DrawGraph();

		ge.Flip();

		ge.SaveEvent();
		if (ge.PollEvent())
		{
			if (ge.GetInputEvent().IsQuit()
			 || ge.GetInputEvent().IsKeyboard() && ge.GetInputEvent().GetKeyboardKey() == KEY_ESC)
				bQuit = true;

			//if (ge.GetInputEvent().IsKeyboard())
			//	break;
		}
	}

	return 0;
}

