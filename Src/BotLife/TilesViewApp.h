#ifndef __TILESVIEWAPP_H__
#define __TILESVIEWAPP_H__

#include "Utils.h"
#include "GApp.h"
#include "Map/BLTiles.h"

class BLTiles;
class BLMap;

class TilesViewApp : public GAppBase
{
	DECLARE_APP(TilesViewApp)
	
	public:
		TilesViewApp(GEngine* pEngine, int argc, char *argv[]);
		~TilesViewApp();

		virtual int Update(float dt);
		virtual int Draw();


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

