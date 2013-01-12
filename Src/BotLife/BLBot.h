#ifndef __BOTLIFE_BOT_H__
#define __BOTLIFE_BOT_H__

#include "Utils.h"
#include "World\IBObject.h"
#include "NavDijkstra.h"
#include "BLWorld.h"
#include "NavAStar.h"
#include "Vector2.h"

class GEngine;
class BLWorld;
class CanvasBase;
class ImageFlipBook;

class BLBot : public IBObject
{
	public:
		BLBot(GEngine& ge, BLWorld& oWorld);
		~BLBot();

		enum BotState
		{
			Idle,
			Walk,
			Action,
		};

		enum BotDir
		{
			Down,
			Right,
			Up,
			Left
		};


	public:
		void				SetPos(float x, float y);
		void				SetLoc(float i, float j);
					
		uint				GetWidth() const { return m_iWidth; }
		uint				GetHeight() const { return m_iHeight; }
					
		void				SetState(BotState state, BotDir dir=Down, float delay=-1.f);
		BotState			GetState() const { return m_eState; }
					
		void				Update(float dt);
		void				Draw(CanvasBase& canva) const;

		BotDir				ComputeDir(const Vector2& Start, const Vector2& Target) const;

	private:
		BLWorld&			m_oWorld;

		ImageFlipBook*		m_pImage;
		uint				m_iWidth;
		uint 				m_iHeight;
		uint 				m_iCenterX;
		uint 				m_iCenterY;
		uint 				m_iAnimImgcount;

		float				m_fLocX; // pixel
		float				m_fLocY; // pixel
		Vector2				m_vPos; // Grid


		BotState 			m_eState;
		BotDir 				m_eDir;
		Vector2				m_vTarget;
		float 				m_fStateTime;
		float 				m_fStateDelay;

		NavDijkstra<BLSquare>*	m_pNavDijkstra;
		NavAStar<BLSquare>*	m_pNavAStar;
		Path				m_oPath;

	private:
		static float s_fDirArrayX[4];
		static float s_fDirArrayY[4];
		static Vector2 s_vDirArray[4];
};

#endif