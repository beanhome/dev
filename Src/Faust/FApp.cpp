#include "FApp.h"

#include "FMainFrame.h"
#include "FLoginDialog.h"
#include "ConfigFile.h"

IMPLEMENT_APP(FApp)

FSQLClient FApp::s_oSQLClient;
FEventMap FApp::s_oEventMap;

bool FApp::OnInit()
{
	m_pMainFrame = NULL;

	m_sConfigPath = CONFIG_FILEPATH;

	InitLog(argc, argv);	

	for (int i=1 ; i<argc ; ++i)
	{
		if (argv[i][0] == '-')
		{
			switch ((char)argv[i][1])
			{
				case 'h':	m_sHost = wxString(argv[i+1]).mb_str(wxConvISO8859_1);			break;
				case 'p':	m_sPort = wxString(argv[i+1]).mb_str(wxConvISO8859_1);			break;
				case 'd':	m_sBaseName = wxString(argv[i+1]).mb_str(wxConvISO8859_1);		break;
				case 'u':	m_sLogin = wxString(argv[i+1]).mb_str(wxConvISO8859_1);			break;
				case 'w':	m_sPassword = wxString(argv[i+1]).mb_str(wxConvISO8859_1);		break;
				case 'c':	m_sConfigPath = wxString(argv[i+1]).mb_str(wxConvISO8859_1);	break;
			}
		}
	}

	ConfigFile oConfigFile(m_sConfigPath);
	if (oConfigFile.Read())
	{
		if (m_sHost.length() == 0)		m_sHost = oConfigFile.GetOption("Host");
		if (m_sPort.length() == 0)		m_sPort = oConfigFile.GetOption("Port");
		if (m_sBaseName.length() == 0)	m_sBaseName = oConfigFile.GetOption("BaseName");
		if (m_sLogin.length() == 0)		m_sLogin = oConfigFile.GetOption("Login");
		if (m_sPassword.length() == 0)	m_sPassword = oConfigFile.GetOption("Password");
	}

	wxImage::AddHandler(new wxPNGHandler);

	m_pMainFrame = NULL;
	m_pLoginDialog = NULL;
	Login();

	return true;
}

bool FApp::Connect()
{
	if (m_sHost.length() > 0 && m_sPort.length() > 0 && m_sBaseName.length() > 0 && m_sLogin.length() > 0 && m_sPassword.length() > 0)
	{
		return s_oSQLClient.Connect(m_sHost, m_sPort, m_sBaseName, m_sLogin, m_sPassword, m_sError);
	}
	
	return false;
}

bool FApp::Login()
{
	string sError;

	if (m_pLoginDialog != NULL)
	{
		m_sHost = m_pLoginDialog->GetHost();
		m_sPort = m_pLoginDialog->GetPort();
		m_sBaseName = m_pLoginDialog->GetBaseName();
		m_sLogin = m_pLoginDialog->GetLogin();
		m_sPassword = m_pLoginDialog->GetPassword();

		m_pLoginDialog->Close();
		m_pLoginDialog->Destroy();
		m_pLoginDialog = NULL;
	}

	if (Connect())
	{
		assert(m_pMainFrame == NULL);

		m_pMainFrame = new FMainFrame(wxT("Faust"));//, wxPoint(-1,-1), wxSize(526,670));
		m_pMainFrame->Show(TRUE);
		SetTopWindow(m_pMainFrame);

		ConfigFile oConfigFile(m_sConfigPath);
		oConfigFile.SetOption("Host", m_sHost);
		oConfigFile.SetOption("Port", m_sPort);
		oConfigFile.SetOption("BaseName", m_sBaseName);
		oConfigFile.SetOption("Login", m_sLogin);
#ifdef SAVEPASSWORD
		oConfigFile.SetOption("Password", m_sPassword);
#endif
		oConfigFile.Write();
		return true;
	}
	else
	{
		m_pLoginDialog = new FLoginDialog(wxT("Login"), m_sHost, m_sPort, m_sBaseName, m_sLogin, m_sPassword, m_sError);
		m_pLoginDialog->Show(TRUE);
		SetTopWindow(m_pLoginDialog);
		return false;
	}
}

bool FApp::Logout()
{
	//return Login(true);
	if (m_pLoginDialog != NULL)
		m_pLoginDialog->Close();

	m_pLoginDialog = new FLoginDialog(wxT("Login"), m_sHost, m_sPort, m_sBaseName, m_sLogin, m_sPassword, string());
	m_pLoginDialog->Show();
	SetTopWindow(m_pLoginDialog);

	if (m_pMainFrame != NULL)
	{
		m_pMainFrame->Close();
		m_pMainFrame->Destroy();
		m_pMainFrame = NULL;
	}

	return true;
}

int FApp::MainLoop()
{
	int ret = wxApp::MainLoop();

	return ret;
}



int FApp::OnExit()
{
	s_oSQLClient.Disconnect();

	return wxApp::OnExit();
}

