#include "FNewTagDialog.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "wx\datetime.h"
#include "wx\calctrl.h"

BEGIN_EVENT_TABLE(FNewTagDialog, wxDialog)
	EVT_BUTTON(wxID_OK, OnCreateButton)
END_EVENT_TABLE()


FNewTagDialog::FNewTagDialog(wxWindow *parent, wxWindowID id)
	: wxDialog(parent, id, wxT("Add Tag"), wxDefaultPosition /*, wxSize(200,300)*/)
{
	wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);

	int iLeftWidth = 65;
	int iRightWidth = 100;
	wxFlexGridSizer* pGridSizer = new wxFlexGridSizer(2);
	{
		wxStaticText* pNameLabel = new wxStaticText(this, wxID_ANY, wxT("Name : "), wxDefaultPosition, wxSize(iLeftWidth, -1));
		pGridSizer->Add(pNameLabel, 0, wxALIGN_CENTRE_VERTICAL);

		m_pName = new wxTextCtrl(this, ID_Name, wxT(""), wxDefaultPosition, wxSize(iRightWidth, -1));
		pGridSizer->Add(m_pName, 0 );
	}
	pSizer->Add(pGridSizer, 0, wxALL, 5);

	wxSizer* pButtonSizer = CreateButtonSizer(wxOK | wxCANCEL);
	pSizer->Add(pButtonSizer, 0, wxALIGN_CENTRE_HORIZONTAL | wxBOTTOM, 5);

	SetSizerAndFit(pSizer);
	Layout();
}

string FNewTagDialog::GetTagName() const
{
	return string(m_pName->GetValue().mb_str(wxConvISO8859_1));
}


void FNewTagDialog::OnCreateButton(wxCommandEvent& event)
{
	FApp::s_oSQLClient.Query(FormatString("INSERT INTO \"Tags\" (tag) VALUES ('%s')", GetTagName().c_str()));

	event.Skip();
}