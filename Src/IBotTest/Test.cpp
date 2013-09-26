#include "Utils.h"

#include "GEngine_SDL.h"
#include "InputEvent_SDL.h"
#include "Canvas.h"
#include "Timer.h"

#include "IBPlannerTest.h"
#include "World/IBCubeWorld.h"
#include "Display/IBPlannerDebug.h"
#include "Input.h"

void DrawWorld(const IBCubeWorld& oWorld, CanvasBase& oWorldCanva);
void DrawCube(const IBCube* pCube, CanvasBase& canva, int i, int j);



extern "C" int SDL_main(int argc, char *argv[])
{
	InitLog(argc, argv);

	IBCubeWorld oWorld;

	int w = 1280;
	int h = 996;
	int top = 192;
	int bRealTime = false;

	GEngine_SDL ge(w, h, 32, "../../");
	Canvas world_canva(ge, 0, 0, w, top);
	Canvas graph_canva(ge, 0, top, w, h-top);
	world_canva.SetPrintFont(FONT_PATH, 14);
	graph_canva.SetPrintFont(FONT_PATH, 14);

	IBPlannerTest oPlanner(&oWorld, graph_canva);
	
	oWorld.Init(0);
	oWorld.Print();
	oPlanner.AddGoal("IBFactDef_IsTopOf", oWorld.GetCubeA(), oWorld.GetCubeB());
	oPlanner.AddGoal("IBFactDef_IsTopOf", oWorld.GetCubeB(), oWorld.GetCubeC()); // uncomment to add


	bool bQuit = false;
	int i=0;
	double fTime = Timer::Get();

	while (!bQuit)
	{
		ge.UpdateInput();

		bQuit = (ge.GetInput()->IsQuit() || ge.GetInput()->GetVirtualKey(KEY_ESC) == KeyPressed);

		if (ge.GetInput()->GetVirtualKey(MOUSE_RIGHT) == KeyPressed)
		{
			if (graph_canva.IsMouseInside())
				oPlanner.StartDrag();
		}
		else if (ge.GetInput()->GetVirtualKey(MOUSE_RIGHT) == KeyDown)
		{
			if (oPlanner.IsDraging())
				oPlanner.UpdateDrag();
		}
		else if (ge.GetInput()->GetVirtualKey(MOUSE_RIGHT) == KeyUp)
		{
			oPlanner.StopDrag();
		}

		if (ge.GetInput()->GetVirtualKey(KEY_SPACE) == KeyPressed
		 || (bRealTime && Timer::Get() > fTime + 1.f))
		{

			LOG("\n");
			LOG("****  %d  ****\n", i++);
			/*res = */oPlanner.Step(true, false);

			IBPlannerDebug debug(oPlanner);
			debug.DrawGraph();

			fTime = Timer::Get();
		}

		ge.Clear();

		DrawWorld(oWorld, world_canva);
		oPlanner.Draw();
	
		ge.Flip();
	}

    return 0;
}


void DrawWorld(const IBCubeWorld& oWorld, CanvasBase& oWorldCanva)
{
	int size = 48;
	int space = 32;
	int line = oWorldCanva.GetHeight()-size;
	int left_space = 32;

	oWorldCanva.DrawLine(left_space, line, left_space + (size*oWorld.GetCubes().size()) + ((size+1)*oWorld.GetCubes().size()), line, Color(192, 255, 255));

	for (uint i=0 ; i < oWorld.GetCubes().size() ; ++i)
	{
		const IBCube* pCube = oWorld.GetCubes()[i];

		if (oWorld.GetTable().HasCube((IBCube*)pCube))
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
