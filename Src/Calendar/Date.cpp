
#include "Date.h"
#include "Utils.h"

char Date::s_sMonth[8][32] = { "Kidis", "Anoëtal", "Nirlan", "Drachlen", "Olminar", "Reolta", "Ylavan", "Artonai" };
char Date::s_sWeek[8][32] = { "Dis", "Tal", "Lan", "Len", "Nar", "Ta", "Van", "Nai" };
char Date::s_sDay[8][32] = { "Ki", "Anoë", "Nir", "Drach", "Olmi", "Reol", "Yla", "Arto" };

Date::Date()
	: m_iYear(0)
	, m_iMonth(1)
	, m_iWeek(1)
	, m_iDay(1)
	, m_iMonthDay(1)
	, m_iYearDay(1)
{
}

Date::Date(uint iDay, uint iWeek, uint iMonth, uint iYear)
	: m_iYear(iYear)
	, m_iMonth(min(iMonth, 8))
	, m_iWeek(min(iWeek, 7))
	, m_iDay(min(iDay, 6))
	, m_iMonthDay(1)
	, m_iYearDay(1)
{
	m_iMonthDay = (1 + (iDay-1) + (iWeek-1)*6);
	m_iYearDay = (m_iMonthDay + (iMonth-1)*7*6);
}

Date::Date(uint iMonthDay, uint iMonth, uint iYear)
	: m_iYear(iYear)
	, m_iMonth(min(iMonth, 8))
	, m_iWeek(1)
	, m_iDay(1)
	, m_iMonthDay(min(iMonthDay, 6*7))
	, m_iYearDay(1)
{
	m_iDay = ((iMonthDay-1)%6) + 1;
	m_iWeek = (((iMonthDay-1)/6)%7) + 1;
	m_iYearDay = (m_iMonthDay + (iMonth-1)*7*6);
}

Date::Date(uint iYearDay, uint iYear)
	: m_iYear(iYear)
	, m_iMonth(1)
	, m_iWeek(1)
	, m_iDay(1)
	, m_iMonthDay(1)
	, m_iYearDay(min(iYearDay, 6*7*8))
{
	iYearDay--;
	m_iDay = (iYearDay%6) + 1;

	iYearDay /= 6;
	m_iWeek = (iYearDay%7) + 1;

	m_iMonth = iYearDay/7 + 1;

	m_iMonthDay = m_iDay + (m_iWeek-1)*6;
}

Date::Date(const char* sName)
	: m_iYear(0)
	, m_iMonth(1)
	, m_iWeek(1)
	, m_iDay(1)
	, m_iMonthDay(1)
	, m_iYearDay(1)
{
	char sMonth[32];
	char sWeek[32];
	char sDay[32];

	uint start = 0;
	uint end = 0;

	while(iswspace(sName[start])) start++;
	end = start;
	while(!iswspace(sName[end])) end++;

	strncpy_s(sDay, sName+start, min(end-start, 31));
	start = end+1;

	while(iswspace(sName[start])) start++;
	end = start;
	while(!iswspace(sName[end])) end++;

	strncpy_s(sWeek, sName+start, min(end-start, 31));
	start = end+1;

	while(iswspace(sName[start])) start++;
	end = start;
	while(!iswspace(sName[end])) end++;

	strncpy_s(sMonth, sName+start, min(end-start, 31));
	start = end+1;

	m_iYear = atoi(sName+start);

	for (uint i=0 ; i<8 ; ++i)
	{
		if (strcmp(s_sMonth[i], sMonth) == 0)
		{
			m_iMonth = i+1;
			break;
		}
	}

	uint w = 0;
	for (uint i=0 ; i<8 ; ++i)
	{
		if (strcmp(s_sWeek[i], sWeek) == 0)
		{
			w = i;
			break;
		}
	}

	m_iWeek = (w>=m_iMonth ? w-1 : w) + 1;
	
	uint d = 0;
	for (uint i=0 ; i<8 ; ++i)
	{
		if (strcmp(s_sDay[i], sDay) == 0)
		{
			d = i;
			break;
		}
	}

	m_iDay = (d>=m_iMonth ? d-1 : d);
	if (d>=m_iWeek)
		m_iDay--;
	m_iDay++;

	m_iMonthDay = (1 + (m_iDay-1) + (m_iWeek-1)*6);
	m_iYearDay = (m_iMonthDay + (m_iMonth-1)*7*6);
}

Date::~Date()
{
}

uint Date::GetMonthID() const
{
	return m_iMonth-1;
}

uint Date::GetWeekID() const
{
	return (m_iWeek-1 < GetMonthID() ? m_iWeek-1 : m_iWeek);
}

uint Date::GetDayID() const
{
	uint iDayID = m_iDay - 1;

	if (m_iDay >= m_iWeek) iDayID++;
	if (iDayID+1 >= m_iMonth) iDayID++;

	return iDayID;
}

void Date::Log() const
{
	char buff[20];
	sprintf_s(buff, 19, "%s %s %s", GetDayName(), GetWeekName(), GetMonthName());
	::Log("%-19s %4d (%02d/%02d) (%02d/%02d/%02d) [%3d]\n", buff, m_iYear, m_iMonthDay, m_iMonth, m_iDay, m_iWeek, m_iMonth, m_iYearDay);
}

void Date::PrintYear()
{
	for (uint m=0 ; m<8 ; ++m)
	{
		::Log("%s\n", s_sMonth[m]);

		for (uint w=0 ; w<7 ; ++w)
		{
			::Log("%-8s ", s_sWeek[w<m ? w : w+1]);
			//::Log("%s \t\t", s_sWeek[w<m ? w : w+1]);

			for (uint d=0 ; d<6 ; ++d)
			{
				Date Day(d+1, w+1, m+1, 0);
				::Log("%-5s ", Day.GetDayName());
				//::Log("%s \t", Day.GetDayName());
			}

			::Log("\n");
		}

		::Log("\n");
	}

	/*
	for (uint i=0 ; i<8*7*6 ; i++)
	{
		Date(i+1, 0).Log();
		
		if ((i+1)%6 == 0 || (i+1)%(6*7) == 0)
			::Log("\n");
	}
	*/

	/*
	int iMonth = 1;
	for (int m=0 ; m<8 ; ++m)
	{
		int iWeek = 1;
		for (int w=0 ; w<8 ; ++w)
		{
			if (m==w) continue;

			int iDay = 1;
			for (int d=0 ; d<8 ; d++)
			{
				if (d==m || d==w) continue;

				::Log("[%3d] (%02d-%02d-%02d) %s %s %s [%d %d %d]\n", 1 + (iDay-1) + (iWeek-1)*6 + (iMonth-1)*7*6, iMonth, iWeek, iDay, s_sMonth[m], s_sWeek[w], s_sDay[d], m, w, d);

				iDay++;
			}

			iWeek++;
		}

		iMonth++;
	}
	*/
}
