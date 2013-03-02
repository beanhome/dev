#ifndef __TILESVIEWAPP_H__
#define __TILESVIEWAPP_H__

#include "Utils.h"
#include "GApp.h"
#include "GEngine_SDL.h"
#include "Map\BLTiles.h"

class BLTiles;
class BLMap;

class TilesViewApp : public GApp<GEngine_SDL>
{
	public:
		TilesViewApp(int w, int h, const char* rootpath, const char* name);
		~TilesViewApp();

		virtual int Update(float dt);
		virtual int Draw();

		virtual int Loop();


	private:
		enum Mode
		{
			Explore,
			Choose_TL,
			Choose_TR,
			Choose_BL,
			Choose_BR,
			Save,
		};

		BLTiles* m_pTiles;

		Mode mode;
		Mode lastmode;

		TileKey oKey;
		int id;

};

#endif // __TILESVIEWAPP_H__

