#include "Utils.h"

#include "GEngine_SDL.h"
#include "WidgetEditor.h"

#ifdef _WIN32
extern "C" int SDL_main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	InitLog(argc, argv);

	int w = 1280;
	int h = 720;

	const char* path = ".";

	for (int i=1 ; i<argc ; ++i)
	{
		if (argv[i][0] == '-')
		{
			ASSERT(argc > i+1);
			switch (argv[i][1])
			{
				case 'w':		w = atoi(argv[i+1]);		break;
				case 'h':		h = atoi(argv[i+1]);		break;
				case 'p':		path = argv[i+1];			break;
			}
		}
	}

	WidgetEditor oWidgetEditor(w, h, path);

	oWidgetEditor.Init();

	int ret = oWidgetEditor.Loop();

	oWidgetEditor.Close();

	return ret;
}

