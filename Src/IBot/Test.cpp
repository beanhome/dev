#include "Utils.h"

#include "GEngine_SDL.h"
#include "InputEvent_SDL.h"
#include "Color.h"
#include "Image.h"
#include "ImageRotoZoom.h"


int main(int argc, char *argv[])
{
	InitLog(argc, argv);

	GEngine_SDL ge(1024, 748, 32);

	bool bContinue = true;

	ImageResource* pImageRes = ge.GetImageResource(DATA_DIR "/PlanetWar/Images/FleetBlue.png");
	Image* pImage = new Image(&ge, DATA_DIR "/PlanetWar/Images/FleetBlue.bmp");
	ImageRotoZoom* pImage2 = new ImageRotoZoom(&ge, DATA_DIR "/PlanetWar/Images/FleetRed.bmp");
	pImage->SetPos(300, 200);
	pImage2->SetPos(400, 300);
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

		ge.Flip();
	}

	delete pImage;
	delete pImage2;

    return 0;
}


