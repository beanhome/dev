#include "FLoginDialog.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "wx\datetime.h"
#include "wx\calctrl.h"
#include "FDatation.h"

BEGIN_EVENT_TABLE(FLoginDialog, wxFrame)
	EVT_BUTTON(ID_OkButton, OnClickOkButton)
	EVT_BUTTON(ID_CancelButton, OnClickCancelButton)
END_EVENT_TABLE()


FLoginDialog::FLoginDialog(const wxString& title, const string& sHost, const string& sPort, const string& sBaseName, const string& sLogin, const string& sPassword, const string& sError)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
	wxWindow* pBG = new wxWindow(this, wxID_ANY);

	wxBoxSizer* pBGSizer = new wxBoxSizer(wxVERTICAL);
	pBGSizer->Add(pBG, 1, wxEXPAND);
	{
		wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
		{
			wxFlexGridSizer* pEntrySizer = new wxFlexGridSizer(2);
			{
				int iLabelWidth = 65;
				int iControlWidth = 135;

				wxStaticText* pHostLabel = new wxStaticText(pBG, wxID_ANY, wxT("Host : "), wxDefaultPosition, wxSize(iLabelWidth, -1));
				pEntrySizer->Add(pHostLabel, 0, wxLEFT, 5);
				m_pHost = new wxTextCtrl(pBG, ID_Host, wxString(sHost.c_str(), wxConvISO8859_1), wxDefaultPosition, wxSize(iControlWidth, -1));
				pEntrySizer->Add(m_pHost, 0, wxRIGHT, 5);

				wxStaticText* pPortLabel = new wxStaticText(pBG, wxID_ANY, wxT("Port : "), wxDefaultPosition, wxSize(iLabelWidth, -1));
				pEntrySizer->Add(pPortLabel, 0, wxLEFT, 5);
				m_pPort = new wxTextCtrl(pBG, ID_Port, wxString(sPort.c_str(), wxConvISO8859_1), wxDefaultPosition, wxSize(iControlWidth, -1));
				pEntrySizer->Add(m_pPort, 0, wxRIGHT, 5);

				wxStaticText* pBaseNameLabel = new wxStaticText(pBG, wxID_ANY, wxT("BaseName : "), wxDefaultPosition, wxSize(iLabelWidth, -1));
				pEntrySizer->Add(pBaseNameLabel, 0, wxLEFT, 5);
				m_pBaseName = new wxTextCtrl(pBG, ID_BaseName, wxString(sBaseName.c_str(), wxConvISO8859_1), wxDefaultPosition, wxSize(iControlWidth, -1));
				pEntrySizer->Add(m_pBaseName, 0, wxRIGHT, 5);

				wxStaticText* pLoginLabel = new wxStaticText(pBG, wxID_ANY, wxT("Login : "), wxDefaultPosition, wxSize(iLabelWidth, -1));
				pEntrySizer->Add(pLoginLabel, 0, wxLEFT, 5);
				m_pLogin = new wxTextCtrl(pBG, ID_Login, wxString(sLogin.c_str(), wxConvISO8859_1), wxDefaultPosition, wxSize(iControlWidth, -1));
				pEntrySizer->Add(m_pLogin, 0, wxRIGHT, 5);

				wxStaticText* pPasswordLabel = new wxStaticText(pBG, wxID_ANY, wxT("Password : "), wxDefaultPosition, wxSize(iLabelWidth, -1));
				pEntrySizer->Add(pPasswordLabel, 0, wxLEFT, 5);
				m_pPassword = new wxTextCtrl(pBG, ID_Password, wxString(sPassword.c_str(), wxConvISO8859_1), wxDefaultPosition, wxSize(iControlWidth, -1), wxTE_PASSWORD);
				pEntrySizer->Add(m_pPassword, 0, wxRIGHT, 5);
			}
			pSizer->Add(pEntrySizer);

			if (sError.length() > 0)
			{
				pSizer->AddSpacer(5);
				wxTextCtrl* perror = new wxTextCtrl(pBG, wxID_ANY, wxString(sError.c_str(), wxConvISO8859_1), wxDefaultPosition, wxSize(-1, 60), wxTE_READONLY | wxTE_MULTILINE);
				pSizer->Add(perror, 0, wxEXPAND, 0);
			}

			pSizer->AddSpacer(5);

			wxBoxSizer* pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
			{
				m_pOkButton = new wxButton(pBG, ID_OkButton, wxT("OK"));
				pButtonSizer->Add(m_pOkButton, 1, 0, 0);
				m_pCancelButton = new wxButton(pBG, ID_CancelButton, wxT("Cancel"));
				pButtonSizer->Add(m_pCancelButton, 1, 0, 0);
			}
			pSizer->Add(pButtonSizer, 0, wxEXPAND);

		}
		pBG->SetSizerAndFit(pSizer);
		pBG->Layout();
	}
	SetSizerAndFit(pBGSizer);
	SetSizeHints(GetSize(), GetSize());
	Layout();
}


FLoginDialog::~FLoginDialog()
{

}

void FLoginDialog::OnClickOkButton(wxCommandEvent& event)
{
	Close();

	FApp* pApp = wxDynamicCast(wxTheApp, FApp);
	pApp->Login();
}

void FLoginDialog::OnClickCancelButton(wxCommandEvent& event)
{
	FApp* pApp = wxDynamicCast(wxTheApp, FApp);
	pApp->Exit();
}
