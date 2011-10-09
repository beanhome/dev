
#include "Date.h"
#include "Utils.h"

int main(int argc, char** argv)
{
	bool bTest = false;
	int iNumber = 0;
	int iString = 0;

	for (int i=1 ; i<argc ; ++i)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 'v':	g_bVisualOutput = true;		break;
			case 't':	bTest = true;				break;
			case 'd':	iNumber = i+1;				break;
			case 's':	iString = i+1;				break;
			}
		}
	}

	if (!bTest && iNumber == 0 && iString == 0)
	{
		Date::PrintYear();
	}

	if (bTest)
	{
		Date::PrintYear();

		Log("\n");

		{ Date d(183, 1250);	d.Log(); }
	
		Log("\n");

		{ Date d(128, 321);		d.Log(); }
		{ Date d(5, 1203);		d.Log(); }
		{ Date d(42, 1120);		d.Log(); }
		{ Date d(43, 689);		d.Log(); }

		Log("\n");

		{ Date d(2, 4, 321);	d.Log(); }
		{ Date d(5, 1, 1203);	d.Log(); }
		{ Date d(42, 1, 1120);	d.Log(); }
		{ Date d(1, 2, 689);	d.Log(); }

		Log("\n");

		{ Date("Drach Lan Olminar 1250").Log(); }
	}

	if (iNumber > 0)
	{
		switch (iString > iNumber ? iString - iNumber - 1 : argc - iNumber)
		{
			case 1: Date(atoi(argv[iNumber]), 0).Log(); break;
			case 2: Date(atoi(argv[iNumber]), atoi(argv[iNumber+1]), 0).Log(); break;
			case 3: Date(atoi(argv[iNumber]), atoi(argv[iNumber+1]), atoi(argv[iNumber+2]), 0).Log(); break;
			case 4: Date(atoi(argv[iNumber]), atoi(argv[iNumber+1]), atoi(argv[iNumber+2]), atoi(argv[iNumber+3])).Log(); break;
		}
	}

	if (iString > 0)
	{
		uint start = 0;
		char buff[32];
		buff[0] = 0;

		for (int i=iString ; i<argc ; ++i)
		{
			if (argv[i][0] == '-')
				break;

			strcpy_s(buff + start, 31-start, argv[i]);
			start += strlen(argv[i]);
			
			if (start>=31)
			{
				buff[31] = 0;
				break;
			}

			buff[start++] = ' ';
		}

		buff[start] = 0;

		Date(buff).Log();
	}

	return 0;
}

