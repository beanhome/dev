#include "FRoleControlEdit.h"
#include "Utils.h"
#include "Config.h"
#include "FQuery.h"
#include "FApp.h"
#include "FEvent.h"
#include "FNewRoleDialog.h"

BEGIN_EVENT_TABLE(FRoleControlEdit, FRoleControl)
	EVT_BUTTON(ID_CreateBtn, OnCreateButton)
END_EVENT_TABLE()


FRoleControlEdit::FRoleControlEdit(wxWindow *parent, wxWindowID id, const wxString& sLabel)
	: FRoleControl(parent, id, sLabel)
{
	wxStaticBoxSizer* pSizer = new wxStaticBoxSizer(wxVERTICAL, this, sLabel);
	{
		FRoleControl::Create(pSizer);

		pSizer->AddSpacer(5);

		m_pCreateBtn = new wxButton(this, ID_CreateBtn, wxT("Create new"), wxDefaultPosition, wxSize(150, -1));
		pSizer->Add(m_pCreateBtn, 0, 0, 0);
	}

	SetSizeHints(160, -1, 160, -1);
	SetSizerAndFit(pSizer);
	Layout();
}

void FRoleControlEdit::Save(FEvent& oEvent) const
{
	oEvent.ClearRoles();
	for (uint i=0 ; i<m_pRole->GetCount() ; ++i)
	{
		if (m_pRole->IsSelected(i))
			oEvent.AddRoles(string(m_pRole->GetString(i).mb_str(wxConvISO8859_1)));
	}
}

void FRoleControlEdit::Load(const FEvent& oEvent)
{
	for (uint i=0 ; i<m_pRole->GetCount() ; ++i)
	{
		m_pRole->SetSelection(i, oEvent.IsRole(string(m_pRole->GetString(i).mb_str(wxConvISO8859_1))));
	}
}

void FRoleControlEdit::OnCreateButton(wxCommandEvent& event)
{
	FNewRoleDialog oDialog(this, wxID_ANY, wxT("New Group"), wxDefaultPosition, wxDefaultSize, FNewRoleDialog::EM_NewGroup);
	if (oDialog.ShowModal() == wxID_OK)
	{
		UpdateRoleList();
	}
}
