#ifndef WORLD_H
#define WORLD_H

#include "Utils.h"
#include "Vector2.h"
#include "Grid.h"
#include "Timer.h"
#include "Ant.h"


const char cDirChar[EDirection_MAX] = {'N', 'E', 'S', 'W'};
extern Vector2 vMove[EDirection_MAX];

class World
{
	public:
		World();
		~World();

		int GetViewRadiusSq() const { return m_iViewRadiusSq; }

		void ReadSetup();
		bool ReadTurn(int iRound = -1);

		void DrawDebug() const;
#ifdef MYDEBUG
		void Draw(bool bPostCompute, int i, int j) const;
		int DrawLoop(bool bPostCompute);
#endif

		const Grid& GetGrid() const { return m_oGrid; }
		uint GetTurn() const { return m_iTurn; }

		//void setup();
		
		void NewTurn();

		bool IsEmpty(Vector2 pos) const;
		bool IsWater(Vector2 pos) const;
		bool HasAnt(Vector2 pos) const;

		const vector<Ant>& GetFriendAnts() const { return m_aFriendAnts; }
		const vector<Vector2>& GetFoods() const { return m_aFoods; }

		void ExecMove(const Vector2 &loc, EDirection direction);

		float Distance(const Vector2 &loc1, const Vector2 &loc2);
		int DistanceSq(const Vector2 &loc1, const Vector2 &loc2);
		Vector2 GetLocation(const Vector2 &startLoc, EDirection direction);
		EDirection GetDirection(const Vector2 &startLoc, const Vector2 &targetLoc);

	    void UpdateVisionInformation();


	private:
		uint				m_iWidth;
		uint				m_iHeight;

		uint				m_iLoadTime;
		uint				m_iTurnTime;

		uint				m_iTurn;
		uint				m_iMaxTurn;
		uint				m_iPlayerCount;
		
		float				m_fAttackRadius;
		float				m_fSpawnRadius;
		int					m_iViewRadiusSq;

		uint				m_iSeed;

		/*
		std::vector<float> scores;
		bool gameover;
		*/

		FILE*				m_pInput;
		vector<uint32>		m_aTurnInputFileLoc;

		FILE*				m_pInputSave;

		Grid				m_oGrid;

		vector<Ant>			m_aFriendAnts;
		vector<Ant>			m_aEnemyAnts;
		vector<Vector2>		m_aFriendHills;
		vector<Vector2>		m_aEnemyHills;
		vector<Vector2>		m_aFoods;

#ifdef MYDEBUG
		bool m_bKeyDown;
		float m_fKeyDownTime;
		float m_fRepeatDelay;
		float m_fFirstRepeatDelay;
		float m_fNextRepeatDelay;
#endif

		Timer m_oTimer;
};


#endif //WORLD_H
