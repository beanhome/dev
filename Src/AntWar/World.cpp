#include "World.h"
#include <math.h>
#include "Square.h"
#include "Utils.h"
#include "StringUtils.h"
#include "Hill.h"
#include "NavDijkstra.h"

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
		MYFOPEN(m_pInput, "Input.txt", "rt");
		ASSERT(m_pInput != NULL);
		rewind(m_pInput);
		m_pInputSave = NULL;
	}
	else
#endif
	{
		m_pInput = stdin;
		MYFOPEN(m_pInputSave, "Input.txt", "wt");
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
	m_aFoods.clear();

	for (uint i=0 ; i<m_aHills.size() ; ++i)
	{
		m_aHills[i].Reset();
	}
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

vector<Vector2> World::GetFriendHills() const
{
	vector<Vector2> aLoc;

	for (uint i=0 ; i<m_aHills.size() ; ++i)
		if (m_aHills[i].GetPlayer() == 0)
			aLoc.push_back(m_aHills[i].GetLocation());

	return aLoc;
}

vector<Vector2> World::GetEnemyHills() const
{
	vector<Vector2> aLoc;

	for (uint i=0 ; i<m_aHills.size() ; ++i)
		if (m_aHills[i].GetPlayer() > 0)
			aLoc.push_back(m_aHills[i].GetLocation());

	return aLoc;
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

	if (iHori < -((int)m_iWidth) / 2)
		iHori += m_iWidth;

	if (iVert > (int)m_iHeight / 2)
		iVert -= m_iHeight;

	if (iVert < -((int)m_iHeight) / 2)
		iVert += m_iHeight;

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
		fflush(m_pInputSave);
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
		fflush(m_pInputSave);
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

		if (strncmp(lines[i].c_str(), "end", 3) == 0)
		{
			return false;
		}

		if (strncmp(lines[i].c_str(), "turn", 4) == 0)
		{
			m_iTurn = atoi(line + 4);
		}

		char* pLastChar;

		int y = strtol(line+2, &pLastChar, 10);
		int x = strtol(pLastChar, &pLastChar, 10);

		m_oGrid[x][y].Init(line, pLastChar, iRound);

		// Ant line
		int iAntPlayer = m_oGrid[x][y].GetAntPlayer();
		if (iAntPlayer > -1)
		{
			//Ant& oAnt = GetAnt(Vector2(x, y));
			m_aAnts.push_back(Ant(x, y, iAntPlayer));
		}

		int iHillPlayer = m_oGrid[x][y].GetHillPlayer();
		if (iHillPlayer > -1)
		{
			Hill* pHill = GetHill(Vector2(x, y));
			if (pHill != NULL)
			{
				pHill->SetPlayer(iHillPlayer);
				pHill->SetUpdated();
			}
			else
			{
				m_aHills.push_back(Hill(Vector2(x, y), iHillPlayer));
			}
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

		for (uint k=0 ; k<m_aHills.size() ; ++k)
		{
			Hill& oHill = m_aHills[k];
			if (m_oGrid.GetCase(oHill.GetLocation()).IsVisible() && oHill.IsNotUpdated())
				oHill.SetPlayer(-1);
		}
	}

	ASSERT(iRound == -1 || m_iTurn == iRound);

	return true;
}

void World::InitData()
{
	m_oHillsDist.Init(GetGrid());
	m_oHillsDist.Explore(GetFriendHills(), GetTurn());
	m_oHillsDist.PrintDebug();

	m_aDistCount.clear();
	m_aDistCount.reserve(m_oHillsDist.GetGrid().GetWidth() + m_oHillsDist.GetGrid().GetHeight());
	for (uint x=0 ; x<m_oHillsDist.GetGrid().GetWidth() ; ++x)
	{
		for (uint y=0 ; y<m_oHillsDist.GetGrid().GetHeight() ; ++y)
		{
			int iCount = m_oHillsDist.GetGrid()[x][y].iCount;
			if (iCount >= 0)
			{
				if (iCount >= (int)m_aDistCount.size())
					m_aDistCount.resize(iCount+1);

				m_aDistCount[iCount].push_back(Vector2(x,y));
			}
		}
	}

	m_iMinDistCount = (uint)-1;
	for (uint i=5 ; i<m_aDistCount.size() ; ++i)
	{
		if (m_iMinDistCount == -1 || m_iMinDistCount < m_aDistCount[m_iMinDistId].size())
		{
			m_iMinDistId = i;
			m_iMinDistCount = m_aDistCount[m_iMinDistId].size();
		}
	}

	m_aDistAnts.clear();
	for (uint i=0 ; i<m_aAnts.size() ; ++i)
	{
		if (m_aAnts[i].GetPlayer() == 0)
		{
			const NavDijkstra::Case& oCase = m_oHillsDist.GetGrid().GetCase(m_aAnts[i].GetLocation());
			m_aDistAnts.insert(DistAntPair(oCase.iCount, &m_aAnts[i]));
		}
	}
}

vector<Vector2> World::GetBestDistCase() const
{
	vector<Vector2> loc;

	for (uint i=0 ; i<m_aDistCount[m_iMinDistId].size() ; ++i)
	{
		Vector2 coord = m_aDistCount[m_iMinDistId][i];

		if (m_oGrid.GetCase(coord).HasAnt() == false)
			loc.push_back(coord);
	}

	return loc;
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

	for (uint k=0 ; k<m_aHills.size() ; ++k)
	{
		const Hill& oHill = m_aHills[k];
		oHill.Draw(oHill.GetLocation().x, oHill.GetLocation().y, m_oGrid.GetWidth(), m_oGrid.GetHeight(), m_iTurn, false);
	}

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


