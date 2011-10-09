#include "FNewRoleDialog.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "wx\datetime.h"
#include "wx\calctrl.h"

BEGIN_EVENT_TABLE(FNewRoleDialog, wxDialog)
	EVT_BUTTON(wxID_OK, OnOkButton)
END_EVENT_TABLE()


FNewRoleDialog::FNewRoleDialog(wxWindow *parent, wxWindowID id, const wxString& sTitle, const wxPoint& pos, const wxSize& size, EMode eMode)
	: wxDialog(parent, id, sTitle, pos, size)
	, m_pNameEntry(NULL)
	, m_pNameChoice(NULL)
	, m_pPassword(NULL)
	, m_pParentRole(NULL)
	, m_eMode(eMode)
{
	wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);

	int iLeftWidth = 65;
	int iRightWidth = 100;
	wxFlexGridSizer* pGridSizer = new wxFlexGridSizer(2);
	{
		wxStaticText* pNameLabel = new wxStaticText(this, wxID_ANY, wxT("Name : "), wxDefaultPosition, wxSize(iLeftWidth, -1));
		pGridSizer->Add(pNameLabel, 0, wxALIGN_CENTRE_VERTICAL);

		if (m_eMode != EM_EditUser)
		{
			m_pNameEntry = new wxTextCtrl(this, ID_NameEntry, wxT(""), wxDefaultPosition, wxSize(iRightWidth, -1));
			pGridSizer->Add(m_pNameEntry, 0 );
		}
		else
		{
			m_pNameChoice = new wxChoice(this, ID_NameChoice, wxDefaultPosition, wxSize(iRightWidth, -1));
			pGridSizer->Add(m_pNameChoice, 0 );
		}

		if (m_eMode != EM_NewGroup)
		{
			wxStaticText* pPasswordLabel = new wxStaticText(this, wxID_ANY, wxT("Password : "), wxDefaultPosition, wxSize(iLeftWidth, -1));
			pGridSizer->Add(pPasswordLabel, 0, wxALIGN_CENTRE_VERTICAL);

			m_pPassword = new wxTextCtrl(this, ID_Password, wxT(""), wxDefaultPosition, wxSize(iRightWidth, -1), wxTE_PASSWORD);
			pGridSizer->Add(m_pPassword, 0 );
		}

		wxStaticText* pRoleLabel = new wxStaticText(this, wxID_ANY, (m_eMode == EM_NewGroup ? wxT("Group : ") : wxT("Parent Group : ")), wxDefaultPosition, wxSize(iLeftWidth, -1));
		pGridSizer->Add(pRoleLabel, 0, wxALIGN_CENTRE_VERTICAL);

		m_pParentRole = new wxListBox(this, ID_ParentRole, wxDefaultPosition, wxSize(iRightWidth, -1));
		pGridSizer->Add(m_pParentRole);
	}
	pSizer->Add(pGridSizer, 0, wxALL, 5);

	wxSizer* pButtonSizer = CreateButtonSizer(wxOK | wxCANCEL);
	pSizer->Add(pButtonSizer, 0, wxALIGN_CENTRE_HORIZONTAL | wxBOTTOM, 5);

	UpdateGroupList();
	if (m_eMode == EM_EditUser)
		UpdateUserList();

	SetSizerAndFit(pSizer);
	Layout();
}

string FNewRoleDialog::GetRoleName() const
{
	if (m_eMode != EM_EditUser)
		return string(m_pNameEntry->GetValue().mb_str(wxConvISO8859_1));
	else
		return string(m_pNameChoice->GetString(m_pNameChoice->GetSelection()).mb_str(wxConvISO8859_1));
}

string FNewRoleDialog::GetPassword() const
{
	if (m_eMode != EM_NewGroup && m_pPassword != NULL)
		return string(m_pPassword->GetValue().mb_str(wxConvISO8859_1));

	return string();
}

string FNewRoleDialog::GetParentRole() const
{
	if (m_pParentRole->GetSelection() > -1)
		return string(m_pParentRole->GetString(m_pParentRole->GetSelection()).mb_str(wxConvISO8859_1));
	
	return string();
}

void FNewRoleDialog::UpdateGroupList()
{
	m_pParentRole->Clear();
	PGresult* pResult;
	if (FApp::s_oSQLClient.Query(FQ_ALLGROUPS, &pResult))
	{
		int iTuplesCount = PQntuples(pResult);
		for (int i=0 ; i<iTuplesCount ; ++i)
		{
			wxString sRole = wxString(PQgetvalue(pResult, i, 0), wxConvISO8859_1);
			m_pParentRole->Append(sRole);
		}
	}
	FApp::s_oSQLClient.Clear(pResult);
}

void FNewRoleDialog::UpdateUserList()
{
	m_pNameChoice->Clear();
	PGresult* pResult;
	if (FApp::s_oSQLClient.Query(FQ_ALLUSERS, &pResult))
	{
		int iTuplesCount = PQntuples(pResult);
		for (int i=0 ; i<iTuplesCount ; ++i)
		{
			wxString sRole = wxString(PQgetvalue(pResult, i, 0), wxConvISO8859_1);
			m_pNameChoice->Append(sRole);
		}
	}
	FApp::s_oSQLClient.Clear(pResult);
}

void FNewRoleDialog::OnOkButton(wxCommandEvent& event)
{
	string sName = GetRoleName();
	string sPassword = GetPassword();
	string sParent = GetParentRole();
	string sOption;

	switch (m_eMode)
	{
		case EM_NewUser:	if (sPassword.length() == 0)	m_eMode = EM_NewGroup;			break;
		case EM_NewGroup:	break;
		case EM_EditUser:	if (sPassword.length() == 0 && sParent.length() == 0) { event.Skip(); return; }		break;
		default: assert(false);
	}

	if (sParent == "Scenario")
		sOption = " NOSUPERUSER INHERIT NOCREATEDB CREATEROLE ";
	else
		sOption = " NOSUPERUSER INHERIT NOCREATEDB NOCREATEROLE ";

	string sQuery;
	switch (m_eMode)
	{
		case EM_NewUser:	sQuery = "CREATE ROLE \"" + sName + "\" LOGIN PASSWORD '" + sPassword + "' "		+ sOption + ";";		break;
		case EM_NewGroup:	sQuery = "CREATE ROLE \"" + sName + "\" "											+ sOption + ";";		break;
		case EM_EditUser:	sQuery = "ALTER ROLE \"" + sName + "\" PASSWORD '" + sPassword + "' "				";";		break;
		default: assert(false);
	}

	FApp::s_oSQLClient.Query(sQuery);

	if (sParent.length() > 0)
	{
		switch (m_eMode)
		{
			case EM_NewUser:	sQuery = "GRANT \"" + sParent + "\" TO \"" + sName + "\";";		break;
			case EM_NewGroup:	sQuery = "GRANT \"" + sParent + "\" TO \"" + sName + "\";";		break;
			case EM_EditUser:	sQuery = "GRANT \"" + sParent + "\" TO \"" + sName + "\";";		break;
			default: assert(false);
		}

		FApp::s_oSQLClient.Query(sQuery);
	}

	event.Skip();
}



