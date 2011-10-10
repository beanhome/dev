#ifndef WORLD_H
#define WORLD_H

#include "Utils.h"
#include "Vector2.h"
#include "Grid.h"

enum EDirection
{
	North,
	Est,
	South,
	West,

	EDirection_MAX
};

const char cDirChar[4] = {'N', 'E', 'S', 'W'};
extern Vector2 vMove[4];

class World
{
	public:
		World();
		~World();

		float GetViewRadius() const { return m_fViewRadius; }

		void ReadSetup();
		void ReadTurn();

		void DrawDebug();

		//void setup();
		
		void NewTurn();

		bool IsEmpty(Vector2 pos) const;
		bool IsWater(Vector2 pos) const;
		bool HasAnt(Vector2 pos) const;

		const vector<Vector2>& GetFriendAnts() const { return m_aFriendAnts; }
		const vector<Vector2>& GetFoods() const { return m_aFoods; }

		void ExecMove(const Vector2 &loc, EDirection direction);

		float Distance(const Vector2 &loc1, const Vector2 &loc2);
		Vector2 GetLocation(const Vector2 &startLoc, EDirection direction);
		EDirection GetDirection(const Vector2 &startLoc, const Vector2 &targetLoc);

	    void UpdateVisionInformation();


	private:
		uint	m_iWidth;
		uint	m_iHeight;

		uint	m_iLoadTime;
		uint	m_iTurnTime;

		uint	m_iTurn;
		uint	m_iMaxTurn;
		uint	m_iPlayerCount;
		
		float	m_fAttackRadius;
		float	m_fSpawnRadius;
		float	m_fViewRadius;

		uint	m_iSeed;

		/*
		std::vector<float> scores;
		bool gameover;
		*/

		FILE*	m_pInput;
		FILE*	m_pInputSave;

		Grid	m_oGrid;

		vector<Vector2> m_aFriendAnts;
		vector<Vector2> m_aEnemyAnts;
		vector<Vector2> m_aFriendHills;
		vector<Vector2> m_aEnemyHills;
		vector<Vector2> m_aFoods;

		//Timer timer;
};


#endif //WORLD_H
