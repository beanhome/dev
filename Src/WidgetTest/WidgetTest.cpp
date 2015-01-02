#include "Utils.h"

#include "GEngine_SDL.h"
#include "WidgetEditor.h"


extern "C" int SDL_main(int argc, char *argv[])
{
	InitLog(argc, argv);

	int w = 1280;
	int h = 720;

	GEngine_SDL ge(w, h, 32, "../../");
	WidgetEditor oWidgetEditor(ge);

	return oWidgetEditor.Loop();
}

