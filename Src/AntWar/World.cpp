#include "World.h"
#include <math.h>
#include "Square.h"

using namespace std;

Vector2 vMove[4] = { Vector2(0, -1), Vector2(1, 0), Vector2(0, 1), Vector2(-1, 0)};

World::World()
{
    //gameover = 0;
    m_iTurn = 0;

	if (g_bVisualDebug)
	{
		fopen_s(&m_pInput, "Input.txt", "rt");
		rewind(m_pInput);
		m_pInputSave = NULL;
	}
	else
	{
		m_pInput = stdin;
		fopen_s(&m_pInputSave, "Input.txt", "wt");
	}
}

World::~World()
{
}

void World::Reset()
{

}

//outputs move information to the engine
/*
void World::makeMove(const Vector2 &loc, int direction)
{
    cout << "o " << loc.row << " " << loc.col << " " << cDirChar[direction] << endl;

    Vector2 nLoc = getLocation(loc, direction);
    grid[nLoc.row][nLoc.col].ant = grid[loc.row][loc.col].ant;
    grid[loc.row][loc.col].ant = -1;
};
*/

//returns the euclidean distance between two locations with the edges wrapped
float World::Distance(const Vector2 &loc1, const Vector2 &loc2)
{
    uint d1 = abs(loc1.x-loc2.x);
    uint d2 = abs(loc1.y-loc2.y);
    int dr = min(d1, m_iWidth-d1);
    int dc = min(d2, m_iHeight-d2);
    return sqrt((float)dr*dr + (float)dc*dc);
};

//returns the new location from moving in a given direction with the edges wrapped
Vector2 World::GetLocation(const Vector2 &loc, EDirection dir)
{
    return Vector2( (loc.x + vMove[dir].x + m_iWidth) % m_iWidth,
                     (loc.y + vMove[dir].y + m_iHeight) % m_iHeight );
};

/*
    This function will update update the lastSeen value for any squares currently
    visible by one of your live ants.

    BE VERY CAREFUL IF YOU ARE GOING TO TRY AND MAKE THIS FUNCTION MORE EFFICIENT,
    THE OBVIOUS WAY OF TRYING TO IMPROVE IT BREAKS USING THE EUCLIDEAN METRIC, FOR
    A CORRECT MORE EFFICIENT IMPLEMENTATION, TAKE A LOOK AT THE GET_VISION FUNCTION
    IN ANTS.PY ON THE CONTESTS GITHUB PAGE.
*/
void World::UpdateVisionInformation()
{
	/*
    std::queue<Vector2> locQueue;
    Vector2 sLoc, cLoc, nLoc;

    for(int a=0; a<(int) myAnts.size(); a++)
    {
        sLoc = myAnts[a];
        locQueue.push(sLoc);

        std::vector<std::vector<bool> > visited(rows, std::vector<bool>(cols, false));
        grid[sLoc.row][sLoc.col].isVisible = 1;
        visited[sLoc.row][sLoc.col] = 1;

        while(!locQueue.empty())
        {
            cLoc = locQueue.front();
            locQueue.pop();

            for(int d=0; d<TDIRECTIONS; d++)
            {
                nLoc = getLocation(cLoc, d);

                if(!visited[nLoc.row][nLoc.col] && distance(sLoc, nLoc) <= viewradius)
                {
                    grid[nLoc.row][nLoc.col].isVisible = 1;
                    locQueue.push(nLoc);
                }
                visited[nLoc.row][nLoc.col] = 1;
            }
        }
    }
	*/
};

/*
    This is the output function for a state. It will add a char map
    representation of the state to the output stream passed to it.

    For example, you might call "cout << state << endl;"
*/

/*
ostream& operator<<(ostream &os, const World &state)
{
    for(int row=0; row<state.rows; row++)
    {
        for(int col=0; col<state.cols; col++)
        {
            if(state.grid[row][col].isWater)
                os << '%';
            else if(state.grid[row][col].isFood)
                os << '*';
            else if(state.grid[row][col].isHill)
                os << (char)('A' + state.grid[row][col].hillPlayer);
            else if(state.grid[row][col].ant >= 0)
                os << (char)('a' + state.grid[row][col].ant);
            else if(state.grid[row][col].isVisible)
                os << '.';
            else
                os << '?';
        }
        os << endl;
    }

    return os;
};
*/

