#include "AntWar.h"
#include "Utils.h"

#include "NavDijkstra.h"
#include "NavAStar.h"

#ifdef MYDEBUG
#include "Graphic.h"

GraphicEngine ge(1024, 748, 32);
GraphicFrame gf_pw(&ge, 0, 0, 748, 748);
GraphicFrame gf_dbg(&ge, 748, 0, 276, 748);

#endif


//constructor
AntWar::AntWar()
	: m_oWorld()
{
}

//plays a single game of Ants.
void AntWar::PlayGame()
{
	m_oWorld.ReadSetup();

    EndTurn();

#ifdef MYDEBUG
	ge.Init();
#endif

	int iRound = 1;

	while(true)
	{
		uint16 iNewRound = iRound;

#ifdef MYDEBUG
		if (g_bVisualDebug)
		{
			while (iNewRound == iRound)
			{
				// Reset Data for new turn
				m_oWorld.NewTurn();

				// GetInfo
				if (m_oWorld.ReadTurn(iNewRound) == false)
				{
					iNewRound--;
					continue;
				}

				// Compute
				m_oWorld.InitData();

				iNewRound = m_oWorld.DrawLoop(false);
				if (iNewRound == (uint16)-1)
					return;

				if (iNewRound == iRound)
				{
					// Execute
					MakeMoves();

					// End Turn
					EndTurn();

					iNewRound = m_oWorld.DrawLoop(true);
					if (iNewRound == (uint16)-1)
						return;
				}

				if (iNewRound == 0)
					iNewRound = 1;
			}
			iRound = iNewRound;
		}
		else
#endif
		{
			// Reset Data for new turn
			m_oWorld.NewTurn();

			// GetInfo
			if (m_oWorld.ReadTurn() == false)
				break;
			
			// Compute
			m_oWorld.InitData();

			// Execute
			MakeMoves();

			// End Turn
			EndTurn();

			iRound++;
		}
	}


#ifdef MYDEBUG
	ge.Close();
#endif
};

