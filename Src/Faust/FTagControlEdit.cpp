#include "FTagControlEdit.h"
#include "Utils.h"
#include "Config.h"
#include "FQuery.h"
#include "FApp.h"
#include "FNewTagDialog.h"
#include "FListControl.h"

BEGIN_EVENT_TABLE(FTagControlEdit, FTagControl)
	EVT_LISTBOX(ID_Tag, OnChangeTag)
	EVT_BUTTON(ID_CreateBtn, OnCreateButton)
END_EVENT_TABLE()

FTagControlEdit::FTagControlEdit()
{
}

//FTagControlEdit::FTagControlEdit(wxWindow *parent, wxWindowID id, const wxString& sLabel)
//	: FTagControl(parent, id, sLabel)
//{
//	Create(parent, id, sLabel);
//}

bool FTagControlEdit::Create(wxWindow *parent, wxWindowID id, const wxString& sLabel)
{
	wxPanel::Create(parent, id);

	wxStaticBoxSizer* pSizer = new wxStaticBoxSizer(wxVERTICAL, this, sLabel);
	{
		m_pTag = new FListControl(this, ID_Tag, wxDefaultPosition, wxSize(150, -1)/*, wxArrayString(), wxLB_MULTIPLE*/);
		pSizer->Add(m_pTag, 0, 0, 0);
		
		pSizer->AddSpacer(5);

		m_pCreateBtn = new wxButton(this, ID_CreateBtn, wxT("Create new"), wxDefaultPosition, wxSize(150, -1));
		pSizer->Add(m_pCreateBtn, 0, 0, 0);
	}
	SetSizeHints(160, -1, 160, -1);
	SetSizerAndFit(pSizer);
	Layout();

	UpdateTagList();

	return true;
}


void FTagControlEdit::OnCreateButton(wxCommandEvent& event)
{
	FNewTagDialog oDialog(this, wxID_ANY);
	if (oDialog.ShowModal() == wxID_OK)
	{
		wxString sName = wxString(oDialog.GetTagName().c_str(), wxConvISO8859_1);
		
		UpdateTagList();
		m_pTag->SetSelection(m_pTag->FindString(sName), true);
	}
}
