#include "Utils.h"

//#define USE_GRAPH

#ifdef USE_GRAPH
#include "GEngine_SDL.h"
#include "InputEvent_SDL.h"
#include "Canvas.h"
#include "Timer.h"
#endif


#include "IBPlanner.h"
#include "World/IBWorld.h"
#include "Graph/IBPlannerGraph.h"
#include "Graph/IBPlannerDebug.h"

IBWorld g_oWorld;


int main(int argc, char *argv[])
{
	InitLog(argc, argv);

#ifdef USE_GRAPH
	GEngine_SDL ge(1280, 748, 32);
	Canvas world_canva(ge, 0, 0, 1280, 128);
	Canvas graph_canva(ge, 0, 128, 1280, 620);
	world_canva.SetPrintFont(FONT_PATH, 14);
	graph_canva.SetPrintFont(FONT_PATH, 14);
#endif

	IBPlanner oPlanner;
#ifdef USE_GRAPH
	IBPlannerDisplay* oPlannerDisplay = new IBPlannerGraph(oPlanner, world_canva, graph_canva);
#else
	IBPlannerDisplay* oPlannerDisplay = new IBPlannerDebug(oPlanner);
#endif
	
	g_oWorld.Init();
	g_oWorld.Print();
	oPlanner.AddGoal("IBFactDef_IsTopOf", g_oWorld.GetCubeA(), g_oWorld.GetCubeB());
	//oPlanner.AddGoal("IBFactDef_IsTopOf", g_oWorld.GetCubeB(), g_oWorld.GetCubeC()); // uncomment to add


	bool bQuit = false;

	int res = 0;
	for (uint i=0 ; i<10 && res==0 && !bQuit; ++i)
	{
#ifdef USE_GRAPH
		ge.Clear();
#endif

		LOG("\n");
		LOG("****  %d  ****\n", i);
		res = oPlanner.Step();

		oPlannerDisplay->DrawWorld();
		oPlannerDisplay->DrawGraph();
	
#ifdef USE_GRAPH
		ge.Flip();

		float fTime = Timer::Get();
		while  (res == 1 || Timer::Get() < fTime + 1.f)
		{
			ge.SaveEvent();
			if (ge.PollEvent())
			{
				if (ge.GetInputEvent().IsQuit())
				{
					bQuit = true;
					break;
				}

				if (ge.GetInputEvent().IsKeyboard() && ge.GetInputEvent().GetKeyboardKey() == KEY_ESC)
					bQuit = true;

				if (ge.GetInputEvent().IsKeyboard())
					break;
			}
		}
#else
		printf("Press Enter\n");
		getchar();
#endif
	}

    return 0;
}