//makes the bots moves for the turn
void AntWar::MakeMoves()
{
	NavDijkstra m_oNavDijkstra(m_oWorld.GetGrid());
	NavAStar m_oNavAStar(m_oWorld.GetGrid());

	int   iExplMin = 5;
	float fExplCoeff = 0.1f;

	int iExpl = max(iExplMin, (int)(m_oWorld.GetAntCount() * fExplCoeff));
	int iProtect = 0;//max<int>(0, min<int>(m_oWorld.GetMinDistCount(), (int)m_oWorld.GetAntCount() - iExpl));
	int iGuard = max<int>(0, m_oWorld.GetAntCount() - (iExpl + iProtect));

	vector<Vector2> aLootAnt;
	World::DistAntMap::const_reverse_iterator begin = m_oWorld.GetAntByDist().rbegin();
	World::DistAntMap::const_reverse_iterator end = m_oWorld.GetAntByDist().rend();
	World::DistAntMap::const_reverse_iterator it;

	map<Vector2, Ant*> aExploreAnt;
	map<Vector2, Ant*> aGuardAnt;
	map<Vector2, Ant*> aProtectAnt;
	int i;
	for (i=0, it=begin  ; it != m_oWorld.GetAntByDist().rend(); ++it, ++i)
	{
		Ant* pAnt = it->second;
		Vector2 loc = pAnt->GetLocation();
		
		if (i<iExpl)
			aExploreAnt.insert(pair<Vector2, Ant*>(loc, pAnt));
		
		if (i>=iExpl && i<iExpl+iGuard)
			aGuardAnt.insert(pair<Vector2, Ant*>(loc, pAnt));

		if (i<iExpl+iGuard)
			aLootAnt.push_back(pAnt->GetLocation());

		if (i>=iExpl+iGuard)
			aProtectAnt.insert(pair<Vector2, Ant*>(loc, pAnt));
	}

	vector<Vector2> aLootLoc;
	aLootLoc.reserve(m_oWorld.GetEnemyHills().size() + m_oWorld.GetFoods().size());
	for (uint i=0 ; i<m_oWorld.GetEnemyHills().size() ; ++i)
	{
		aLootLoc.push_back(m_oWorld.GetEnemyHills()[i]);
	}
	for (uint i=0 ; i<m_oWorld.GetFoods().size() ; ++i)
	{
		aLootLoc.push_back(m_oWorld.GetFoods()[i]);
	}

	if (aLootLoc.size())
	{
		m_oNavDijkstra.Explore(aLootLoc, aLootAnt, m_oWorld.GetTurn());

#ifdef MYDEBUG
		m_oNavDijkstra.PrintDebug();
#endif

		typedef map<Vector2, set<Path>> AllPathMap;
		typedef pair<Vector2, set<Path>> AllPathPair;
		AllPathMap aAllPath;
		for (uint i=0 ; i<aLootAnt.size() ; ++i)
		{
			Vector2 antloc = aLootAnt[i];
			Path oPath;
			if (m_oNavDijkstra.GetPath(antloc, oPath))
			{
				Vector2 start = oPath.GetStart();
				AllPathMap::iterator it = aAllPath.find(start);
				if (it == aAllPath.end())
				{
					pair<AllPathMap::iterator, bool> res = aAllPath.insert(AllPathPair(start, set<Path>()));
					it = res.first;
				}
				it->second.insert(oPath);
			}
		}

		for (AllPathMap::const_iterator it = aAllPath.begin() ; it != aAllPath.end() ; ++it)
		{
			const Path& oPath = *(it->second.begin());
			Ant& oAnt = m_oWorld.GetAnt(oPath.GetTarget());
			ASSERT(oAnt.GetPlayer() == 0);
			if (oAnt.GetPath().size() == 0)
				oAnt.GetPath() = oPath.GetListInverse();

			map<Vector2, Ant*>::iterator found;
			found = aExploreAnt.find(oPath.GetTarget());
			if (found != aExploreAnt.end())
				aExploreAnt.erase(found);
			found = aGuardAnt.find(oPath.GetTarget());
			if (found != aGuardAnt.end())
				aGuardAnt.erase(found);
		}
	}

	// Explore Ant
	for (map<Vector2, Ant*>::iterator it = aExploreAnt.begin() ; it != aExploreAnt.end() ; ++it)
	{
		m_oNavDijkstra.FindNearest(it->first, NavDijkstra::Undiscovered, it->second->GetPath(), m_oWorld.GetTurn());
	}

	// Guard Ant
	for (map<Vector2, Ant*>::iterator it = aGuardAnt.begin() ; it != aGuardAnt.end() ; ++it)
	{
		m_oNavDijkstra.FindNearest(it->first, NavDijkstra::Unvisible, it->second->GetPath(), m_oWorld.GetTurn());
	}

	// Protect Ant
	for (map<Vector2, Ant*>::iterator it = aProtectAnt.begin() ; it != aProtectAnt.end() ; ++it)
	{
		m_oNavDijkstra.FindNearest(it->first, m_oWorld.GetBestDistCase(), it->second->GetPath(), m_oWorld.GetTurn());
	}

	// move
	for (it=begin, i=0 ; it != m_oWorld.GetAntByDist().rend(); ++it, ++i)
	{
		Ant* pAnt = it->second;
		if (pAnt->GetPath().size() > 0)
		{
			EDirection dir;
			Vector2 target = pAnt->GetPath()[0];
			if (m_oWorld.IsEmpty(target))
			{
				dir = m_oWorld.GetDirection(pAnt->GetLocation(), target);
				ExecMove(pAnt->GetLocation(), dir);
			}
		}
	}
};

void AntWar::ExecMove(const Vector2 &loc, EDirection direction)
{
	cout << "o " << loc.y << " " << loc.x << " " << cDirChar[direction] << endl;

	m_oWorld.ExecMove(loc, direction);
}

void AntWar::EndTurn()
{
	//if(m_oWorld.turn > 0)
	//    m_oWorld.reset();
	//m_oWorld.turn++;

	cout << "go" << endl;
}
