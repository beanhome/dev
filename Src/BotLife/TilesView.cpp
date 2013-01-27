#include "Utils.h"

#include "GEngine_SDL.h"
#include "InputEvent_SDL.h"
#include "Canvas.h"
#include "Timer.h"

#include "BLBot.h"
#include "BLWorld.h"
#include <complex>
#include "Map/BLMap.h"
#include "Map/BLTiles.h"


int main(int argc, char *argv[])
{
	InitLog(argc, argv);

	GEngine_SDL ge(800, 800, 32);
	ge.SetPrintFont(FONT_PATH);
	ge.Clear();

	BLTiles oTiles(ge, "summertiles");

	bool bQuit = false;
	bool bLeft = false;
	bool bRight = false;

	int id = 200; //oTiles.Find(DarkGrass);
	if (id < 0)
		id = 0;

	enum Mode
	{
		Explore,
		Choose_TL,
		Choose_TR,
		Choose_BL,
		Choose_BR,
		Save,
	};

	Mode mode = Explore;
	Mode lastmode = Explore;

	TileKey oKey = oTiles.Find(id);

	while (!bQuit)
	{
		lastmode = mode;

		switch (mode)
		{
			case Explore:
				if (bLeft) id = max(0, id-1);
				if (bRight) id = min(id+1, oTiles.GetTilesCount());
				oKey = oTiles.Find(id);
				break;

			case Choose_TL:
				if (bLeft) oKey.TL = (oKey.TL-1) % CaseType_MAX;
				if (bRight) oKey.TL = (oKey.TL+1) % CaseType_MAX;
				break;

			case Choose_TR:
				if (bLeft) oKey.TR = (oKey.TR-1) % CaseType_MAX;
				if (bRight) oKey.TR = (oKey.TR+1) % CaseType_MAX;
				break;

			case Choose_BL:
				if (bLeft) oKey.BL = (oKey.BL-1) % CaseType_MAX;
				if (bRight) oKey.BL = (oKey.BL+1) % CaseType_MAX;
				break;

			case Choose_BR:
				if (bLeft) oKey.BR = (oKey.BR-1) % CaseType_MAX;
				if (bRight) oKey.BR = (oKey.BR+1) % CaseType_MAX;
				break;
		}

		bLeft = false;
		bRight = false;

		ge.Clear();

		int iTileSize = 128;

		ge.Print(400, 150, ge.GetPrintFont(), 40, CenterBottom, 0, 0, 0, "%d", id);
		oTiles.DrawTile(ge, id, 400, 400, iTileSize, iTileSize);

		if (oKey.TL != (uint8)-1)
		{
			oTiles.DrawTile(ge, oTiles.Find((CaseType)oKey.TL), 400-iTileSize, 400-iTileSize, iTileSize, iTileSize);
			ge.Print(400-iTileSize, 400-iTileSize, ge.GetPrintFont(), 20, Center, 0, 0, 0, "%s", BLMap::s_sCaseType[oKey.TL]);
		}

		if (oKey.TR != (uint8)-1)
		{
			oTiles.DrawTile(ge, oTiles.Find((CaseType)oKey.TR), 400+iTileSize, 400-iTileSize, iTileSize, iTileSize);
			ge.Print(400+iTileSize, 400-iTileSize, ge.GetPrintFont(), 20, Center, 0, 0, 0, "%s", BLMap::s_sCaseType[oKey.TR]);
		}

		if (oKey.BL != (uint8)-1)
		{
			oTiles.DrawTile(ge, oTiles.Find((CaseType)oKey.BL), 400-iTileSize, 400+iTileSize, iTileSize, iTileSize);
			ge.Print(400-iTileSize, 400+iTileSize, ge.GetPrintFont(), 20, Center, 0, 0, 0, "%s", BLMap::s_sCaseType[oKey.BL]);
		}

		if (oKey.BR != (uint8)-1)
		{
			oTiles.DrawTile(ge, oTiles.Find((CaseType)oKey.BR), 400+iTileSize, 400+iTileSize, iTileSize, iTileSize);
			ge.Print(400+iTileSize, 400+iTileSize, ge.GetPrintFont(), 20, Center, 0, 0, 0, "%s", BLMap::s_sCaseType[oKey.BR]);
		}

		if (oKey.TL != (uint8)-1 && oKey.TR != (uint8)-1)
			oTiles.DrawTile(ge, oTiles.Find((CaseType)oKey.TL, (CaseType)oKey.TR, (CaseType)oKey.TL, (CaseType)oKey.TR), 400, 400-iTileSize, iTileSize, iTileSize);
		
		if (oKey.BL != (uint8)-1 && oKey.BR != (uint8)-1)
			oTiles.DrawTile(ge, oTiles.Find((CaseType)oKey.BL, (CaseType)oKey.BR, (CaseType)oKey.BL, (CaseType)oKey.BR), 400, 400+iTileSize, iTileSize, iTileSize);

		if (oKey.TL != (uint8)-1 && oKey.BL != (uint8)-1)
			oTiles.DrawTile(ge, oTiles.Find((CaseType)oKey.TL, (CaseType)oKey.TL, (CaseType)oKey.BL, (CaseType)oKey.BL), 400-iTileSize, 400, iTileSize, iTileSize);
		
		if (oKey.TR != (uint8)-1 && oKey.BR != (uint8)-1)
			oTiles.DrawTile(ge, oTiles.Find((CaseType)oKey.TR, (CaseType)oKey.TR, (CaseType)oKey.BR, (CaseType)oKey.BR), 400+iTileSize, 400, iTileSize, iTileSize);

		switch (mode)
		{
			case Explore:
				break;

			case Choose_TL:
				ge.DrawRect(400-iTileSize*3/2, 400-iTileSize*3/2, iTileSize, iTileSize, 0, 0, 0);
				break;

			case Choose_TR:
				ge.DrawRect(400+iTileSize/2, 400-iTileSize*3/2, iTileSize, iTileSize, 0, 0, 0);
				break;

			case Choose_BL:
				ge.DrawRect(400-iTileSize*3/2, 400+iTileSize/2, iTileSize, iTileSize, 0, 0, 0);
				break;

			case Choose_BR:
				ge.DrawRect(400+iTileSize/2, 400+iTileSize/2, iTileSize, iTileSize, 0, 0, 0);
				break;
		}

		ge.Flip();

		while (!bQuit && !bLeft && !bRight && lastmode == mode)
		{
			ge.SaveEvent();
			if (ge.PollEvent())
			{
				if (ge.GetInputEvent().IsQuit())
					bQuit = true;

				if (ge.GetInputEvent().IsKeyboard() && ge.GetInputEvent().GetKeyboardEvent() == KeyDown)
				{
					switch (mode)
					{
						case Explore:
							if      (!bLeft && ge.GetInputEvent().GetKeyboardKey() == KEY_LEFT)		bLeft = true;
							else if (!bRight && ge.GetInputEvent().GetKeyboardKey() == KEY_RIGHT)	bRight = true;
							else if (ge.GetInputEvent().GetKeyboardKey() == KEY_F1)		mode = Choose_TL;
							else if (ge.GetInputEvent().GetKeyboardKey() == KEY_F2)		mode = Choose_TR;
							else if (ge.GetInputEvent().GetKeyboardKey() == KEY_F3)		mode = Choose_BL;
							else if (ge.GetInputEvent().GetKeyboardKey() == KEY_F4)		mode = Choose_BR;
							else if (ge.GetInputEvent().GetKeyboardKey() == KEY_ESC)	bQuit = true;
							else if (ge.GetInputEvent().GetKeyboardKey() == KEY_DELETE)
							{
								oTiles.Del(id);
							}
							break;

						case Choose_TL:
						case Choose_TR:
						case Choose_BL:
						case Choose_BR:
							if      (ge.GetInputEvent().GetKeyboardKey() == KEY_ESC)	mode = Explore;
							else if (!bLeft && ge.GetInputEvent().GetKeyboardKey() == KEY_LEFT)		bLeft = true;
							else if (!bRight && ge.GetInputEvent().GetKeyboardKey() == KEY_RIGHT)	bRight = true;
							else if (ge.GetInputEvent().GetKeyboardKey() == KEY_F1)		mode = Choose_TL;
							else if (ge.GetInputEvent().GetKeyboardKey() == KEY_F2)		mode = Choose_TR;
							else if (ge.GetInputEvent().GetKeyboardKey() == KEY_F3)		mode = Choose_BL;
							else if (ge.GetInputEvent().GetKeyboardKey() == KEY_F4)		mode = Choose_BR;
							else if (ge.GetInputEvent().GetKeyboardKey() == KEY_SPACE)
							{
								oTiles.Add(oKey, id);
								mode = Explore;
							}
							break;
					}
				}
			}
		}
	}

	return 0;
}

