#ifndef __BLAPP_H__
#define __BLAPP_H__

#include "Utils.h"
#include "GApp.h"
#include "GEngine_SDL.h"

class GEngine;
class Canvas;
class BLWorld;
class IBPlannerDisplay;
class BLGoalMenu;

class BLApp : public GApp<GEngine_SDL>
{
	public:
		BLApp(int w, int h, float r, int sx, int sy, const char* tilesname);
		~BLApp();

		virtual int Update(float dt);
		virtual int UpdatePause();
		virtual int Draw();

		void UpdateUserInterface();

		Canvas& GetPlannerCanvas() { return *m_pGraphCanva; }

	private:
		Canvas* m_pWorldCanva;
		Canvas* m_pGraphCanva;

		BLWorld* m_pWorld;

		BLGoalMenu* m_pGoalMenu;
};

#endif // __GAPP_H__

