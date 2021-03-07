#ifndef __BOTLIFE_BOT_H__
#define __BOTLIFE_BOT_H__

#include "Utils.h"
#include "World/BLActor.h"
#include "BLWorld.h"
#include "Vector2.h"

class GEngine;
class BLWorld;
class CanvasBase;
class ImageFlipBook;
class IBPlanner;
class BLProp;

class BLBot : public BLActor
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

		void					SetState(BotState state, BotDir dir=Down, float delay=-1.f, BLProp* pObj=NULL);
		BotState				GetState() const { return m_eState; }
					
		void					Update(float dt);
		void					Draw() const;

		BotDir					GetDir() const { return m_eDir; }
		BotDir					ComputeDir(const Vector2& Target) const;
		BotDir					ComputeDir(const Vector2& Start, const Vector2& Target) const;
		void					SetDir(BLBot::BotDir eDir);
		void					SetDir(const Vector2& vTarget);


		const IBPlanner&		GetPlanner() const { return *m_pPlanner; }
		IBPlanner&				GetPlanner() { return *m_pPlanner; }
		const BLWorld&			GetWorld() const { return m_oWorld; }
		BLWorld&				GetWorld() { return m_oWorld; }

		bool					StartAction(class BotAction* pAction);

		void					PickProp(BLProp* pProp);
		bool					HasObject(BLProp* pObj) const { return (pObj != NULL && pObj == m_pCarryObject); }
		BLProp*					GetFirstObject() const { return m_pCarryObject; }
		void					DropObject(BLProp* pProp, const Vector2& pos);

		void					AddGoal(const class BLGoal& oGoal);
		
		void					AddGoal(const string& name);
		void					AddGoal(const string& name, IBObject* pUserData);
		void					AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2);
		void					AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3);

	private:
		BLWorld&				m_oWorld;

		ImageFlipBook*			m_pIdleImage;
		ImageFlipBook*			m_pWalkImage;
		ImageFlipBook*			m_pWorkImage;

		float					m_fLocX; // pixel
		float					m_fLocY; // pixel

		vector<BLGoal>			m_aGoals;

		BotState				m_eState;
		BotDir 					m_eDir;

		class BotAction*		m_pCurrentAction;
		class BotAction*		m_pPendingAction;

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
