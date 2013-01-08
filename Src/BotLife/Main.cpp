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
	uint h = 980;

	GEngine_SDL ge(1280, h, 32);
	Canvas world_canva(ge, 0, 0, 1280, (uint16)(ratio*(float)h));
	Canvas graph_canva(ge, 0, (sint16)(ratio*(float)h), 1280, (uint16)((1.f-ratio)*(float)h));
	world_canva.SetPrintFont(FONT_PATH, 14);
	graph_canva.SetPrintFont(FONT_PATH, 14);

	BLWorld oWorld(world_canva, 20);


	IBPlanner oPlanner;
	IBPlannerDisplay* oPlannerDisplay = new IBPlannerGraph(oPlanner, graph_canva);

	/*
	g_oWorld.Init();
	g_oWorld.Print();
	oPlanner.AddGoal("IBFactDef_IsTopOf", g_oWorld.GetCubeA(), g_oWorld.GetCubeB());
	//oPlanner.AddGoal("IBFactDef_IsTopOf", g_oWorld.GetCubeB(), g_oWorld.GetCubeC()); // uncomment to add
	*/


	bool bQuit = false;

	float fTime = Timer::Get();
	float fLastTime = fTime;

	while (!bQuit)
	{
		fLastTime = fTime;
		fTime = Timer::Get();
		float dt = fTime - fLastTime;

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

