#ifndef WORLD_H
#define WORLD_H

#include "Utils.h"
#include "Vector2.h"
#include "Grid.h"
#include "Timer.h"
#include "Ant.h"
#include "NavDijkstra.h"
#include "Hill.h"


const char cDirChar[CardDirCount] = {'N', 'E', 'S', 'W'};
extern Vector2 vMove[EDirection_MAX];

class World
{
	public:
		World();
		~World();

	public:
		typedef multimap<int, Ant*> DistAntMap;
		typedef pair<int, Ant*> DistAntPair;

	public:
		int GetViewRadiusSq() const { return m_iViewRadiusSq; }

		void ReadSetup();
		bool ReadTurn(int iRound = -1);

		void PrintDebug() const;
		void PrintInfluence() const;
#ifdef MYDEBUG
		void Draw(bool bPostCompute, int i, int j, DrawMode mode) const;
		int DrawLoop(bool bPostCompute);
#endif

		const Grid& GetGrid() const { return m_oGrid; }
		uint GetTurn() const { return m_iTurn; }

		//void setup();
		
		void NewTurn();

		bool IsEmpty(Vector2 pos) const;
		bool IsWater(Vector2 pos) const;
		bool HasAnt(Vector2 pos) const;

		uint GetAntCount() const { return m_aDistAnts.size(); }

		const vector<Ant>& GetAnts() const { return m_aAnts; }
		vector<Ant>& GetAnts() { return m_aAnts; }
		const Ant& GetAnt(uint i) const { ASSERT(i<m_aAnts.size()); return m_aAnts[i]; }
		Ant& GetAnt(uint i) { ASSERT(i<m_aAnts.size()); return m_aAnts[i]; }
		const Ant& GetAnt(Vector2 pos) const { for (uint i=0 ; i<m_aAnts.size() ; ++i) if (m_aAnts[i].GetLocation() == pos) return m_aAnts[i]; }
		Ant& GetAnt(Vector2 pos) { for (uint i=0 ; i<m_aAnts.size() ; ++i) if (m_aAnts[i].GetLocation() == pos) return m_aAnts[i]; ASSERT(false); return m_aAnts[0]; }

		void GetFriendAnt(vector<Vector2>& aAnts) const;
		void GetEnemyAnt(vector<Vector2>& aAnts) const;

		const DistAntMap& GetAntByDist() const { return m_aDistAnts; }
		//uint GetMinDistCount() const { return m_iMinDistCount; }

		//vector<Vector2> GetBestDistCase() const;

		const Hill* GetHill(Vector2 pos) const { for (uint i=0 ; i<m_aHills.size() ; ++i) if (m_aHills[i]->GetLocation() == pos) return m_aHills[i]; return NULL; }
		Hill* GetHill(Vector2 pos) { for (uint i=0 ; i<m_aHills.size() ; ++i) if (m_aHills[i]->GetLocation() == pos) return m_aHills[i]; return NULL; }

		const vector<Vector2>& GetFoods() const { return m_aFoods; }
		
		vector<Vector2> GetFriendHills() const;
		vector<Vector2> GetEnemyHills() const;

		void ExecMove(const Vector2 &loc, EDirection direction);

		float Distance(const Vector2 &loc1, const Vector2 &loc2) const;
		int DistanceSq(const Vector2 &loc1, const Vector2 &loc2) const;
		Vector2 GetLocation(const Vector2 &startLoc, EDirection direction);
		EDirection GetDirection(const Vector2 &startLoc, const Vector2 &targetLoc);

	    void InitData();


	private:
		uint				m_iWidth;
		uint				m_iHeight;

		uint				m_iLoadTime;
		uint				m_iTurnTime;

		uint				m_iTurn;
		uint				m_iMaxTurn;
		uint				m_iPlayerCount;
		
		int					m_iAttackRadiusSq;
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

		vector<Ant>			m_aAnts;
		vector<Hill*>		m_aHills;
		vector<Vector2>		m_aFoods;

		NavDijkstra			m_oHillsDist;
		DistAntMap			m_aDistAnts;

#ifdef MYDEBUG
		bool				m_bKeyDown;
		float				m_fKeyDownTime;
		float				m_fRepeatDelay;
		float				m_fFirstRepeatDelay;
		float				m_fNextRepeatDelay;
#endif
		DrawMode			m_eDrawMode;

		Timer				m_oTimer;
};


#endif //WORLD_H
