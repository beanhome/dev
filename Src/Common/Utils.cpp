#include "Utils.h"

#include <stdio.h>
#include <stdlib.h>

#include <wtypes.h>
#include <basetsd.h>
#include <winbase.h>

bool g_bVisualOutput = false;

void InitLog(int argc, char *argv[])
{
	for (int i=1 ; i<argc ; ++i)
	{
		if (argv[i][0] == '-' && argv[i][1] == 'v')
			g_bVisualOutput = true;
	}
}


void Log(const char* format, ...)
{
	char output[1024];
	va_list arglist;
	va_start(arglist, format);
	_vsprintf_s_l(output, 1024, format, NULL, arglist);
	
	if (g_bVisualOutput)
		OutputDebugStringA(output);
	else
		printf("%s", output);
}

string FormatString(const char* format, ...)
{
	va_list arglist;
	va_start(arglist, format);

	int nb = _vscprintf(format, arglist);

	char* buff = new char[nb+2];

	_vsprintf_s_l(buff, nb+1, format, NULL, arglist);

	string output(buff);

	free(buff);

	return output;
}
