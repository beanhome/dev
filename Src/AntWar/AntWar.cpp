#include "AntWar.h"

using namespace std;




//constructor
AntWar::AntWar()
{

};

//plays a single game of Ants.
void AntWar::PlayGame()
{
	m_oWorld.ReadSetup();

    EndTurn();

    //continues making moves while the game is not over
    while(true)
    {
		m_oWorld.NewTurn();
		m_oWorld.ReadTurn();
		//m_oWorld.DrawDebug();
        m_oWorld.UpdateVisionInformation();
        MakeMoves();
        EndTurn();
    }
};

//makes the bots moves for the turn
void AntWar::MakeMoves()
{
	for (uint i=0 ; i<m_oWorld.GetFriendAnts().size() ; ++i)
	{
		EDirection dir = EDirection_MAX;

		const Vector2& pos = m_oWorld.GetFriendAnts()[i];

		if (dir == EDirection_MAX)
		{
			for (uint j=0 ; j<m_oWorld.GetFoods().size() ; ++j)
			{
				const Vector2& vFoodLoc = m_oWorld.GetFoods()[j];

				float fDist = m_oWorld.Distance(pos, vFoodLoc);

				if (fDist * fDist < m_oWorld.GetViewRadius())
				{
					dir = m_oWorld.GetDirection(pos, vFoodLoc);
					Vector2 target = m_oWorld.GetLocation(pos, dir);
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
					ExecMove(pos, ndir);
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
