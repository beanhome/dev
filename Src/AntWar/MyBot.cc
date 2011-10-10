#include "Utils.h"
#include "AntWar.h"

#ifdef MYDEBUG
bool  g_bVisualDebug = false;
FILE* g_MyLog = NULL;
#endif

int main(int argc, char *argv[])
{
    cout.sync_with_stdio(0); //this line makes your bot faster

#ifdef MYDEBUG
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
#endif

    AntWar aw;
    aw.PlayGame();

    return 0;
}


