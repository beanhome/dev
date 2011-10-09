#ifndef FSQLCLIENT_H
#define FSQLCLIENT_H

#include "Config.h"
#include "Utils.h"
#include "libpq-fe.h"

class FSQLClient
{
	public:
		FSQLClient();
		~FSQLClient();

		bool IsWriter() const { return m_bIsWriter; }

		bool Connect(const string& sHost, const string& iPort, const string& sBaseName, const string& sLogin, const string& sPassword, string& sError);
		void Disconnect();

		const string& GetUser() const { return m_sUser; }

		bool Query(const string& sQuery, PGresult** res);
		bool Query(const string& sQuery);

		void Clear(PGresult* pResult);

	private:
		PGconn     *m_pConnection;

		string		m_sUser;
		bool		m_bIsWriter;
};


#endif