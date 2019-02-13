#ifndef __MAPVIEWAPP_H__
#define __MAPVIEWAPP_H__

#include "Utils.h"
#include "GApp.h"
#include "GEngine_SDL.h"

class IBotTestApp : public GApp<GEngine_SDL>
{
	public:
		IBotTestApp(int w, int h, int sx, int sy, float r, const char* rootpath);
		~IBotTestApp();

		virtual void Init() override;
		virtual int Update(float dt);
		virtual int UpdatePause();
		virtual int Draw();

	private:
		class Canvas* m_pWorldCanva;
		class Canvas* m_pGraphCanva;

		class IBCubeWorld* m_pWorld;

		class IBPlannerTest* m_pPlanner;

		class IBGraphPlannerDisplay* m_pPlannerDisplay;
};

#endif // __MAPVIEWAPP_H__

