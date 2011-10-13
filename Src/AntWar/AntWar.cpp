#include "AntWar.h"
#include "Utils.h"

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
				m_oWorld.UpdateVisionInformation();

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
			m_oWorld.UpdateVisionInformation();

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
	Navigation m_oNavigation(m_oWorld.GetGrid());

	for (uint i=0 ; i<m_oWorld.GetAnts().size() ; ++i)
	{
		Ant& oAnt = m_oWorld.GetAnts()[i];		
		if (oAnt.GetPlayer() != 0)
			continue;

		const Vector2& pos = oAnt.GetLocation();
		oAnt.GetPath().clear();

		EDirection dir = EDirection_MAX;

		if (dir == EDirection_MAX)
		{
			for (uint j=0 ; j<m_oWorld.GetEnemyHills().size() ; ++j)
			{
				const Vector2& vHillLoc = m_oWorld.GetEnemyHills()[j];

				if (m_oWorld.DistanceSq(pos, vHillLoc) < m_oWorld.GetViewRadiusSq())
				{
					if (m_oNavigation.FindPath(pos, vHillLoc, oAnt.GetPath(), m_oWorld.GetTurn()))
					{
						dir = m_oWorld.GetDirection(pos, oAnt.GetPath()[0]);
					}
					break;
				}
			}
		}

		if (dir == EDirection_MAX)
		{
			for (uint j=0 ; j<m_oWorld.GetFoods().size() ; ++j)
			{
				const Vector2& vFoodLoc = m_oWorld.GetFoods()[j];

				if (m_oWorld.DistanceSq(pos, vFoodLoc) < m_oWorld.GetViewRadiusSq())
				{
					if (m_oNavigation.FindPath(pos, vFoodLoc, oAnt.GetPath(), m_oWorld.GetTurn()))
					{
						dir = m_oWorld.GetDirection(pos, oAnt.GetPath()[0]);
					}
					break;
				}
			}
		}

		if (dir == EDirection_MAX)
		{
			dir = (EDirection)(rand() % EDirection_MAX);
		}

		if (dir != EDirection_MAX)
		{
			for (uint k=0 ; k<(uint)EDirection_MAX ; ++k)
			{
				EDirection ndir = (EDirection)(((uint)dir+k)%(uint)EDirection_MAX);
				Vector2 target = m_oWorld.GetLocation(pos, ndir);
				if (m_oWorld.IsEmpty(target))
				{
					if (oAnt.GetPath().size() == 0)
						oAnt.GetPath().push_back(target);
					
					ExecMove(pos, ndir);
					break;
				}
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
