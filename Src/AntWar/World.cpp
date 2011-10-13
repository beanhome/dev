#include "World.h"
#include <math.h>
#include "Square.h"
#include "Utils.h"
#include "StringUtils.h"

#ifdef MYDEBUG
#include "Graphic.h"
#endif

Vector2 vMove[4] = { Vector2(0, -1), Vector2(1, 0), Vector2(0, 1), Vector2(-1, 0)};

World::World()
#ifdef MYDEBUG
	: m_bKeyDown(false)
	, m_fKeyDownTime(0.f)
	, m_fRepeatDelay(0.f)
	, m_fFirstRepeatDelay(500.f)
	, m_fNextRepeatDelay(30.f)
#endif

{
    //gameover = 0;
    m_iTurn = 0;

#ifdef MYDEBUG
	if (g_bVisualDebug)
	{
		fopen_s(&m_pInput, "Input.txt", "rt");
		ASSERT(m_pInput != NULL);
		rewind(m_pInput);
		m_pInputSave = NULL;
	}
	else
#endif
	{
		m_pInput = stdin;
		fopen_s(&m_pInputSave, "Input.txt", "wt");
	}

	m_oTimer.Start();
}

World::~World()
{
}

void World::NewTurn()
{
	m_oGrid.NewTurn();

	m_aAnts.clear();
	m_aFriendHills.clear();
	m_aEnemyHills.clear();
	m_aFoods.clear();
}

bool World::IsEmpty(Vector2 pos) const
{
	return !m_oGrid[pos.x][pos.y].IsWater() && !m_oGrid[pos.x][pos.y].HasAnt();
}


bool World::IsWater(Vector2 pos) const
{
	return m_oGrid[pos.x][pos.y].IsWater();
}

bool World::HasAnt(Vector2 pos) const
{
	return m_oGrid[pos.x][pos.y].HasAnt();
}


void World::ExecMove(const Vector2 &loc, EDirection direction)
{
    Vector2 nLoc = GetLocation(loc, direction);
    m_oGrid[nLoc.x][nLoc.y].SetAntPlayer(m_oGrid[loc.x][loc.y].GetAntPlayer());
    m_oGrid[loc.x][loc.y].SetAntPlayer(-1);
};

//returns the euclidean distance between two locations with the edges wrapped
float World::Distance(const Vector2 &loc1, const Vector2 &loc2)
{
    uint d1 = abs(loc1.x-loc2.x);
    uint d2 = abs(loc1.y-loc2.y);
    int dr = min(d1, m_iWidth-d1);
    int dc = min(d2, m_iHeight-d2);
    return sqrt((float)dr*dr + (float)dc*dc);
};

int World::DistanceSq(const Vector2 &loc1, const Vector2 &loc2)
{
	uint d1 = abs(loc1.x-loc2.x);
	uint d2 = abs(loc1.y-loc2.y);
	int dr = min(d1, m_iWidth-d1);
	int dc = min(d2, m_iHeight-d2);
	return (dr*dr + dc*dc);
}


//returns the new location from moving in a given direction with the edges wrapped
Vector2 World::GetLocation(const Vector2 &loc, EDirection dir)
{
    return Vector2( (loc.x + vMove[dir].x + m_iWidth) % m_iWidth,
                     (loc.y + vMove[dir].y + m_iHeight) % m_iHeight );
};

