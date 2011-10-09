#include "FSQLClient.h"
#include "Config.h"
#include "Utils.h"

#include "libpq-fe.h"

#ifdef USE_LIBPQTYPES
#include "libpqtypes.h"
#endif


#include <wx\utils.h> // busy cursor

FSQLClient::FSQLClient()
	: m_pConnection(NULL)
{}

FSQLClient::~FSQLClient()
{}

bool FSQLClient::Connect(const string& sHost, const string& sPort, const string& sBaseName, const string& sLogin, const string& sPassword, string& sError)
{
	m_sUser = sLogin;

#ifndef DISCONNECTED
	string sConnInfo;
	sConnInfo += ( isdigit(sHost[0]) ? "hostaddr = " : "host = ") + sHost + " ";
	sConnInfo += "port = " + sPort + " ";
	sConnInfo += "dbname = " + sBaseName + " ";
	sConnInfo += "user = " + sLogin + " ";
	sConnInfo += "password = " + sPassword + " ";

	if (m_pConnection != NULL)
		Disconnect();

	m_pConnection = PQconnectdb(sConnInfo.c_str());

	if (PQstatus(m_pConnection) != CONNECTION_OK)
	{
		sError = PQerrorMessage(m_pConnection);
		Log("Connection to database failed: %s", PQerrorMessage(m_pConnection));
		return false;
	}

	PGresult* pResult;
	if (Query(FormatString("SELECT pg_has_role('%s', 'Scenario', 'MEMBER');", m_sUser.c_str()), &pResult))
	{
		assert(PQntuples(pResult) == 1);
		assert(PQnfields(pResult) == 1);
		char* res = PQgetvalue(pResult, 0, 0);
		m_bIsWriter = (res[0] == 't' && res[1] == 0);
	}
	Clear(pResult);
#else
	m_bIsWriter = true;
#endif

#ifdef USE_LIBPQTYPES
	PQinitTypes(m_pConnection);

	/* need to register simple and complex */
	PGregisterType types[] = {
		{"Datation", NULL, NULL}
	};

	if (PQregisterTypes(m_pConnection, PQT_COMPOSITE, types, 1, 0) == 0)
	{
		Log("PQregisterTypes Error : %s\n", PQgeterror());
	}
#endif

	return true;
}

void FSQLClient::Disconnect()
{
#ifndef DISCONNECTED
	PQfinish(m_pConnection);
#endif
	m_pConnection = NULL;
}

bool FSQLClient::Query(const string& sQuery)
{
	PGresult* res;
	bool err = Query(sQuery, &res);
	PQclear(res);
	return err;
}

bool FSQLClient::Query(const string& sQuery, PGresult** res)
{
	string sSendQuery = sQuery;

	uint begin = 0;
	uint end = 0;
	while (begin < sSendQuery.length())
	{
		begin = sSendQuery.find_first_of(" \t\n\r", begin);
		if (begin == (uint)-1)
			break;
		end = sSendQuery.find_first_not_of(" \t\n\r", begin);
		if (end == (uint)-1)
			break;
		if (end > begin)
			sSendQuery.replace(begin, end-begin, 1, ' ');
		begin++;

	}
	string sLogQuery = sSendQuery;

	begin = 0;
	while (begin < sLogQuery.length())
	{
		begin = sLogQuery.find_first_of("%", begin);
		if (begin == (uint)-1)
			break;
		sLogQuery.replace(begin, 1, "%%");
		begin+=2;
	}

	Log(sLogQuery.c_str());
	Log("\n");

#ifndef DISCONNECTED
	wxBeginBusyCursor();
	*res = PQexec(m_pConnection, sSendQuery.c_str());
	wxEndBusyCursor();
	ExecStatusType err = PQresultStatus(*res);
	switch (err)
	{
		case PGRES_EMPTY_QUERY:
			Log("Query is empty\n");
			return false;

		case PGRES_COMMAND_OK:
		case PGRES_TUPLES_OK:
			break;

		case PGRES_COPY_OUT:
		case PGRES_COPY_IN:
			break;

		case PGRES_BAD_RESPONSE:
		case PGRES_NONFATAL_ERROR:
		case PGRES_FATAL_ERROR:
		default:
			Log("Query \"%s\" failed\n%s\n", sSendQuery.c_str(), PQerrorMessage(m_pConnection));
			return false;
	}
#else
	*res = PQmakeEmptyPGresult(m_pConnection, PGRES_COMMAND_OK);
#endif

#if 0
	if (err = PGRES_TUPLES_OK)
	{
		int iFieldsCount = PQnfields(*res);
		int iTuplesCount = PQntuples(*res);
		String output;

		for (int i=0 ; i<iFieldsCount ; ++i)
		{
			Log("%-32s ", PQfname(*res, i));
		}
		Log("\n");

		for (int i=0 ; i<iTuplesCount; ++i)
		{
			for (int j=0 ; j<iFieldsCount ; ++j)
			{
				if (PQgetisnull(*res, i, j))
				{
					output = "";
				}
				else
				{
					output = PQgetvalue(*res, i, j);
					/*
					int start = output.find_first_not_of(" \t");
					int end = output.find_last_not_of(" \t");
					output = output.substr(start, end-start+1);
					*/
					if (output.length() > 31)
						output[31] = 0;
				}
				Log("%-32s ", output.c_str());
			}
			Log("\n");
		}
	}
#endif

	return true;
}


void FSQLClient::Clear(PGresult* pResult)
{
	PQclear(pResult);
}