int ReadData(FILE* pSrcFile, string& sData)
{
	sData.clear();
	while(true)
	{
		// Get Line
		string current_line;
		current_line.clear();
		int c = 0;
		do
		{
			c = fgetc(pSrcFile);
			current_line += (char)c;
		} while (c != '\n' && c != EOF);

		if (c == EOF)
			return 1;

		if (/*current_line.length() == 2 && */current_line.substr(0, 2) == "go")
			break;
		else if (/*current_line.length() == 5 && */current_line.substr(0, 5) == "ready")
			break;
		else
			sData += current_line;
	}

	return 0;
}



void World::ReadSetup()
{
	string map_data;
	ReadData(m_pInput, map_data);

	if (m_pInputSave != NULL)
	{
		fwrite(map_data.c_str(), map_data.size(), 1, m_pInputSave);
		fputs("ready\n\n", m_pInputSave);
	}

	vector<string> lines = Tokenize(map_data, "\n");

#ifdef MYDEBUG
	for (uint i=0 ; i<lines.size() ; ++i)
	{
		LOG(lines[i].c_str());
		LOG("\n");
	}
	LOG("\n");
#endif

	for (uint i=0 ; i<lines.size() ; ++i)
	{
		uint pos = lines[i].find_first_of(" ");
		int val = atoi(lines[i].c_str() + pos + 1);

		if (strncmp(lines[i].c_str(), "turn", pos) == 0)
			m_iTurn = val;
		else if (strncmp(lines[i].c_str(), "loadtime", pos) == 0)
			m_iLoadTime = val;
		else if (strncmp(lines[i].c_str(), "turntime", pos) == 0)
			m_iTurnTime = val;
		else if (strncmp(lines[i].c_str(), "rows", pos) == 0)
			m_iHeight = val;
		else if (strncmp(lines[i].c_str(), "cols", pos) == 0)
			m_iWidth = val;
		else if (strncmp(lines[i].c_str(), "turns", pos) == 0)
			m_iMaxTurn = val;
		else if (strncmp(lines[i].c_str(), "viewradius2", pos) == 0)
			m_fViewRadius = (float)val;
		else if (strncmp(lines[i].c_str(), "attackradius2", pos) == 0)
			m_fAttackRadius = (float)val;
		else if (strncmp(lines[i].c_str(), "spawnradius2", pos) == 0)
			m_fSpawnRadius = (float)val;
		else if (strncmp(lines[i].c_str(), "player_seed", pos) == 0)
			m_iSeed = val;
	}

	m_oGrid.Init(m_iWidth, m_iHeight);
}

void World::ReadTurn()
{
	string map_data;
	ReadData(m_pInput, map_data);

	if (m_pInputSave != NULL)
	{
		fwrite(map_data.c_str(), map_data.size(), 1, m_pInputSave);
		fputs("go\n\n", m_pInputSave);
	}

	vector<string> lines = Tokenize(map_data, "\n");

#ifdef MYDEBUG
	for (uint i=0 ; i<lines.size() ; ++i)
	{
		LOG(lines[i].c_str());
		LOG("\n");
	}
	LOG("\n");
#endif

	for (uint i=0 ; i<lines.size() ; ++i)
	{
		 const char* line = lines[i].c_str();
		 char* pLastChar;

		 int y = strtol(line+2, &pLastChar, 10);
		 int x = strtol(pLastChar, &pLastChar, 10);

		 switch (line[0])
		 {
			 case 'w': // water
				 m_oGrid[x][y].isVisible = true;
				 m_oGrid[x][y].isWater = true;
				 break;

			 case 'f': // food
				 m_oGrid[x][y].isVisible = true;
				 m_oGrid[x][y].isFood = true;
				 break;

			 case 'h': // hill
				 m_oGrid[x][y].isVisible = true;
				 m_oGrid[x][y].isHill = true;
				 m_oGrid[x][y].hillPlayer = strtol(pLastChar, &pLastChar, 10);
				 break;

			 case 'a': // live ant
				 m_oGrid[x][y].isVisible = true;
				 m_oGrid[x][y].ant = strtol(pLastChar, &pLastChar, 10);

				 if (m_oGrid[x][y].ant == 0)
				 {
					 int r = (int)sqrt(m_fViewRadius);
					 for (int lx = -r ; lx < r+1 ; ++lx)
					 {
						 for (int ly = -r ; ly < r+1 ; ++ly)
						 {
							 if ((int)Distance(Vector2(x, y), Vector2(x+lx, y+ly)) <= r)
								 m_oGrid[x+lx][y+ly].isVisible = true;
						 }
					 }
				 }
				 break;

			 case 'd': // dead ant
				 m_oGrid[x][y].isVisible = true;
				 m_oGrid[x][y].deadAnts.push_back(strtol(pLastChar, &pLastChar, 10));
				 break;
		 }
	}
}

