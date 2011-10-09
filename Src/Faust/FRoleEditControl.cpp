#include "FRoleEditControl.h"
#include "Utils.h"
#include "Config.h"
#include "FQuery.h"
#include "FApp.h"
#include "wx/datetime.h"
#include "FEvent.h"
#include "FNewRoleDialog.h"

BEGIN_EVENT_TABLE(FRoleEditControl, wxWindow)
	EVT_LISTBOX(ID_Role, OnChangeRole)
	EVT_BUTTON(ID_CreateBtn, OnCreateButton)
END_EVENT_TABLE()


FRoleEditControl::FRoleEditControl(wxWindow *parent, wxWindowID id, const wxString& sLabel)
	: wxWindow(parent, id)
	, m_pRole(NULL)
{
	wxStaticBoxSizer* pSizer = new wxStaticBoxSizer(wxVERTICAL, this, sLabel);
	{
		m_pRole = new wxListBox(this, ID_Role, wxDefaultPosition, wxSize(150, -1), wxArrayString(), wxLB_MULTIPLE);
		pSizer->Add(m_pRole, 0, 0, 0);
		
		pSizer->AddSpacer(5);

		m_pCreateBtn = new wxButton(this, ID_CreateBtn, wxT("Create new"), wxDefaultPosition, wxSize(150, -1));
		pSizer->Add(m_pCreateBtn, 0, 0, 0);
	}
	UpdateRoleList();

	SetSizeHints(160, -1, 160, -1);
	SetSizerAndFit(pSizer);
	Layout();
}

void FRoleEditControl::UpdateRoleList()
{
	m_pRole->Clear();

	wxString sEverybody = wxString(wxT("everybody"), wxConvISO8859_1);

	m_pRole->Append(sEverybody);

	PGresult* pResult;
	string SQuery = FormatString(FQ_ALLROLES_EXCEPT_PG);
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

	//if (m_pRole->GetCount() > 0)
	//	m_pRole->SetSelection(0);

	UpdateRole();
}

void FRoleEditControl::UpdateRole()
{
}

void FRoleEditControl::Save(FEvent& oEvent) const
{
	oEvent.ClearKnowers();
	for (uint i=0 ; i<m_pRole->GetCount() ; ++i)
	{
		if (m_pRole->IsSelected(i))
			oEvent.AddKnowers(string(m_pRole->GetString(i).mb_str(wxConvISO8859_1)));
	}
}

void FRoleEditControl::Load(const FEvent& oEvent)
{
	for (uint i=0 ; i<m_pRole->GetCount() ; ++i)
	{
		m_pRole->SetSelection(i, oEvent.IsKnower(string(m_pRole->GetString(i).mb_str(wxConvISO8859_1))));
	}
}


void FRoleEditControl::OnChangeRole(wxCommandEvent& event)
{
	UpdateRole();
}

void FRoleEditControl::OnCreateButton(wxCommandEvent& event)
{
	FNewRoleDialog oDialog(this, wxID_ANY, wxT("New Group"), wxDefaultPosition, wxDefaultSize, FNewRoleDialog::EM_NewGroup);
	if (oDialog.ShowModal() == wxID_OK)
	{
		UpdateRoleList();
	}
}
