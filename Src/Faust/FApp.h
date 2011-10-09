#ifndef FAPP_H
#define FAPP_H

#include "wx/wx.h" 
#include "FSQLClient.h"
#include "FEventMap.h"

class FMainFrame;
class FLoginDialog;

class FApp: public wxApp
{
	public:
		bool Connect();
		bool Login();
		bool Logout();

	private:
		virtual bool OnInit();
		virtual int OnExit();
		virtual int MainLoop();


	public:
		static FSQLClient s_oSQLClient;
		static FEventMap s_oEventMap;

		FMainFrame* m_pMainFrame;
		FLoginDialog* m_pLoginDialog;

		string m_sHost;
		string m_sPort;
		string m_sBaseName;
		string m_sLogin;
		string m_sPassword;
		string m_sConfigPath;
		string m_sError;
};

DECLARE_APP(FApp)

#endif