void World::DrawDebug()
{
	for (uint y=0 ; y<m_iHeight ; ++y)
	{
		for (uint x=0 ; x<m_iWidth ; ++x)
		{
			char c = '?';

			if (m_oGrid[x][y].isVisible)
			{
				if (m_oGrid[x][y].isWater)
					c = '%';
				else if (m_oGrid[x][y].isFood)
					c = '*';
				else if (m_oGrid[x][y].isHill && m_oGrid[x][y].ant == -1)
					c = '0' + m_oGrid[x][y].hillPlayer;
				else if (m_oGrid[x][y].isHill && m_oGrid[x][y].ant != -1)
					c = 'A' + m_oGrid[x][y].hillPlayer;
				else if (m_oGrid[x][y].ant != -1)
					c = 'a' + m_oGrid[x][y].hillPlayer;
				else if (m_oGrid[x][y].deadAnts.size() > 0)
					c = '!';
				else
					c = '.';
			}

			LOG("%c", c);
		}
		LOG("\n");
	}
	LOG("\n");
}


#if 0

//input function
istream& operator>>(istream &is, World &state)
{
    int row, col, player;
    string inputType, junk;

    //finds out which turn it is
    while(is >> inputType)
    {
        if(inputType == "end")
        {
            state.gameover = 1;
            break;
        }
        else if(inputType == "turn")
        {
            is >> state.turn;
            break;
        }
        else //unknown line
            getline(is, junk);
    }

    if(state.turn == 0)
    {
        //reads game parameters
        while(is >> inputType)
        {
            if(inputType == "loadtime")
                is >> state.loadtime;
            else if(inputType == "turntime")
                is >> state.turntime;
            else if(inputType == "rows")
                is >> state.rows;
            else if(inputType == "cols")
                is >> state.cols;
            else if(inputType == "turns")
                is >> state.turns;
            else if(inputType == "viewradius2")
            {
                is >> state.viewradius;
                state.viewradius = sqrt(state.viewradius);
            }
            else if(inputType == "attackradius2")
            {
                is >> state.attackradius;
                state.attackradius = sqrt(state.attackradius);
            }
            else if(inputType == "spawnradius2")
            {
                is >> state.spawnradius;
                state.spawnradius = sqrt(state.spawnradius);
            }
            else if(inputType == "ready") //end of parameter input
            {
                state.timer.start();
                break;
            }
            else    //unknown line
                getline(is, junk);
        }
    }
    else
    {
        //reads information about the current turn
        while(is >> inputType)
        {
            if(inputType == "w") //water square
            {
                is >> row >> col;
                state.grid[row][col].isWater = 1;
            }
            else if(inputType == "f") //food square
            {
                is >> row >> col;
                state.grid[row][col].isFood = 1;
                state.food.push_back(Vector2(row, col));
            }
            else if(inputType == "a") //live ant square
            {
                is >> row >> col >> player;
                state.grid[row][col].ant = player;
                if(player == 0)
                    state.myAnts.push_back(Vector2(row, col));
                else
                    state.enemyAnts.push_back(Vector2(row, col));
            }
            else if(inputType == "d") //dead ant square
            {
                is >> row >> col >> player;
                state.grid[row][col].deadAnts.push_back(player);
            }
            else if(inputType == "h")
            {
                is >> row >> col >> player;
                state.grid[row][col].isHill = 1;
                state.grid[row][col].hillPlayer = player;
                if(player == 0)
                    state.myHills.push_back(Vector2(row, col));
                else
                    state.enemyHills.push_back(Vector2(row, col));

            }
            else if(inputType == "players") //player information
                is >> state.noPlayers;
            else if(inputType == "scores") //score information
            {
                state.scores = vector<float>(state.noPlayers, 0.0);
                for(int p=0; p<state.noPlayers; p++)
                    is >> state.scores[p];
            }
            else if(inputType == "go") //end of turn input
            {
                if(state.gameover)
                    is.setstate(std::ios::failbit);
                else
                    state.timer.start();
                break;
            }
            else //unknown line
                getline(is, junk);
        }
    }

    return is;
};

#endif