#include "Utils.h"

bool g_bVisualOutput = false;

#ifdef _WIN32
FILE* myfopen(const char *p, const char *m) { FILE* f; fopen_s(&f, p, m); return f; }
#endif

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

	#ifdef _WIN32
	_vsprintf_s_l(output, 1024, format, NULL, arglist);
	#else
	vsnprintf(output, 1024, format, arglist);
	#endif
	
	#ifdef _WIN32
	if (g_bVisualOutput)
		OutputDebugStringA(output);
	else
	#endif
		printf("%s", output);
}

string FormatString(const char* format, ...)
{
	va_list arglist;
	va_start(arglist, format);

#ifdef _WIN32
	int nb = _vscprintf(format, arglist);
#else
	int nb = vsnprintf(NULL, 0, format, arglist);
#endif

	char* buff = new char[nb+2];


#ifdef _WIN32
	_vsprintf_s_l(buff, nb+1, format, NULL, arglist);
#else
	vsnprintf(buff, nb+1, format, arglist);
#endif



	string output(buff);

	free(buff);

	return output;
}


int Rand()
{
	return rand();
}

int Rand(int iMax)
{
	return rand() % (iMax+1);
}

int Rand(int iMin, int iMax)
{
	return Rand(iMax-iMin) + iMin;
}

float Lerp(float a, float b, float t)
{
	return a + (b-a)*t;
}
