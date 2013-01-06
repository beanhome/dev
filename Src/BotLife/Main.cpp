#include "Utils.h"

#include "GEngine_SDL.h"
#include "InputEvent_SDL.h"
#include "Canvas.h"
#include "Timer.h"

#include "IBPlanner.h"
#include "Graph/IBPlannerGraph.h"
#include "Bot.h"

void DrawWorld(CanvasBase& canva);

Bot* pBot;

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

	pBot = new Bot(ge);

	IBPlanner oPlanner;
	IBPlannerDisplay* oPlannerDisplay = new IBPlannerGraph(oPlanner, graph_canva);

	/*
	g_oWorld.Init();
	g_oWorld.Print();
	oPlanner.AddGoal("IBFactDef_IsTopOf", g_oWorld.GetCubeA(), g_oWorld.GetCubeB());
	//oPlanner.AddGoal("IBFactDef_IsTopOf", g_oWorld.GetCubeB(), g_oWorld.GetCubeC()); // uncomment to add
	*/


	bool bQuit = false;

	int res = 0;
	for (uint i=0 ; i<10 && res==0 && !bQuit; ++i)
	{
		ge.Clear();

		LOG("\n");
		LOG("****  %d  ****\n", i);
		
		res = oPlanner.Step();

		DrawWorld(world_canva);
		oPlannerDisplay->DrawGraph();

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
	}

	return 0;
}


void DrawWorld(CanvasBase& canva)
{
	canva.DrawRect(0, 0, canva.GetWidth(), canva.GetHeight(), Color(255, 0, 0));

	pBot->Draw(canva);
}
