#ifndef __MAPVIEWAPP_H__
#define __MAPVIEWAPP_H__

#include "Utils.h"
#include "GApp.h"
#include "GEngine_SDL.h"

class BLTiles;
class BLMap;

class MapViewApp : public GApp<GEngine_SDL>
{
	public:
		MapViewApp(int w, int h, const char* rootpath, int sx, int sy, const char* name);
		~MapViewApp();

		virtual int Update(float dt);
		virtual int Draw();

	private:
		BLTiles* m_pTiles;
		BLMap* m_pMap;

		Canvas* m_pCanvas;

		bool m_bDrag;
		int m_iStartDragX;
		int m_iStartDragY;

		int m_iMouseCaseX;
		int m_iMouseCaseY;
};

#endif // __MAPVIEWAPP_H__

