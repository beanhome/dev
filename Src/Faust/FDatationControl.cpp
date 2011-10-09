#include "FDatationControl.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "wx/datetime.h"
#include "FCalendarDialog.h"
#include "FDateControl.h"

BEGIN_EVENT_TABLE(FDatationControl, wxPanel)
	EVT_CHECKBOX(ID_Activate, OnActivate)
END_EVENT_TABLE()


FDatationControl::FDatationControl(wxWindow *parent, wxWindowID id, const wxString& sLabel, wxPoint pos, wxSize size, bool bNoActivate)
	: wxPanel(parent, id, pos, size)
	, m_pActivateCheckBox(NULL)
	, m_pStartDate(NULL)
	, m_pEndDate(NULL)
{
	wxStaticBoxSizer* pSizer = new wxStaticBoxSizer(wxVERTICAL, this, sLabel);
	{
		if (!bNoActivate)
		{
			wxBoxSizer* pActivateSizer = new wxBoxSizer(wxHORIZONTAL);
			{
				wxStaticText* pActivateText = new wxStaticText(this, wxID_ANY, wxString(wxT("Activate")), wxDefaultPosition, wxSize(50, -1));
				pActivateSizer->Add(pActivateText, 0, wxALIGN_CENTER_VERTICAL, 0);

				m_pActivateCheckBox = new wxCheckBox(this, ID_Activate, wxT(""), wxDefaultPosition, wxDefaultSize);
				pActivateSizer->Add(m_pActivateCheckBox);
			}
			pSizer->Add(pActivateSizer, 0, wxBOTTOM, 3);
		}

		m_pStartDate= new FDateControl(this, ID_StartDate, wxString(wxT("Start")));
		pSizer->Add(m_pStartDate, 0, 0, 0);

		pSizer->AddSpacer(3);

		m_pEndDate = new FDateControl(this, ID_StartDate, wxString(wxT("End")));
		pSizer->Add(m_pEndDate, 0, 0, 0);
	}
	SetSizeHints(160, -1, 160, -1);
	SetSizerAndFit(pSizer);
	Layout();

	if (m_pActivateCheckBox != NULL)
	{
		m_pActivateCheckBox->SetValue(false);
		Activate(false);
	}
}

bool FDatationControl::IsActivated() const
{
	return (m_pActivateCheckBox == NULL || m_pActivateCheckBox->IsChecked());
}

void FDatationControl::Activate(bool bActivate)
{
	m_pStartDate->Enable(bActivate);
	m_pEndDate->Enable(bActivate);
}

bool FDatationControl::IsStartActivated() const
{
	return m_pStartDate != NULL && m_pStartDate->IsActivated();
}

bool FDatationControl::IsEndActivated() const
{
	return m_pEndDate != NULL && m_pEndDate->IsActivated();
}


FDate FDatationControl::GetStartDate() const
{
	return (m_pStartDate != NULL ? m_pStartDate->GetDate() : FDate());
}

FDate FDatationControl::GetEndDate() const
{
	return (m_pEndDate != NULL ? m_pEndDate->GetDate() : FDate());
}

void FDatationControl::SetDatation(const FDatation& oDatation)
{
	bool bStartIsNull = oDatation.GetStart().IsNull();
	m_pStartDate->Activate(!bStartIsNull);
	if (!bStartIsNull)
		m_pStartDate->GetTextControl()->SetValue(wxString(oDatation.GetStart().GetFormated(), wxConvISO8859_1));
	
	bool bEndIsNull = oDatation.GetEnd().IsNull();
	m_pEndDate->Activate(!bEndIsNull);
	if (!bEndIsNull)
		m_pEndDate->GetTextControl()->SetValue(wxString(oDatation.GetEnd().GetFormated(), wxConvISO8859_1));
}

void FDatationControl::OnActivate(wxCommandEvent& event)
{
	Activate(IsActivated());
}
