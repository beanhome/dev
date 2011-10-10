#include <stdio.h>

#include "Utils.h"
#include "Time.h"

#include "PlanetWars.h"

#ifdef MYDEBUG
#include "Graphic.h"
#include "Enum.h"

FILE* g_MyLog;
bool  g_bVisualDebug;
GraphicEngine ge(1024, 748, 32);
GraphicFrame gf_pw(&ge, 0, 0, 748, 748);
GraphicFrame gf_dbg(&ge, 748, 0, 276, 748);
#endif


PlanetWars pw;

extern void DoTurn(); 


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

		if (current_line.length() < 2 || current_line.substr(0, 2) != "go")
		{
			sData += current_line;
		}
		else
		{
			break;
		}
	}

	return 0;
}

#ifdef MYDEBUG

/*
void TestLoop()
{
	uint size = 5;

	uint8* tab = new uint8[size];

	for (uint i=0 ; i<size ; ++i)
	{
		for (uint j=0 ; j<size ; ++j)
			tab[j] = 0;
		while(FillID(tab, size, i))
		{
			for (uint j=0 ; j<size ; ++j)
				LOG("%d ", tab[j]);
			LOG("\n");
		}
	}

	delete [] tab;
}
*/

int main(int argc, char** argv)
{
	if (argc > 1 && strcmp(argv[1], "--visual") == 0)
	{
		g_bVisualDebug = true;
		g_MyLog = stdout;
	}
	else
	{
		g_bVisualDebug = false;
		fopen_s(&g_MyLog, "MyLog.txt", "wt");
	}

	EnumTest eTest(3);
	LOG("test : %d %s\n", (int)eTest, (const char*)eTest);

	//TestLoop();

	FILE* pInput = stdin;

	FILE* pInputSave = NULL;
	bool bInverted = false;
	if (g_bVisualDebug)
	{
		fopen_s(&pInput, "Input.txt", "rt");
		char line[16];
		fgets(line, 15, pInput);
		if (strncmp(line, "#inverted", 9) == 0)
			bInverted = true;
		rewind(pInput);
	}
	else
	{
		fopen_s(&pInputSave, "Input.txt", "wt");
	}


	vector<uint32> m_aTurnInputFileLoc;

	ge.Init();

	for(uint16 iRound = 0 ; iRound < 1001 ; )
	{
		// start turn

		//uint iPreTurnTime = GetTime();

		if (g_bVisualDebug)
		{
			if (iRound == m_aTurnInputFileLoc.size())
			{
				m_aTurnInputFileLoc.push_back(ftell(pInput));
			}
			else
			{
				fseek(pInput, m_aTurnInputFileLoc[iRound], SEEK_SET);
			}
		}

		// Get Data
		string map_data;
		if (ReadData(pInput, map_data) > 0)
		{
			if (g_bVisualDebug)
			{
				iRound--;
				continue;
			}
			else
			{
				break;
			}
		}

		if (pInputSave != NULL)
		{
			fwrite(map_data.c_str(), map_data.size(), 1, pInputSave);
			fputs("go\n", pInputSave);
			fflush(pInputSave);
		}

		uint16 iNewRound = iRound;
		if (g_bVisualDebug)
		{
			while (iNewRound == iRound)
			{
				// Create PlanetWars
				pw.NewTurn(iRound, map_data, bInverted);

				iNewRound = pw.DrawLoop(false);
				if (iNewRound == (uint16)-1)
					return 0;

				if (iNewRound == iRound)
				{
					// Compute
					DoTurn();

					iNewRound = pw.DrawLoop(true);
					if (iNewRound == (uint16)-1)
						return 0;
				}
			}
			iRound = iNewRound;
		}
		else
		{
			// Create PlanetWars
			pw.NewTurn(iRound, map_data);

			pw.Draw();
					
			// Compute
			DoTurn();

			// Execute
			pw.ExecuteOrders();

			// End Turn
			pw.FinishTurn();

			iRound++;
		}
		
		//uint iPostTurnTime = GetTime();
		//LOG("Turn Duration : %d ms\n\n", GetDelta(iPreTurnTime, iPostTurnTime));
	}

	fclose(g_MyLog);
	if (pInput != NULL)
		fclose(pInput);

	ge.Close();

	return 0;
}




#else

int main(int, char**)
{
	FILE* pInput = stdin;

	for(uint16 iRound = 0 ; iRound < 1001 ; iRound++)
	{
		// start turn

		// Get Data
		string map_data;
		if (ReadData(pInput, map_data) > 0)
		{
			break;
		}

		// Create PlanetWars
		pw.NewTurn(iRound, map_data);

		// Compute
		DoTurn();

		// Execute
		pw.ExecuteOrders();

		// End Turn
		pw.FinishTurn();
	}

	return 0;
}

#endif
