#include "FRoleControlView.h"
#include "Utils.h"
#include "Config.h"
#include "FQuery.h"
#include "FApp.h"
#include "FListControl.h"

BEGIN_EVENT_TABLE(FRoleControlView, FRoleControl)
	EVT_CHECKBOX(ID_Activate, OnActivate)
	EVT_CHOICE(ID_Login, OnChangeLogin)
END_EVENT_TABLE()


FRoleControlView::FRoleControlView(wxWindow *parent, wxWindowID id, const wxString& sLabel)
	: FRoleControl(parent, id, sLabel)
	, m_pActivateCheckBox(NULL)
	, m_pLogin(NULL)
	, m_pLoginControl(NULL)
{
	wxStaticBoxSizer* pSizer = new wxStaticBoxSizer(wxVERTICAL, this, sLabel);

	if (FApp::s_oSQLClient.IsWriter())
	{
		wxBoxSizer* pActivateSizer = new wxBoxSizer(wxHORIZONTAL);
		{
			m_pActivateCheckBox = new wxCheckBox(this, ID_Activate, wxT(""), wxDefaultPosition, wxDefaultSize);
			pActivateSizer->Add(m_pActivateCheckBox);

			wxStaticText* pActivateText = new wxStaticText(this, wxID_ANY, wxString(wxT("Activate")));
			pActivateSizer->Add(pActivateText, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
		}
		pSizer->Add(pActivateSizer, 0, wxBOTTOM, 3);
	}

	wxBoxSizer* pLoginSizer = new wxBoxSizer(wxHORIZONTAL);
	{
		wxStaticText* pLoginText = new wxStaticText(this, wxID_ANY, wxString(wxT("Login")), wxDefaultPosition, wxSize(50, -1));
		pLoginSizer->Add(pLoginText, 0, wxALIGN_CENTER_VERTICAL, 0);

		const string& sLogin = FApp::s_oSQLClient.GetUser();
		if (FApp::s_oSQLClient.IsWriter())
		{
			m_pLogin = new wxChoice(this, ID_Login, wxDefaultPosition, wxSize(100, -1));
			pLoginSizer->Add(m_pLogin, 0, 0, 0);
			UpdateLoginList(sLogin);
		}
		else
		{
			m_pLoginControl = new wxTextCtrl(this, wxID_ANY, wxString(sLogin.c_str(), wxConvISO8859_1), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
			pLoginSizer->Add(m_pLoginControl);
		}
	}
	pSizer->Add(pLoginSizer, 0, wxBOTTOM, 3);

	FRoleControl::Create(pSizer);

	SetSizeHints(160, -1, 160, -1);
	SetSizerAndFit(pSizer);
	Layout();

	if (m_pActivateCheckBox != NULL)
	{
		m_pActivateCheckBox->SetValue(false);
		Activate(false);
	}
	else
	{
		if (m_pRole->GetCount() > 0)
			m_pRole->SetSelection(0);
	}
}

string FRoleControlView::GetLogin() const
{
	wxString sLogin = m_pLogin->GetString(m_pLogin->GetSelection());
	return string(sLogin.mb_str(wxConvISO8859_1));
}


void FRoleControlView::UpdateLoginList(const string& sLogin)
{
	m_pLogin->Clear();

	PGresult* pResult;
	if (FApp::s_oSQLClient.Query("SELECT rolname FROM pg_roles WHERE rolcanlogin = true;", &pResult))
	{
		m_pLogin->Append(wxT("everybody"));

		int iTuplesCount = PQntuples(pResult);
		for (int i=0 ; i<iTuplesCount ; ++i)
		{
			int col = PQfnumber(pResult, "rolname");
			m_pLogin->Append(wxString(PQgetvalue(pResult, i, col), wxConvISO8859_1));
		}
	}
	FApp::s_oSQLClient.Clear(pResult);

	m_pLogin->SetSelection(m_pLogin->FindString(wxString(sLogin.c_str(), wxConvISO8859_1)));
}



bool FRoleControlView::IsActivated() const
{
	return (m_pActivateCheckBox == NULL || m_pActivateCheckBox->IsChecked());
}

void FRoleControlView::Activate(bool bActivate)
{
	if (m_pLogin != NULL)
		m_pLogin->Enable(bActivate);
	if (m_pLoginControl != NULL)
		m_pLoginControl->Enable(bActivate);
	m_pRole->Enable(bActivate);
}


string FRoleControlView::GetJoinQuery() const
{
	vector<string> aRole;
	GetRole(aRole);

	string sQuery;
	if (IsActivated() && aRole.size() > 0)
	{
		sQuery += FQ_EVENT_JOIN_ROLE_BEGIN;

		for (uint i=0 ; i<aRole.size() ; ++i)
		{
			sQuery += (i == 0 ? "WHERE " : "OR ");
			if (aRole[i] == "everybody")
				sQuery += FQ_EVENT_JOIN_ROLE_EVYBDY;
			else
				sQuery += FormatString(FQ_EVENT_JOIN_ROLE, aRole[i].c_str());
		}

		sQuery += FQ_EVENT_JOIN_ROLE_END;
	}

	return sQuery;
}

void FRoleControlView::OnActivate(wxCommandEvent& event)
{
	Activate(IsActivated());
}

void FRoleControlView::OnChangeLogin(wxCommandEvent& event)
{
	UpdateRoleList();

	if (m_pRole->GetCount() > 0)
		m_pRole->SetSelection(0);
}