EDirection World::GetDirection(const Vector2 &startLoc, const Vector2 &targetLoc)
{
	int iHori = targetLoc.x - startLoc.x;
	int iVert = targetLoc.y - startLoc.y;

	if (iHori > (int)m_iWidth / 2)
		iHori -= m_iWidth;

	if (iVert > (int)m_iHeight / 2)
		iVert -= m_iHeight;

	if (abs(iHori) > abs(iVert))
	{
		return (iHori > 0 ? Est : West);
	}
	else
	{
		return (iVert > 0 ? South : North);
	}
}

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
			m_iViewRadiusSq = val;
		else if (strncmp(lines[i].c_str(), "attackradius2", pos) == 0)
			m_fAttackRadius = (float)val;
		else if (strncmp(lines[i].c_str(), "spawnradius2", pos) == 0)
			m_fSpawnRadius = (float)val;
		else if (strncmp(lines[i].c_str(), "player_seed", pos) == 0)
			m_iSeed = val;
	}

	m_oGrid.Init(m_iWidth, m_iHeight);

	/*
	for (uint i=0 ; i<m_oGrid.GetSize() ; ++i)
	{
		Vector2 vCoord = m_oGrid.GetCoord(i);
		ASSERT(m_oGrid.GetIndex(vCoord) == i);
	}

	for (uint i=0 ; i<m_oGrid.GetWidth() ; ++i)
	{
		for (uint j=0 ; j<m_oGrid.GetHeight() ; ++j)
		{
			uint id = m_oGrid.GetIndex(i, j);
			ASSERT(m_oGrid.GetCoord(id) == Vector2(i, j));
		}
	}
	*/
}

bool World::ReadTurn(int iRound)
{
	if (iRound > 0)
	{
		if (iRound-1 == m_aTurnInputFileLoc.size())
		{
			m_aTurnInputFileLoc.push_back(ftell(m_pInput));
		}
		else
		{
			fseek(m_pInput, m_aTurnInputFileLoc[iRound-1], SEEK_SET);
		}
	}

	string map_data;
	if (ReadData(m_pInput, map_data) == 1)
		return false;

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

		if (strncmp(lines[i].c_str(), "turn", 4) == 0)
		{
			m_iTurn = atoi(line + 4);
		}

		char* pLastChar;

		int y = strtol(line+2, &pLastChar, 10);
		int x = strtol(pLastChar, &pLastChar, 10);

		m_oGrid[x][y].Init(line, pLastChar, iRound);

		switch (m_oGrid[x][y].GetAntPlayer())
		{
			case -1:	break;
			default:	m_aAnts.push_back(Ant(x, y, m_oGrid[x][y].GetAntPlayer()));
		}

		switch (m_oGrid[x][y].GetHillPlayer())
		{
			case -1:	break;
			case 0:		m_aFriendHills.push_back(Vector2(x, y)); break;
			default:	m_aEnemyHills.push_back(Vector2(x, y));
		}

		if (m_oGrid[x][y].IsFood())
			m_aFoods.push_back(Vector2(x, y));

		if (m_oGrid[x][y].HasFriendAnt())
		{
			for (int lx = -m_iViewRadiusSq ; lx < m_iViewRadiusSq+1 ; ++lx)
			{
				for (int ly = -m_iViewRadiusSq ; ly < m_iViewRadiusSq+1 ; ++ly)
				{
					if (DistanceSq(Vector2(x, y), Vector2(x+lx, y+ly)) <= m_iViewRadiusSq)
					{
						m_oGrid[x+lx][y+ly].SetVisible(true);
						m_oGrid[x+lx][y+ly].SetDiscovered(m_iTurn);
					}
				}
			}
		}
	}

	ASSERT(iRound == -1 || m_iTurn == iRound);

	return true;
}

