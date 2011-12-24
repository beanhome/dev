#ifndef FDATATION_H
#define FDATATION_H

#include "Utils.h"
#include "Config.h"

class FDate
{
	public:
		FDate();
		FDate(uint uYear);
		FDate(uint uYear, uint uMonth);
		FDate(uint uYear, uint uMonth, uint uDay);
		FDate(const char* sDate);

		FDate& operator=(const FDate& right);

		bool IsNull() const { return m_bNull; }

		uint GetYear() const { return m_uYear; }
		uint GetMonth() const { return m_uMonth; }
		uint GetDay() const { return m_uDay; }

		const char* GetFormated() const { return m_sOutput; }

		void SetYear(uint uYear) { m_uYear = uYear; Format(); }
		void SetMonth(uint uMonth) { m_uMonth = uMonth; Format(); }
		void SetDay(uint uDay) { m_uDay = uDay; Format(); }

		bool Parse(const char* sDate);
		

	private:
		bool Check() const;
		void Format();

	private:
		bool			m_bNull;
		uint			m_uYear;
		uint			m_uMonth;
		uint			m_uDay;

		char			m_sOutput[12];
};

bool operator==(const FDate& oLeft, const FDate& oRight);
bool operator!=(const FDate& oLeft, const FDate& oRight);
bool operator<(const FDate& oLeft, const FDate& oRight);
bool operator>(const FDate& oLeft, const FDate& oRight);
bool operator<=(const FDate& oLeft, const FDate& oRight);
bool operator>=(const FDate& oLeft, const FDate& oRight);


class FDatation
{
	public:
		FDatation();
		FDatation(const FDate& start);
		FDatation(const FDate& start, const FDate& end);

		bool IsNull() const { return m_oStart.IsNull(); }

		const FDate& GetStart() const { return m_oStart; }
		FDate& GetStart() { return m_oStart; }
		const FDate& GetEnd() const { return m_oEnd; }
		FDate& GetEnd() { return m_oEnd; }

		string GetFormated() const;

	public:
		static FDatation ParseResult(const char* sLine);
		static FDatation ParseResult(const char* sStart, const char* sEnd);


	private:
		FDate			m_oStart;
		FDate			m_oEnd;

};


#endif