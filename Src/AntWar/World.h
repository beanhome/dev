#ifndef WORLD_H
#define WORLD_H

#include "Utils.h"
#include "Vector2.h"
#include "Grid.h"

//
//const int DIRECTIONS[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };      //{N, E, S, W}

enum EDirection
{
	North,
	Est,
	South,
	West,

	EDirection_MAX
};

const char cDirChar[4] = {'N', 'E', 'S', 'W'};
extern Vector2 vMove[4];// = { Vector2(0, -1), Vector2(1, 0), Vector2(0, 1), Vector2(-1, 0)};

class World
{
	public:
		World();
		~World();

		void ReadSetup();
		void ReadTurn();

		void DrawDebug();

		//void setup();
		
		void Reset();

		//void makeMove(const Vector2 &loc, int direction);

		float Distance(const Vector2 &loc1, const Vector2 &loc2);
		Vector2 GetLocation(const Vector2 &startLoc, EDirection direction);

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

		//std::vector<Vector2> myAnts, enemyAnts, myHills, enemyHills, food;

		//Timer timer;
};


#endif //WORLD_H
