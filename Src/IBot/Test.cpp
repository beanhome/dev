#include "Utils.h"

#include "GEngine_SDL.h"
#include "InputEvent_SDL.h"
#include "Color.h"
#include "Image.h"
#include "ImageRotoZoom.h"
#include "Canvas.h"


int main(int argc, char *argv[])
{
	InitLog(argc, argv);

	GEngine_SDL ge(1024, 748, 32);
	Canvas canva(ge, 100, 300, 300, 50);
	canva.SetPrintFont(FONT_PATH, 14);

	bool bContinue = true;

	ImageResource* pImageRes = ge.GetImageResource(DATA_DIR "/PlanetWar/Images/FleetBlue.png");
	Image* pImage = new Image(&ge, DATA_DIR "/PlanetWar/Images/FleetBlue.bmp");
	pImage->SetPos(300, 200);

	ImageRotoZoom* pImage2 = new ImageRotoZoom(&canva, DATA_DIR "/PlanetWar/Images/FleetRed.bmp");
	pImage2->SetPos(100, 10);
	pImage2->SetZoom(0.6f);
	pImage2->SetRotation(90.f);

	while(bContinue)
	{
		const InputEvent& oInputEvent = ge.PollEvent();
		if (oInputEvent.IsQuit())
			bContinue = false;

		ge.Clear();

		ge.CanvasBase::DrawRect(10, 10, 100, 100, Color(100, 200, 50));
		ge.SetPrintParameter(14, 14, FONT_PATH, 10, LeftTop, Color(255, 200, 200));
		ge.Print("Hello World !");
		ge.Print("Next");

		ge.DrawImage(*pImageRes, 200, 100, 0.f, 0.5f);

		pImage->Draw();
		pImage2->Draw();

		canva.DrawRect(0, 0, canva.GetWidth(), canva.GetHeight(), 20, 100, 255);
		canva.Print("Autre canva");

		ge.Flip();
	}

	delete pImage;
	delete pImage2;

    return 0;
}


