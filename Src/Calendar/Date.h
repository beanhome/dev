#ifndef DATE_H
#define DATE_H

#include "Utils.h"

class Date
{
public:
	Date();
	Date(uint iDay, uint iWeek, uint iMonth, uint iYear);
	Date(uint iMonthDay, uint iMonth, uint iYear);
	Date(uint iYearDay, uint iYear);
	Date(const char* sName);
	~Date();


	uint GetYear() const { return m_iYear; }
	uint GetMonth() const { return m_iMonth; }
	uint GetWeek() const { return m_iWeek; }
	uint GetDay() const { return m_iDay; }
	
	uint GetMonthDay() const { return m_iMonthDay; }
	uint GetYearDay() const { return m_iYearDay; }

	const char* GetMonthName() const { return s_sMonth[GetMonthID()]; }
	const char* GetWeekName() const { return s_sWeek[GetWeekID()]; }
	const char* GetDayName() const { return s_sDay[GetDayID()]; }

	void Log() const;

	static void PrintYear();

private:
	uint GetMonthID() const;
	uint GetWeekID() const;
	uint GetDayID() const;

private:
	static char s_sMonth[8][32];
	static char s_sWeek[8][32]; 
	static char s_sDay[8][32];

	uint m_iYear;
	uint m_iMonth;
	uint m_iWeek;
	uint m_iDay;

	uint m_iYearDay;
	uint m_iMonthDay;
};

#endif
