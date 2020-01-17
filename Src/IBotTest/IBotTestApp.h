#ifndef __IBOTTESTAPP_H__
#define __IBOTTESTAPP_H__

#include "Utils.h"
#include "GApp.h"
#include "GEngine_SDL.h"

class IBotTestApp : public GAppBase
{
	DECLARE_APP(IBotTestApp)

	public:
		IBotTestApp(GEngine* pEngine, int argc, char *argv[]);
		~IBotTestApp();

		virtual void Init(int argc, char *argv[]) override;
		virtual int Update(float dt);
		virtual int UpdatePause();
		virtual int Draw();

	private:
		class Canvas* m_pWorldCanva;
		class Canvas* m_pGraphCanva;

		class IBCubeWorld* m_pWorld;

		class IBPlannerTest* m_pPlanner;

		class IBGraphPlannerDisplay* m_pPlannerDisplay;

	public:
		static int s_iDummy;
};

#endif // __IBOTTESTAPP_H__

