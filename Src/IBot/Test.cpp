#include "Utils.h"

#include "GEngine_SDL.h"
#include "InputEvent_SDL.h"
#include "Color.h"
#include "Image.h"
#include "ImageRotoZoom.h"
#include "Canvas.h"
#include "ImageFlipBook.h"
#include "ImageResource_SDL.h"
#include "Timer.h"


#include "IBPlanner.h"
#include "World/IBWorld.h"

IBWorld g_oWorld;


int main(int argc, char *argv[])
{
	InitLog(argc, argv);

	IBPlanner oPlanner;

	g_oWorld.Init();

	g_oWorld.Print();

	oPlanner.AddGoal("IBFactDef_IsTopOf", g_oWorld.GetCubeA(), g_oWorld.GetCubeB());
	//oPlanner.AddGoal("IBFactDef_IsTopOf", g_oWorld.GetCubeB(), g_oWorld.GetCubeC());

	int res = 0;
	for (uint i=0 ; i<10 && res==0 ; ++i)
	{

		LOG("\n");
		LOG("****  %d  ****\n", i);
		res = oPlanner.Step();
	}

#if 0

	GEngine_SDL ge(1024, 748, 32);
	Canvas canva(ge, 100, 300, 300, 100);
	canva.SetPrintFont(FONT_PATH, 14);

	bool bContinue = true;

	ImageResource* pImageRes = ge.GetResource<ImageResource_SDL>(ImageResource_SDL::Desc(DATA_DIR "/PlanetWar/Images/Background.bmp"));
	
	ImageFlipBook* pImage = new ImageFlipBook(ge, ge.GetResource<ImageResource_SDL>(DATA_DIR "/Test/gb_walk.png"), 3, 6);
	pImage->SetPos(300, 200);
	pImage->SetCurrent(0);

	ImageRotoZoom* pImage2 = new ImageRotoZoom(canva, ge.GetResource<ImageResource_SDL>(DATA_DIR "/PlanetWar/Images/FleetRed.bmp"));
	pImage2->SetPos(100, 10);
	pImage2->SetZoom(0.6f);
	pImage2->SetRotation(75.f);


	float fDelay = 0.f;

	while(bContinue)
	{
		float fps = 1.f/(Timer::Get() - fDelay);
		fDelay = Timer::Get();

		while (true)
		{
			ge.SaveEvent();
			if (!ge.PollEvent())
				break;
			uint16 mx, my;
			ge.GetInputEvent().GetMouseMove(mx, my);
			ge.SetMouse(mx, my);

			if (ge.GetInputEvent().IsQuit())
				bContinue = false;

			if (ge.GetInputEvent().IsKeyboard() && ge.GetInputEvent().GetKeyboardKey() == KEY_ESC)
				bContinue = false;

			if (ge.GetInputEvent().IsKeyboard() && ge.GetInputEvent().GetKeyboardEvent() == KeyDown)
			{
				if (ge.GetPreviousInputEvent().IsKeyboard() == false || ge.GetPreviousInputEvent().GetKeyboardEvent() != KeyDown)
					pImage->SetCurrent((pImage->GetCurrent()+1) % 14);
			}
		}

		ge.Clear();
		ge.DrawImage(*pImageRes, 400, 400);

		ge.SetPrintParameter(14, 14, FONT_PATH, 10, LeftTop, Color(255, 200, 200));
		canva.SetPrintPos(0, 0);

		ge.CanvasBase::DrawRect(10, 10, 100, 100, Color(100, 200, 50));

		ge.Print("Hello World !");
		ge.Print("Next");


		pImage->Draw();
		pImage2->Draw();

		canva.DrawRect(0, 0, canva.GetWidth(), canva.GetHeight(), 20, 100, 255);
		canva.Print("Autre canva");

		ge.Print(ge.GetWidth()-5, 5, FONT_PATH, 14, RightTop, 200, 200, 255, "%.1f", fps);
		ge.Print(ge.GetWidth()-5, 20, FONT_PATH, 14, RightTop, 200, 200, 255, "%.3f", Timer::Get());

		ge.DrawFillRect(ge.GetMouseX()-5, ge.GetMouseY()-5, 10, 10, 255, 50, 100);

		ge.Print(ge.GetWidth()-5, 50, FONT_PATH, 14, RightTop, 200, 200, 255, "%d %d", ge.GetMouseX(), ge.GetMouseY());
		ge.Print(ge.GetWidth()-5, 65, FONT_PATH, 14, RightTop, 200, 200, 255, "%d %d", canva.GetMouseX(), canva.GetMouseY());

		ge.Flip();
	}

	delete pImage;
	delete pImage2;

#endif
    return 0;
}


