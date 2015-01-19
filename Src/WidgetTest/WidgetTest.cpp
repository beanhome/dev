#include "Utils.h"

#include "GEngine_SDL.h"
#include "WidgetEditor.h"


extern "C" int SDL_main(int argc, char *argv[])
{
	InitLog(argc, argv);

	int w = 1280;
	int h = 720;

	WidgetEditor oWidgetEditor(w, h, "../../Data/Widget/Black/");

	oWidgetEditor.Init();

	int ret = oWidgetEditor.Loop();

	oWidgetEditor.Close();

	return ret;
}

