#include "FLocation.h"

#include "Config.h"
#include "Utils.h"
#include "libpq-fe.h"
#include "FQuery.h"
#include "FApp.h"


const char* FLocation::s_scolName[ELocElem_MAX] = {"country", "city", "district", "street", "address" };

FLocation::FLocation()
	: m_uID(0)
{}

FLocation::FLocation(PGresult* pRes, int iTuple)
{
	int col = -1;

	col = PQfnumber(pRes, "id");
	assert(col != -1);
	m_uID = atoi(PQgetvalue(pRes, iTuple, col));

	for (uint i=0 ; i<ELocElem_MAX ; ++i)
	{
		col = PQfnumber(pRes, s_scolName[i]);
		assert(col != -1);
		m_sValue[i] = PQgetvalue(pRes, iTuple, col);
	}
}

bool FLocation::UpdateID()
{
	string sQuery;

	assert(m_sValue[0].length() > 0);

	sQuery = "SELECT id FROM \"Location\" ";

	for (uint i=0 ; i<ELocElem_MAX ; ++i)
	{
		sQuery += (i == 0 ? "WHERE " : "AND ");

		if (m_sValue[i].length() > 0)
			sQuery += FormatString("%s = '%s' ", s_scolName[i], m_sValue[i].c_str());
		else
			sQuery += FormatString("%s IS NULL ", s_scolName[i]);
	}

	sQuery += ";";

	PGresult* pResult;
	bool res = false;
	if (FApp::s_oSQLClient.Query(sQuery.c_str(), &pResult))
	{
		assert(PQntuples(pResult) < 2);

		res = (PQntuples(pResult) == 1);
		if (res)
		{
			m_uID = atoi(PQgetvalue(pResult, 0, 0));
		}
	}
	FApp::s_oSQLClient.Clear(pResult);

	return res;
}


void FLocation::Save()
{
	FLocation tmp;

	for (uint i=0 ; i<ELocElem_MAX && m_sValue[i].length()>0 ; ++i)
	{
		tmp.m_sValue[i] = m_sValue[i];
		if (!tmp.UpdateID())
		{
			string sQuery = "INSERT INTO \"Location\" (";
			for (uint j=0 ; j<i+1 ; ++j)
			{
				if (j != 0)
					sQuery += ", ";
				sQuery += string(s_scolName[j]);
			}
			sQuery += ") VALUES (";
			for (uint j=0 ; j<i+1 ; ++j)
			{
				if (j != 0)
					sQuery += ", ";
				sQuery += "'" + m_sValue[j] + "'";
			}
			sQuery += ") ";
			sQuery += "RETURNING id;";

			PGresult* pResult;
			FApp::s_oSQLClient.Query(sQuery, &pResult);

			assert(PQntuples(pResult) == 1);
			m_uID = atoi(PQgetvalue(pResult, 0, 0));

			FApp::s_oSQLClient.Clear(pResult);
		}
	}
}



string FLocation::GetJoinQuery() const
{
	string sQuery;

	sQuery += FQ_EVENT_JOIN_LOCATION_BEGIN;

	if (IsNull())
	{
		sQuery += FormatString("WHERE \"Location\".%s = 'none' ", s_scolName[0]);
	}
	else
	{
		assert(m_sValue[0].length() > 0);

		for (uint i=0 ; i<ELocElem_MAX ; ++i)
		{
			if (m_sValue[i].length() > 0)
			{
				sQuery += (i == 0 ? "WHERE " : "AND ");
				sQuery += FormatString("\"Location\".%s = '%s' ", s_scolName[i], m_sValue[i].c_str());
			}
		}
	}

	sQuery += FQ_EVENT_JOIN_LOCATION_END;

	return sQuery;
}

string FLocation::GetFormated() const
{
	string out;

	for (uint i=0 ; i<ELocElem_MAX ; ++i)
	{
		if (m_sValue[i].length() > 0)
		{
			if (i>0)
				out += ", ";
			out += m_sValue[i];
		}
	}

	return out;
}

// static
FLocation FLocation::Parse(const char* str)
{
	FLocation loc;

	int begin = 0;
	int end = 0;

	for (uint i= 0 ; i<ELocElem_MAX ; ++i)
	{
		while (isspace(str[begin]) || str[begin] == ',') ++begin;
		if (str[begin] == 0)
			break;
		end = begin + 1;
		while (!isspace(str[end]) && str[end] != ',' && str[end] != 0) ++end;

		loc.m_sValue[i] = string(str, begin, end-begin);

		if (str[end] == 0)
			break;

		begin = end;
	}

	if (!loc.UpdateID())
	{
		string msg = FormatString("Create new Location %s ? ", loc.GetFormated().c_str());
		int answer = wxMessageBox(wxString(msg.c_str(), wxConvISO8859_1), "Location not found", wxYES_NO, NULL);
		if (answer == wxYES)
		{
			loc.Save();
		}
	}

	return loc;
}

