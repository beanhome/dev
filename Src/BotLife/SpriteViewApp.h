#ifndef __SPRITEVIEWAPP_H__
#define __SPRITEVIEWAPP_H__

#include "Utils.h"
#include "GApp.h"
#include "GEngine_SDL.h"

class ImageFlipBook;

class SpriteViewApp : public GApp<GEngine_SDL>
{
	public:
		SpriteViewApp(int w, int h, const char* rootpath);
		~SpriteViewApp();

		virtual int Update(float dt);
		virtual int Draw();


	private:
		ImageFlipBook* m_pImage;
		bool		m_bPlay;
		bool		m_bLeft;
		bool		m_bRight;
		bool		m_bUp;
		bool		m_bDown;
		bool		m_bEnter;
		float 		m_fStateTime;
		float 		m_fStateDelay;
};

#endif // __SPRITEVIEWAPP_H__

