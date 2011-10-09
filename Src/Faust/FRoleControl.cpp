#include "FRoleControl.h"
#include "Utils.h"
#include "Config.h"
#include "FQuery.h"
#include "FApp.h"
#include "FListControl.h"
#include "FEvent.h"

BEGIN_EVENT_TABLE(FRoleControl, wxPanel)
	EVT_LISTBOX(ID_Role, OnChangeRole)
END_EVENT_TABLE()


FRoleControl::FRoleControl(wxWindow *parent, wxWindowID id, const wxString& sLabel)
	: wxPanel(parent, id)
	, m_pRole(NULL)
{
}

void FRoleControl::Create(wxSizer* pSizer)
{
	m_pRole = new FListControl(this, ID_Role, wxDefaultPosition, wxSize(150, -1));//, wxArrayString(), wxLB_MULTIPLE);
	pSizer->Add(m_pRole, 0, 0, 0);

	UpdateRoleList();
}

string FRoleControl::GetLogin() const
{
	return FApp::s_oSQLClient.GetUser();
}

void FRoleControl::ClearSelection()
{
	m_pRole->DeselectAll();
}

void FRoleControl::SetSelection(const wxString& sRole, bool bSelect)
{
	int id = m_pRole->FindString(sRole);
	if (id != wxNOT_FOUND)
		m_pRole->SetSelection(id, bSelect);
}

void FRoleControl::SetSelection(const string& sRole, bool bSelect)
{
	SetSelection(wxString(sRole.c_str(), wxConvISO8859_1), bSelect);
}

void FRoleControl::SetSelection(const wxString& sRole, ESelectState eState)
{
	int id = m_pRole->FindString(sRole);
	if (id != wxNOT_FOUND)
		m_pRole->SetSelection(id, eState);
}

void FRoleControl::SetSelection(const string& sRole, ESelectState eState)
{
	SetSelection(wxString(sRole.c_str(), wxConvISO8859_1), eState);
}


void FRoleControl::UpdateRoleList()
{
	m_pRole->Clear();

	wxString sEverybody = wxString(wxT("everybody"), wxConvISO8859_1);

	if (GetLogin().length() > 0)
		m_pRole->Append(wxString(GetLogin().c_str(), wxConvISO8859_1));

	if (GetLogin() != "everybody")
		m_pRole->Append(sEverybody);

	if (GetLogin().length() > 0)
	{
		PGresult* pResult;
		string SQuery = FormatString(FQ_LOGINGROUPS, GetLogin().c_str());
		if (FApp::s_oSQLClient.Query(SQuery, &pResult))
		{
			int iTuplesCount = PQntuples(pResult);
			for (int i=0 ; i<iTuplesCount ; ++i)
			{
				wxString sRole = wxString(PQgetvalue(pResult, i, 0), wxConvISO8859_1);
				if (m_pRole->FindString(sRole) == wxNOT_FOUND)
					m_pRole->Append(sRole);
			}
		}
		FApp::s_oSQLClient.Clear(pResult);
	}
}

void FRoleControl::GetRole(vector<string>& aRole) const
{
	aRole.clear();

	for (uint i=0 ; i<m_pRole->GetCount() ; ++i)
	{
		if (m_pRole->IsSelected(i))
			aRole.push_back(string(m_pRole->GetString(i).mb_str(wxConvISO8859_1)));
	}

	if (aRole.size() == 0)
		aRole.push_back("everybody");
}

void FRoleControl::ApplyModif(FEvent& oEvent)
{
	SelectMap aSelectMap;
	m_pRole->GetSelectList(aSelectMap);
	oEvent.ApplyRoleModif(aSelectMap);
}



void FRoleControl::OnChangeRole(wxCommandEvent& event)
{
}