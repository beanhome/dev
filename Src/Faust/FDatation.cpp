#include "FDatation.h"

#include "Utils.h"
#include "Config.h"


FDate::FDate()
	: m_bNull(true)
	, m_uYear(0)
	, m_uMonth(0)
	, m_uDay(1)
{
	Format();
}

FDate::FDate(uint uYear)
	: m_bNull(false)
	, m_uYear(uYear)
	, m_uMonth(0)
	, m_uDay(1)
{
	Format();
}

FDate::FDate(uint uYear, uint uMonth)
	: m_bNull(false)
	, m_uYear(uYear)
	, m_uMonth(uMonth)
	, m_uDay(1)
{
	Format();
}

FDate::FDate(uint uYear, uint uMonth, uint uDay)
	: m_bNull(false)
	, m_uYear(uYear)
	, m_uMonth(uMonth)
	, m_uDay(uDay)
{
	Format();
}

FDate::FDate(const char* sDate)
	: m_bNull(true)
	, m_uYear(0)
	, m_uMonth(0)
	, m_uDay(1)
{
	m_bNull = !Parse(sDate);
	Format();
}


FDate& FDate::operator=(const FDate& right)
{
	m_bNull = right.m_bNull;
	m_uYear = right.m_uYear;
	m_uMonth = right.m_uMonth;
	m_uDay = right.m_uDay;

	memcpy(m_sOutput, right.m_sOutput, 12);

	return *this;
}


bool FDate::Parse(const char* sDate)
{
	if (sDate == NULL || sDate[0] == 0)
	{
		m_bNull = true;
	}
	else
	{
		m_uDay   = atoi(sDate+0);
		m_uMonth = atoi(sDate+3)-1;
		m_uYear  = atoi(sDate+6);

		m_bNull = !Check();
		Format();
	}

	return !m_bNull;
}

bool FDate::Check() const
{
	return (m_uMonth < 12
	     && m_uDay > 0 && m_uDay < 32);
}

void FDate::Format()
{
	if (!m_bNull)
		sprintf_s(m_sOutput, 11, "%02d-%02d-%04d", m_uDay, m_uMonth+1, m_uYear);
	else
		m_sOutput[0] = 0;
}


bool operator==(const FDate& oLeft, const FDate& oRight)
{
	if (oLeft.IsNull() && oRight.IsNull())
		return true;
	else if (oLeft.IsNull() != oRight.IsNull())
		return false;
	else
		return (oLeft.GetYear() == oRight.GetYear() && oLeft.GetMonth() == oRight.GetMonth() && oLeft.GetDay() == oRight.GetDay());
}

bool operator!=(const FDate& oLeft, const FDate& oRight)
{
	return ! (oLeft == oRight);
}

bool operator<(const FDate& oLeft, const FDate& oRight)
{
	if (oLeft.IsNull() && oRight.IsNull())
		return true;
	else if (oLeft.IsNull() && !oRight.IsNull())
		return true;
	else if (!oLeft.IsNull() && oRight.IsNull())
		return false;
	else //if (!oLeft.IsNull() && !oRight.IsNull())
		return
			oLeft.GetYear() < oRight.GetYear()
			|| oLeft.GetYear() == oRight.GetYear() && oLeft.GetMonth() < oRight.GetMonth()
			|| oLeft.GetYear() == oRight.GetYear() && oLeft.GetMonth() == oRight.GetMonth() && oLeft.GetDay() < oRight.GetDay();
}

bool operator>(const FDate& oLeft, const FDate& oRight)
{
	return (oLeft != oRight) && !(oLeft < oRight);
}

bool operator<=(const FDate& oLeft, const FDate& oRight)
{
	return (oLeft == oRight) || (oLeft < oRight);
}

bool operator>=(const FDate& oLeft, const FDate& oRight)
{
	return !(oLeft < oRight);
}




FDatation::FDatation()
	: m_oStart()
	, m_oEnd()
{}

FDatation::FDatation(const FDate& start)
	: m_oStart(start)
	, m_oEnd()
{}

FDatation::FDatation(const FDate& start, const FDate& end)
	: m_oStart(start)
	, m_oEnd(end)
{}

FDatation FDatation::ParseResult(const char* sLine)
{
	// "(1903-02-01,1906-05-04)"	

	if (sLine[0] == 0)
		return FDatation();

	assert(strlen(sLine) == 23);

	int ys = -1;
	int ms = -1;
	int ds = -1;
	int ye = -1;
	int me = -1;
	int de = -1;

	ys = atoi(sLine+1);
	ms = atoi(sLine+6)-1;
	ds = atoi(sLine+9);
	
	ye = atoi(sLine+12);
	me = atoi(sLine+17)-1;
	de = atoi(sLine+20);

	assert(ys != -1);
	assert(ms != -1);
	assert(ds != -1);

	assert(ye != -1);
	assert(me != -1);
	assert(de != -1);

	return FDatation(FDate(ys, ms, ds), FDate(ye, me, de));
}

string FDatation::GetFormated() const
{
	string sDatation;

	if (IsNull())
	{
		sDatation = "NULL";
	}
	else
	{
		assert(GetStart().IsNull() == false || GetEnd().IsNull() == false);

		const char* sStart = GetStart().GetFormated();
		const char* sEnd = GetEnd().GetFormated();

		if (GetEnd().IsNull())
			sEnd = sStart;

		if (GetStart().IsNull())
			sStart = sEnd;

		sDatation = "('" + string(sStart) + "','" + string(sEnd) + "')";
	}

	return sDatation;
}

