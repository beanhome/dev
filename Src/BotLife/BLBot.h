#ifndef __BOTLIFE_BOT_H__
#define __BOTLIFE_BOT_H__

#include "Utils.h"
#include "World/IBObject.h"
#include "BLWorld.h"
#include "World/IBVector2.h"

class GEngine;
class BLWorld;
class CanvasBase;
class ImageFlipBook;
class IBPlanner;
class BLProp;
class IBGoal;

class BLBot : public IBObject
{
	public:
		BLBot(GEngine& ge, BLWorld& oWorld, CanvasBase& oPlannerCanvas);
		~BLBot();

		enum BotState
		{
			Idle,
			Walk,
			Action,
			Push,
			
			BotState_MAX,
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
		void					GetLoc(float& x, float& y) const { x = m_fLocX, y = m_fLocY; }
		float					GetLocX() const { return m_fLocX; }
		float					GetLocY() const { return m_fLocY; }
		void					SetLoc(float x, float y);
		void					FixLoc();
		void					SetPos(int i, int j);
		void					SetPos(const Vector2& p);

		const Vector2&			GetPos() const { return m_vPos; }
		const Vector2&			GetTarget() const { return m_vTarget; }
		const IBVector2&		GetIBPos() const { return m_vPos; }
		IBVector2*				GetIBPosAd() { return &m_vPos; }

		//uint					GetWidth() const { return m_iWidth; }
		//uint					GetHeight() const { return m_iHeight; }
					
		void					SetState(BotState state, BotDir dir=Down, float delay=-1.f, BLProp* pObj=NULL);
		BotState				GetState() const { return m_eState; }
		bool					HasFinishState() const { return m_fStateTime > m_fStateDelay; }
					
		void					Update(float dt);
		void					Draw() const;

		BotDir					GetDir() const { return m_eDir; }
		BotDir					ComputeDir(const Vector2& Start, const Vector2& Target) const;

		const IBPlanner&		GetPlanner() const { return *m_pPlanner; }
		IBPlanner&				GetPlanner() { return *m_pPlanner; } // To Del
		const BLWorld&			GetWorld() const { return m_oWorld; }
		BLWorld&				GetWorld() { return m_oWorld; }

		void					PickProp(BLProp* pProp);
		bool					HasObject(BLProp* pObj) const { return (pObj != NULL && pObj == m_pCarryObject); }
		BLProp*					GetFirstObject() const { return m_pCarryObject; }
		void					DropObject(BLProp* pProp, const IBVector2& pos);

		void					AddGoal(const IBGoal& goal);

		void					AddGoal(const string& name);
		void					AddGoal(const string& name, IBObject* pUserData);
		void					AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2);
		void					AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3);

		virtual	void			FormatData() const {}

	private:
		BLWorld&				m_oWorld;

		ImageFlipBook*			m_pIdleImage;
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
		BLProp*					m_pPushObject;

	private:
		static const char*		s_sStateString[BotState_MAX];
		static const char*		s_sDirString[8];
		static float			s_fDirArrayX[8];
		static float			s_fDirArrayY[8];
		static Vector2			s_vDirArray[8];
};

#endif
