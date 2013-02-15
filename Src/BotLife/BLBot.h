#ifndef __BOTLIFE_BOT_H__
#define __BOTLIFE_BOT_H__

#include "Utils.h"
#include "World\IBObject.h"
#include "BLWorld.h"
#include "World\IBVector2.h"

class GEngine;
class BLWorld;
class CanvasBase;
class ImageFlipBook;
class IBPlanner;
class BLProp;

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
			DownRight,
			Right,
			UpRight,
			Up,
			UpLeft,
			Left,
			DownLeft
		};


	public:
		void					SetLoc(float x, float y);
		void					SetPos(int i, int j);
		void					SetPos(const Vector2& p);

		const Vector2&			GetPos() const { return m_vPos; }
		const IBVector2&		GetIBPos() const { return m_vPos; }
		IBVector2*				GetIBPosAd() { return &m_vPos; }

		//uint					GetWidth() const { return m_iWidth; }
		//uint					GetHeight() const { return m_iHeight; }
					
		void					SetState(BotState state, BotDir dir=Down, float delay=-1.f);
		BotState				GetState() const { return m_eState; }
					
		void					Update(float dt);
		void					Draw(CanvasBase& canva) const;

		BotDir					GetDir() const { return m_eDir; }
		BotDir					ComputeDir(const Vector2& Start, const Vector2& Target) const;

		const IBPlanner&		GetPlanner() const { return *m_pPlanner; }
		IBPlanner&				GetPlanner() { return *m_pPlanner; } // To Del
		const BLWorld&			GetWorld() const { return m_oWorld; }
		BLWorld&				GetWorld() { return m_oWorld; }

		void					PickProp(BLProp* pProp);
		bool					HasObject(BLProp* pObj) const { return pObj == m_pCarryObject; }
		BLProp*					GetFirstObject() const { return m_pCarryObject; }

		void					AddGoal(const string& name);
		void					AddGoal(const string& name, IBObject* pUserData);
		void					AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2);
		void					AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3);

	private:
		BLWorld&				m_oWorld;

		ImageFlipBook*			m_pWalkImage;
		ImageFlipBook*			m_pWorkImage;
		//uint					m_iWidth;
		//uint 					m_iHeight;
		//uint 					m_iCenterX;
		//uint 					m_iCenterY;

		float					m_fLocX; // pixel
		float					m_fLocY; // pixel
		IBVector2				m_vPos; // Grid


		BotState				m_eState;
		BotDir 					m_eDir;
		Vector2					m_vTarget;
		float 					m_fStateTime;
		float 					m_fStateDelay;

		float					m_fStepTime;
		float					m_fStepDelay;

		IBPlanner*				m_pPlanner;

		BLProp*					m_pCarryObject;

	private:
		static float			s_fDirArrayX[8];
		static float			s_fDirArrayY[8];
		static Vector2			s_vDirArray[8];
};

#endif