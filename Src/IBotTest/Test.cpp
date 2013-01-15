#include "Utils.h"

#define USE_GRAPH

#ifdef USE_GRAPH
#include "GEngine_SDL.h"
#include "InputEvent_SDL.h"
#include "Canvas.h"
#include "Timer.h"
#endif


#include "IBPlannerTest.h"
#include "World/IBCubeWorld.h"
#include "Graph/IBPlannerGraph.h"
#include "Graph/IBPlannerDebug.h"

IBWorld g_oWorld;


#ifdef USE_GRAPH
void DrawWorld(CanvasBase& oWorldCanva);
void DrawCube(const IBCube* pCube, CanvasBase& canva, int i, int j);
#endif



int main(int argc, char *argv[])
{
	InitLog(argc, argv);

#ifdef USE_GRAPH
	GEngine_SDL ge(1280, 720, 32);
	Canvas world_canva(ge, 0, 0, 1280, 192);
	Canvas graph_canva(ge, 0, 192, 1280, 512);
	world_canva.SetPrintFont(FONT_PATH, 14);
	graph_canva.SetPrintFont(FONT_PATH, 14);
#endif

	IBPlannerTest oPlanner(&g_oWorld);
#ifdef USE_GRAPH
	IBPlannerDisplay* oPlannerDisplay = new IBPlannerGraph(oPlanner, graph_canva);
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

		// TODO
#ifdef USE_GRAPH
		DrawWorld(world_canva);
#endif
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


#ifdef USE_GRAPH
void DrawWorld(CanvasBase& oWorldCanva)
{
	int size = 48;
	int space = 32;
	int line = oWorldCanva.GetHeight()-size;
	int left_space = 32;

	oWorldCanva.DrawLine(left_space, line, left_space + (size*g_oWorld.GetCubes().size()) + ((size+1)*g_oWorld.GetCubes().size()), line, Color(192, 255, 255));

	for (uint i=0 ; i < g_oWorld.GetCubes().size() ; ++i)
	{
		IBCube* pCube = &g_oWorld.GetCubes()[i];

		if (g_oWorld.GetTable().HasCube(pCube))
		{
			DrawCube(pCube, oWorldCanva, i, 0);
		}
	}
}

void DrawCube(const IBCube* pCube, CanvasBase& canva, int i, int j)
{
	int size = 48;
	int space = 32;
	int line = canva.GetHeight()-size;
	int left_space = 32;

	canva.DrawRect(left_space + space + i*(size+space), line-(size*(j+1)), size, size, Color(255, 255, 255));
	canva.Print(left_space + space + i*(size+space) + size/2, line - (size*j) - size/2, canva.GetPrintFont(), 12, Center, Color(255, 255, 255), "%s", pCube->GetName().c_str());

	if (pCube->GetTopCube() != NULL)
	{
		DrawCube(pCube->GetTopCube(), canva, i, j+1);
	}
}
#endif
