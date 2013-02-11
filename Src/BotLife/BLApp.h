#ifndef __BLAPP_H__
#define __BLAPP_H__

#include "Utils.h"
#include "GApp.h"
#include "GEngine_SDL.h"

class GEngine;
class Canvas;
class BLWorld;
class IBPlannerDisplay;

class BLApp : public GApp<GEngine_SDL>
{
	public:
		BLApp(int w, int h, float r);
		~BLApp();

		virtual int Update(float dt);
		virtual int Draw();

	private:
		Canvas* m_pWorldCanva;
		Canvas* m_pGraphCanva;

		BLWorld* m_pWorld;
		IBPlannerDisplay* m_pPlannerDisplay;
};

#endif // __GAPP_H__

