#include "FDateControl.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "wx/datetime.h"
#include "FCalendarDialog.h"

BEGIN_EVENT_TABLE(FDateControl, wxPanel)
	EVT_CHECKBOX( ID_CheckBox,	FDateControl::OnCheckStartDate)
	EVT_BUTTON( ID_CalButton,	FDateControl::OnClickStartDateCalBtn)
END_EVENT_TABLE()


FDateControl::FDateControl(wxWindow *parent, wxWindowID id, const wxString& sLabel)
	: wxPanel(parent, id)
	, m_pDateText(NULL)
	, m_pDateCheckBox(NULL)
	, m_pDateEntry(NULL)
	, m_pDateCalBtn(NULL)
{
	wxBoxSizer* pSizer = new wxBoxSizer(wxHORIZONTAL);

	m_pDateText = new wxStaticText(this, ID_Text, sLabel, wxDefaultPosition, wxSize(34, -1));
	pSizer->Add(m_pDateText, 0, wxALIGN_CENTER_VERTICAL, 0);

	m_pDateCheckBox = new wxCheckBox(this, ID_CheckBox, wxT(""), wxDefaultPosition, wxSize(-1, -1));
	pSizer->Add(m_pDateCheckBox, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 3);
	
	m_pDateEntry = new wxTextCtrl(this, wxID_ANY, wxDateTime::Today().Format(wxT("%d-%m-%Y")), wxDefaultPosition, wxSize(77, -1));
	pSizer->Add(m_pDateEntry, 0, wxRIGHT, 3);
	
	m_pDateCalBtn = new wxButton(this, ID_CalButton, wxT("Cal"), wxDefaultPosition, wxSize(20, -1));
	pSizer->Add(m_pDateCalBtn, 0, 0, 0);
	
	m_pDateCheckBox->SetValue(false);
	m_pDateEntry->Enable(m_pDateCheckBox->IsChecked());
	m_pDateCalBtn->Enable(m_pDateCheckBox->IsChecked());

	SetSizerAndFit(pSizer);
	Layout();
}

FDate FDateControl::GetDate() const
{
	return FDate(m_pDateEntry->GetValue().mb_str(wxConvISO8859_1));
}

void FDateControl::Activate(bool bActivate)
{
	m_pDateCheckBox->SetValue(bActivate);
	m_pDateEntry->Enable(bActivate);
	m_pDateCalBtn->Enable(bActivate);
}


void FDateControl::OnCheckStartDate(wxCommandEvent& WXUNUSED(event))
{
	m_pDateEntry->Enable(m_pDateCheckBox->IsChecked());
	m_pDateCalBtn->Enable(m_pDateCheckBox->IsChecked());
}

void FDateControl::OnClickStartDateCalBtn(wxCommandEvent& WXUNUSED(event))
{
	FCalendarDialog dialog(NULL, wxID_ANY);
	FDate oDate(m_pDateEntry->GetValue().mb_str(wxConvISO8859_1));
	dialog.SetDate(oDate);

	if (dialog.ShowModal() == wxID_OK)
	{
		oDate = dialog.GetDate();
		m_pDateEntry->ChangeValue(wxString(oDate.GetFormated(), wxConvISO8859_1));
	}
}
