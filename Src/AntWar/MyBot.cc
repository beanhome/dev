#include "Utils.h"
#include "AntWar.h"

#ifdef MYDEBUG
bool  g_bVisualDebug = false;
#endif
#ifdef USE_LOG
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
		MYFOPEN(g_MyLog, "MyLog.txt", "wt");
	}
#else
#ifdef USE_LOG
	MYFOPEN(g_MyLog, "MyLog.txt", "wt");
#endif
#endif

    AntWar aw;
    aw.PlayGame();

    return 0;
}


