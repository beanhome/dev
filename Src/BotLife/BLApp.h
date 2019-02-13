#ifndef __BLAPP_H__
#define __BLAPP_H__

#include "Utils.h"
#include "GApp.h"
#include "GEngine_SDL.h"

class BLApp : public GApp<GEngine_SDL>
{
	public:
		BLApp(int w, int h, const char* rootpath, float r, int sx, int sy, const char* tilesname);
		~BLApp();

		virtual int Update(float dt);
		virtual int UpdatePause();
		virtual int Draw();

		void UpdateUserInterface();

		class Canvas& GetPlannerCanvas() { return *m_pGraphCanva; }

	private:
		class Canvas* m_pWorldCanva;
		class Canvas* m_pGraphCanva;

		class BLWorld* m_pWorld;

		class IBGraphPlannerDisplay* m_pPlannerDisplay;

		class BLGoalMenu* m_pGoalMenu;
		const class BLSquare* m_pSelectSquare;
};

#endif // __GAPP_H__