#ifdef MYDEBUG
int World::DrawLoop(bool bPostCompute)
{
	bool bContinue = false;
	uint16 iRound = m_iTurn;

	while(!bContinue)
	{
		const InputEvent& oInputEvent = ge.PollEvent();

		if (oInputEvent.IsQuit())
			return (uint16)-1;

		if (oInputEvent.IsKeyboard())
		{
			if (oInputEvent.GetKeyboardEvent() == KeyUp)
			{
				m_bKeyDown = false;
			}
			else
			{
				if (!m_bKeyDown)
				{
					m_fKeyDownTime = m_oTimer.GetTime();
					m_fRepeatDelay = m_fFirstRepeatDelay;
				}
				else
				{
					if (m_oTimer.GetTime() > m_fKeyDownTime + m_fRepeatDelay)
					{
						m_bKeyDown = false;
						m_fKeyDownTime = m_oTimer.GetTime();
						m_fRepeatDelay = m_fNextRepeatDelay;
					}
				}

				if (!m_bKeyDown)
				{
					switch(oInputEvent.GetKeyboardKey())
					{
					case KEY_LEFT:
						if (iRound > 0)
						{
							bContinue = true;
							iRound--;
						}
						break;

					case KEY_RIGHT:
						bContinue = true;
						iRound++;
						break;

					case KEY_SPACE:
						bContinue = true;
						break;
					}
				}

				m_bKeyDown = true;
			}
		}

		int i = -1;
		int j = -1;

		if (oInputEvent.IsMouse())
		{
			uint16 x, y;
			oInputEvent.GetMouseMove(x, y);

			i = x * m_oGrid.GetWidth() / gf_pw.GetWidth();
			j = y * m_oGrid.GetHeight() / gf_pw.GetHeight();

			if (i < 0 || i > (int)m_oGrid.GetWidth())
				i = -1;

			if (j < 0 || j > (int)m_oGrid.GetHeight())
				j = -1;
		}

		Draw(bPostCompute, i, j);
	}

	return iRound;}

void World::Draw(bool bPostCompute, int i, int j) const
{
	ge.Clear();

	m_oGrid.Draw(m_iTurn, i, j);

	uint iAntSelected = (uint)-1;
	for (uint k=0 ; k<m_aAnts.size() ; ++k)
	{
		const Ant& oAnt = m_aAnts[k];
		if (Vector2(i,j) == oAnt.GetLocation())
		{
			iAntSelected = k;
		}
		else
		{
			oAnt.Draw(oAnt.GetLocation().x, oAnt.GetLocation().y, m_oGrid.GetWidth(), m_oGrid.GetHeight(), m_iTurn, false);
		}
	}

	if (iAntSelected != (uint)-1)
	{
		const Ant& oAnt = m_aAnts[iAntSelected];
		oAnt.Draw(oAnt.GetLocation().x, oAnt.GetLocation().y, m_oGrid.GetWidth(), m_oGrid.GetHeight(), m_iTurn, true);
	}

	// Text
	gf_pw.Print((sint16)gf_pw.GetWidth() / 2, 10, 16, Center, 0, 0, 0, "Turn %d %s", m_iTurn, (bPostCompute ? "After Computing" : ""));

	sint16 x = 10;
	sint16 y = 10;
	sint16 yl = 10;

	if (i != -1 && j != -1)
	{
		gf_dbg.Print(x, y, yl, LeftTop, 0, 0, 0, "Square %d %d", i, j);
		y += yl;
		m_oGrid[i][j].PrintInfo(x, y, yl, m_iTurn);
	}

	if (iAntSelected != (uint)-1)
	{
		const Ant& oAnt = m_aAnts[iAntSelected];
		oAnt.PrintInfo(x, y, yl);
	}

	ge.Flip();
}
#endif

void World::DrawDebug() const
{
	for (uint y=0 ; y<m_iHeight ; ++y)
	{
		for (uint x=0 ; x<m_iWidth ; ++x)
		{
			char c = '?';

			if (m_oGrid[x][y].IsVisible())
			{
				if (m_oGrid[x][y].IsWater())
					c = '%';
				else if (m_oGrid[x][y].IsFood())
					c = '*';
				else if (m_oGrid[x][y].IsHill() && m_oGrid[x][y].HasAnt() == false)
					c = '0' + m_oGrid[x][y].GetHillPlayer();
				else if (m_oGrid[x][y].IsHill() && m_oGrid[x][y].HasAnt())
					c = 'A' + m_oGrid[x][y].GetHillPlayer();
				else if (m_oGrid[x][y].HasAnt())
					c = 'a' + m_oGrid[x][y].GetAntPlayer();
				else if (m_oGrid[x][y].HasDeadAnt())
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