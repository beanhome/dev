#include "AntWar.h"

using namespace std;




//constructor
AntWar::AntWar()
{

};

//plays a single game of Ants.
void AntWar::playGame()
{
	m_oWorld.ReadSetup();

    EndTurn();

    //continues making moves while the game is not over
    while(true)
    {
		m_oWorld.Reset();
		m_oWorld.ReadTurn();
		m_oWorld.DrawDebug();
        m_oWorld.UpdateVisionInformation();
        MakeMoves();
        EndTurn();
    }
};

//makes the bots moves for the turn
void AntWar::MakeMoves()
{
    //picks out moves for each ant

	/*
    for(int ant=0; ant<(int)m_oWorld.myAnts.size(); ant++)
    {
        for(int d=0; d<TDIRECTIONS; d++)
        {
            Vector2 loc = m_oWorld.getLocation(m_oWorld.myAnts[ant], d);

            if(!m_oWorld.grid[loc.x][loc.y].isWater)
            {
                m_oWorld.makeMove(m_oWorld.myAnts[ant], d);
                break;
            }
        }
    }
	*/

};

//finishes the turn
void AntWar::EndTurn()
{
    //if(m_oWorld.turn > 0)
    //    m_oWorld.reset();
    //m_oWorld.turn++;

    cout << "go" << endl;
};
